/* mbedBug @version 0.x
@link    https://github.com/KabukiStarship/mbedBug.git
@file    /led_status.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#ifndef _mbedBug_StatusLED_header
#define _mbedBug_StatusLED_header
#define _Debug 0    //< Use this flag to turn this library into a debug example program. @see mbedBug.cpp:int main ()
#include <mbed.h>
#include <stdint.h>
#define _CreateStatusLED \
static StatusLED<0,1> Status (GREEN_LED);\

#define ASSERT(STATEMENT, MESSAGE) {\
    if (!(STATEMENT)) {\
        printf("ASSERT: %s\r\n%s, line %d\r\n", #MESSAGE, __FILE__, __LINE__)\
        Status.HandleAssert ()\
        while (true)\
    }\
} 

namespace mbedBug {

/* Outputs the firmware Status using the LED on the mbed board.
This class works by using strings with ASCII Mores Code. Each char in a 
represents a pulse split into 4 lengths.

| Frame | ASCII | Index | Duty Cycle |
|:-----:|:-----:|:-----:|:----------:|
| Off   | ' '   | <= 44 |     0%     |
| Long  | '-'   | 45    |    1/3     |
| Short | '.'   | 46    |    1/3     |
| On    | '_'   | >= 47 |   100%     |

Off could be any value less than 44, and On could be any value greater than 
47, but ASCII space (' ') and Period ('.') are used by convention because 
they look like the pulse widths.

## Terminology
* Frame    - Each character in a char Sequence represents 3 timer interrupts.
* Pattern  - A null-terminated string of frames.
* Sequence - A null-terminated string of const char*.

@code
StatusLED<0, 1> stausLED ();        //< Use <0, 1> if you're LED is active low.
StatusLED<1, 0> stausLED (LED_2);   //< Use <0, 1> if you're LED is active high.
    
const char* ExamplePattern[] = { 
    "...   ",       //< Blinks fast three times in a row.
    "...---...   ", //< SOS in Mores Code.
    "____    ",     //< Slowly blinks on and off.
    0               //< Must have null-termination pointer.
};

statusLED.SetPattern (exapmlePattern, 1.5f);

@endcode
*/
template <int On, int Off>
class StatusLED {
  public:
  
    char Count,             //< Counter counts from from 1-3.
        Period;             //< The current Period char.
    
    float Frequency;        //< The Period length

    const char** Sequence;  //< Null-terminated string of pointers.
    
    const char* Pattern,    //< The current string in the Sequence.
        * Cursor;           //< The current char in the current string.
    
    DigitalOut Pin;         //< Red LED on the mbed board.
    
    Ticker Blinker;         //< Ticker for blinking the LEDs.
    
    static const float FrequencyDefault = 0.5f, //< Default Frequency in hertz.
        FrequencyMin = 0.01f,                   //< Min Frequency in hertz.
        FrequencyMax = 2.0f;                    //< Max Frequency in hertz.
    
    typedef enum {
        Off     = 0,
        Short   = 63,
        Long    = 127,
        On      = 255
    } Pulse;
    
    /* Simple constructor. */
    StatusLED (PinName LEDPin = LED1, float Frequency = FrequencyDefault)
    :   Count     (0),
        Period    (0),
        Sequence  (0),
        Pattern   (0),
        Cursor    (0),
        Frequency (Frequency),
        Pin       (LEDPin, Off) {
        /// Nothing to do here.
    }
    
    /* Sets the light blinking Sequence. */
    void SetSequence (char** SequenceNew) {
        if (!SequenceNew) {
            Sequence = 0;
            StopBlinking ();
            return;
        }
        
        const char* TempString = Sequence[0];
        
        if (TempString == 0 || TempString[0] == 0) {
           #if _Debug
            printf ("\r\n\nError: First Sequence and first char can't be null.\r\n\n");
           #endif
            return;
        }
        Sequence = SequenceNew;
        Pattern = SequenceNew[0];
        Cursor = Pattern;
        CurrentByte = *Cursor;
        Update ();
    }
    
    /* Turns off the Blinker. */
    void TurnOff () {
        Pin = Off; 
    }
    
    /* Turns on the Blinker. */
    void TurnOn () { 
        Color = ColorA;
        Update (); 
    }
    
    /* Starts flashing the SOS Sequence. */
    void FlashSOS () {
        Sequence = SoSPattern ();
        Cursor = Sequence[0];
        Cursor = *Cursor;
        Period = *Cursor;
    }
    
    /* Starts blinking. */
    void StartBlinking () {
        const char* _pattern = Sequence[0];
        Pattern = _pattern;
        Cursor = _pattern;
        Period = *_pattern;

        Blinker.attach (this, &StatusLED::blink, Frequency / 4);
        Update ();
    }
    
    /* Stops blinking and turns off the LED. */
    void StopBlinking  () {
        TurnOff ();
        Blinker.detach ();
        Pin = Off;
        Update ();
    }
    
    /* Sets the blink Frequency. */
    void FrequencySet (float Value) {
        Frequency = Value;
        Blinker.attach (this, &StatusLED::Blink, Value);
    }
    
    /* Handler for the ASSERT macro. */
    void HandleAssert () {
        SetPattern (SoSPattern ());
    }
    
    /* Pattern blinks three times in a row. */
    const char** Blink3TimesPattern () {
        static const char** Sequence = { "...   ", 0 };
        return &Sequence;
    }

    /* Standard blink Sequence. */
    const char** SlowBlinkPattern () {
        static const char** Sequence = { "__  ", 0 };
        return &Sequence;
    }
    
    /* Standard blink Sequence. */
    const char** FastBlinkPattern ()     {
        static const char** Sequence = { "_ ", 0 };
        return &Sequence;
    }
    
    /* Standard SOS Sequence. */
    const char** SoSPattern () {
        static const char** Sequence = { "...---...      ", 0 };
        return &Sequence;
    }
    
    /* Returns the next char in the Sequence. */
    inline char GetNextPeriod () {
        /// We've already checked that the Sequence and Cursor and not null.
        
        char period_temp = *(++Cursor);
        
        if (period_temp == 0) {
            const char* temp_pattern = *(Pattern + sizeof (const char*));
            
            if (!temp_pattern) {
                const char* _cursor = Sequence[0];
                Cursor = Pattern = _cursor;
                return *_cursor;
            }
            Pattern = temp_pattern;
            return *temp_pattern;    //< We don't particularly care if the Period is '\0'.
        }
        
        return period_temp;
    }
    
    /* Updates the Status LED. */
    inline void Update () {
        const char* period_temp = Period;
        if (!Sequence || !period_temp) return;
        
        if (Count == 0) {       //< Beginning of cycle Period.
            char _period = GetNextPeriod ();
            Period = _period;
            Count = 1;
            if (_period < '-') {
                Pin = Off; 
                return; 
            }
            Pin = On;
            return;
        }
        else if (Count == 1) { //< 1/3 duty cycle.
            Count = 2;
            if (Period == '.') {
                Pin = Off; 
                return; 
            }
            return;
        }
        /// 2/3 duty cycle.
        Count = 0;
        if (Period > '.')       //< Leave the LED on
            return;
        Pin = Off;
    }
};
}

// _D_e_m_o_____________________________________________________________________

#if 0   //< Set to non-zero to run this demo.

using namespace mbedBug;

StatusLED Status ();
InterruptIn switch3 (SW3);

const char* ExamplePattern[] = {
    "...   ",           //< Blinks fast three times in a row.
    "...---...      ",  //< SOS in Mores Code.
    "____    ",         //< Slowly blinks on and off.
    0                   //< Pattern must have null-term pointer.
};
/* Interrupt handler for SW2. */
void SwitchIRQHandler () {
    static bool ExamplePatterMode = true;
    
    if (ExamplePatterMode) {
        Status.SetPattern (ExamplePattern);
        Status.StartBlinking ();
        ExamplePatterMode = false;
    }
    else {  
        Status.SetPattern(Status.SOSPattern ()));
        ExamplePatterMode = true;
    }
}

int main() {
    printf ("\r\n\nTesting mbed Utils.\r\n\n");
    PrintLine ();
    
    switch3.rise (&SwitchIRQHandler);
    //Status.StartBlinking ()
    
    while (true);
}

#endif  //< Demo
#endif
