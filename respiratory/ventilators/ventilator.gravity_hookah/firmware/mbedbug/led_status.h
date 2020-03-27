/* mbedbug @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /led_status.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#ifndef _mbedBug_StatusLED_header
#define _mbedBug_StatusLED_header
#define _Debug 0    //< Use this flag to turn this library into a debug example program. @see mbedbug.cpp:int main ()
#include <mbed.h>
#include <stdint.h>
#define _CreateStatusLED \
static StatusLED<0,1> status (GREEN_LED);\

#define Assert(statement, message) {\
    if (!(statement)) {\
        printf("Assert: %s\r\n%s, line %d\r\n", #message, __FILE__, __LINE__)\
        status.HandleAssert ()\
        while (true)\
    }\
} 

namespace mbedbug {

/* Outputs the firmware status using the LED on the mbed board.
This class works by using strings with ASCII Mores Code. Each char in a 
represents a pulse split into 4 lengths.

| Frame | ASCII | Index | Duty Cycle |
|:-----:|:-----:|:-----:|:----------:|
| Off   | ' '   | <= 44 |     0%     |
| Long  | '-'   | 45    |    1/3     |
| Short | '.'   | 46    |    1/3     |
| On    | '_'   | >= 47 |   100%     |

Off could be any value less than 44, and On could be any value greater than 
47, but ASCII space (' ') and period ('.') are used by convention because 
they look like the pulse widths.

## Terminology
* Frame    - Each character in a char sequence represents 3 timer interrupts.
* Pattern  - A null-terminated string of frames.
* Sequence - A null-terminated string of const char*.

@code
StatusLED<0, 1> stausLED ();        //< Use <0, 1> if you're LED is active low.
StatusLED<1, 0> stausLED (LED_2);   //< Use <0, 1> if you're LED is active high.
    
const char* example_pattern[] = { 
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
    
    static const float DefaultFrequency = 0.5f, //< Default frequency in hertz.
        MinFrequency = 0.01f,                   //< Min frequency in hertz.
        MaxFrequency = 2.0f;                    //< Max frequency in hertz.
    
    typedef enum {
        Off     = 0,
        Short   = 63,
        Long    = 127,
        On      = 255
    } Pulse;
    
    /* Simple constructor. */
    StatusLED (PinName LEDPin = LED_1, float Frequency = DefaultFrequency)
    :   count     (0),
        period    (0),
        sequence  (0),
        pattern   (0),
        cursor    (0),
        frequency (Frequency),
        pin       (LEDPin, Off) {
        /// Nothing to do here.
    }
    
    /* Sets the light blinking sequence. */
    void SetSequence (char** new_sequence) {
        if (!new_sequence) {
            sequence = 0;
            stopBlinking ();
            return;
        }
        
        const char* temp_string = sequence[0];
        
        if (temp_string == 0 || temp_string[0] == 0) {
           #if _Debug
            printf ("\r\n\nError: First sequence and first char can't be null.\r\n\n");
           #endif
            return;
        }
        sequence = new_sequence;
        pattern = new_sequence[0];
        cursor = pattern;
        currentByte = *cursor;
        Update ();
    }
    
    /* Turns off the blinker. */
    void TurnOff () {
        pin = Off; 
    }
    
    /* Turns on the blinker. */
    void TurnOn () { 
        color = colorA;
        Update (); 
    }
    
    /* Starts flashing the SOS sequence. */
    void FlashSOS () {
        sequence = SoSPattern ();
        const char* _cursor = sequence[0];
        cursor = *_cursor;
        period = *_cursor;
    }
    
    /* Starts blinking. */
    void StartBlinking () {
        const char* _pattern = sequence[0];
        pattern = _pattern;
        cursor = _pattern;
        period = *_pattern;

        blinker.attach (this, &StatusLED::blink, frequency / 4);
        Update ();
    }
    
    /* Stops blinking and turns off the LED. */
    void StopBlinking  () {
        TurnOff ();
        blinker.detach ();
        pin = Off;
        Update ();
    }
    
    /* Sets the blink frequency. */
    void SetFrequency (float Value) {
        frequency = Value;
        blinker.attach (this, &StatusLED::Blink, Value);
    }
    
    /* Handler for the Assert macro. */
    void HandleAssert () {
        SetPattern (SoSPattern ());
    }
    
    /* Pattern blinks three times in a row. */
    const char** Blink3TimesPattern () {
        static const char** sequence = { "...   ", 0 };
        return &sequence;
    }

    /* Standard blink sequence. */
    const char** SlowBlinkPattern () {
        static const char** sequence = { "__  ", 0 };
        return &sequence;
    }
    
    /* Standard blink sequence. */
    const char** FastBlinkPattern ()     {
        static const char** sequence = { "_ ", 0 };
        return &sequence;
    }
    
    /* Standard SOS sequence. */
    const char** SoSPattern () {
        static const char** sequence = { "...---...      ", 0 };
        return &sequence;
    }

  private:
  
    char count,             //< Counter counts from from 1-3.
        period;             //< The current period char.
    
    float frequency;        //< The period length

    const char** sequence;  //< Null-terminated string of pointers.
    
    const char* pattern,    //< The current string in the sequence.
        * cursor;           //< The current char in the current string.
    
    DigitalOut pin;         //< Red LED on the mbed board.
    
    Ticker blinker;         //< Ticker for blinking the LEDs.
    
    /* Returns the next char in the sequence. */
    inline char GetNextPeriod () {
        /// We've already checked that the sequence and cursor and not null.
        
        char period_temp = *(++cursor);
        
        if (period_temp == 0) {
            const char* temp_pattern = *(pattern + sizeof (const char*));
            
            if (!temp_pattern) {
                const char* _cursor = sequence[0];
                cursor = pattern = _cursor;
                return *_cursor;
            }
            pattern = temp_pattern;
            return *temp_pattern;    //< We don't particularly care if the period is '\0'.
        }
        
        return period_temp;
    }
    
    /* Updates the status LED. */
    inline void Update () {
        const char* period_temp = period;
        if (!sequence || !period_temp) return;
        
        if (count == 0) {       //< Beginning of cycle period.
            char _period = GetNextPeriod ();
            period = _period;
            count = 1;
            if (_period < '-') {
                pin = Off; 
                return; 
            }
            pin = On;
            return;
        }
        else if (count == 1) { //< 1/3 duty cycle.
            count = 2;
            if (period == '.') {
                pin = Off; 
                return; 
            }
            return;
        }
        /// 2/3 duty cycle.
        count = 0;
        if (period > '.')       //< Leave the LED on
            return;
        pin = Off;
    }
};
}

// _D_e_m_o_____________________________________________________________________

#if 0   //< Set to non-zero to run this demo.

using namespace mbedbug;

StatusLED status ();
InterruptIn switch3 (SW3);

const char* example_pattern[] = {
    "...   ",           //< Blinks fast three times in a row.
    "...---...      ",  //< SOS in Mores Code.
    "____    ",         //< Slowly blinks on and off.
    0                   //< Pattern must have null-term pointer.
};
/* Interrupt handler for SW2. */
void SwitchIRQHandler () {
    static bool examplePatterMode = true;
    
    if (examplePatterMode) {
        status.SetPattern (example_pattern);
        status.StartBlinking ();
        examplePatterMode = false;
    }
    else {  
        status.SetPattern(status.SOSPattern ()));
        examplePatterMode = true;
    }
}

int main() {
    printf ("\r\n\nTesting mbed Utils.\r\n\n");
    PrintLine ();
    
    switch3.rise (&SwitchIRQHandler);
    //status.StartBlinking ()
    
    while (true);
}

#endif  //< Demo
#endif
