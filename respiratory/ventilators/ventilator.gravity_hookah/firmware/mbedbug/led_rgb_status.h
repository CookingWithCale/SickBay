/* mbedbug @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /led_rgb_status.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#ifndef _mbedBug_RGBStatusLED_header
#define _mbedBug_RGBStatusLED_header
#include "mbed.h"
#include <stdint.h>
#define CREATE_RGB_STATUS_LED \
static RGBStatusLED<0,1> Status (RED_LED, GREEN_LED, BLUE_LED);\

#define Assert(statement, message) {\
    if (!(statement)) {\
        printf("Assert: %s\r\n%s, line %d\r\n", #message, __FILE__, __LINE__)\
        Status.HandleAssert ()\
        while (true)\
    }\
}

namespace Primary {

typedef enum {
    cColorPresetBlack   = 0,
    cColorPresetRed     = 1,
    cColorPresetYellow  = 2,
    cColorPresetGreen   = 3,
    cColorPresetCyan    = 4,
    cColorPresetBlue    = 5,
    cColorPresetMagenta = 6,
    cColorPresetWhite   = 7
} Color;
}   //< namespace Primary

namespace mbedbug {
    
/* The onboard mbed RGB LED.
Some boards have PWM on the RGB LED, some don't. This class uses DigitalOut(s). There are 8 potential combinations 
of color without PWM (@see Wiki:"Color Space"), cColorPresetBlack, cColorPresetRed, cColorPresetYellow, cColorPresetGreen, cColorPresetCyan, cColorPresetBlue, cColorPresetMagenta, and cColorPresetWhite.

@code
RGBStatusLED<0, 1> stausLED (RED_LED, GREEN_LED, BLUE_LED);    //< Use <0, 1> if you're LED is active low.
RGBStatusLED<1, 0> stausLED (p0, p1, p2);                      //< Use <0, 1> if you're LED is active high.

statusLED.SetColorA (Color::);

@endcode
*/
template <int On, int Off>
class RGBStatusLED {
  public:
    
    enum {
        cDefaultBrightness = 128
    };
    
    /* Simple constructor. */
    RGBStatusLED (PinName redLED, PinName greenLED, PinName blueLED, float blinkDelay = 0.2f)
    :   frequency (aFrequency),
        red       (redLED),
        green     (greenLED),
        blue      (blueLED),
        blinker   (),
        color     (Color::cColorPresetBlack),
        color_a    (Color::cColorPresetBlack),
        color_b    (Color::cColorPresetBlack) {
        red = green = blue = 1;
    }
    
    /* Updates the RGB status LED "frame": color. */
    void Update () {
        switch (color) {
            case Color::cColorPresetBlack  : red = 1; green = 1; blue = 1; return;
            case Color::cColorPresetRed    : red = 0; green = 1; blue = 1; return;
            case Color::cColorPresetYellow : red = 0; green = 0; blue = 1; return;
            case Color::cColorPresetGreen  : red = 1; green = 0; blue = 1; return;
            case Color::cColorPresetCyan   : red = 1; green = 0; blue = 0; return;
            case Color::cColorPresetBlue   : red = 1; green = 1; blue = 0; return;
            case Color::cColorPresetMagenta: red = 0; green = 1; blue = 0; return;
            case Color::cColorPresetWhite  : red = 0; green = 0; blue = 0; return;
        }
    }
    
    /* Sets color_a. */
    void SetColorA (Primary::Color value) {
        color_a = value; 
    }
    
    /* Sets color_b. */
    void SetColorB (Primary::Color value) {
        color_b = value; 
    }
    
    /* Turns off the blinker. */
    void TurnOff () {
        red = green = blue = 1;
    }
    
    /* Turns on the blinker. */
    void TurnOn () { 
        color = color_a; 
        Update ();
    }
    
    /* Sets the color of the blinker. */
    void SetColors (Primary::Color ColorA, Primary::Color ColorB = Primary::cColorPresetBlack)
    {
        color_a = ColorA;
        color_b = ColorB;
    }
    
    void flashRedBlue ()
    /* Starts flashing red and blue lights. */
    {
        color_a = Primary::cColorPresetRed;
        color_b = Primary::cColorPresetBlue;
        StartBlinking ();
    }
    
    void startBlinking ()
    /* Starts blinking. */
    {
        blinker.attach (this, &RGBStatusLED::Blink, frequency);
        color = color_a;
        Update ();
    }
    
    /* Stops blinking and turns off the LED. */
    void StopBlinking  () {
        TurnOff ();
        blinker.detach ();
        color = Primary::cColorPresetBlack;
        Update ();
    }
    
    /* Starts blinking and turns on Color A. */
    void StopBlinkingA () {
        color = color_a;
        blinker.detach ();
    }
    
    /* Starts blinking and turns on Color B. */
    void StopBlinkingB () {
        color = color_b;
        blinker.detach ();
    }
    
    
    /* Sets the Blink frequency. */
    void SetFrequency (float value) {
        frequency = value;
        blinker.attach (this, &RGBStatusLED::Blink, value);
    }
    
    /* Handler for the Assert macro. */
    void HandleAssert () {
        FlashRedBlue ()
    }

  private:
    
    float frequency;            //< The frequency of the blinking.
    
    DigitalOut red,             //< cColorPresetRed LED on the mbed board.
         green,                 //< cColorPresetGreen LED on the mbed board.
         blue;                  //< cColorPresetBlue LED on the mbed board.
    
    Ticker blinker;             //< Ticker for blinking the LEDs.
    
    uint8_t color,              //< The current color.
        color_a,                 //< Blink color A.
        color_b;                 //< Blink color B.
    
    /* Blinks the status RGB LED on the mbed board between color_a and color_b. */
    void Blink () { 
        color = (color == color_a) ? color_b : color_a;   
        Update ();
    }
};
}

// _D_e_m_o_____________________________________________________________________

#if 0   //< Set to non-zero to run this demo.

using namespace mbedbug;

RGBStatusLED Status (LED_RED, LED_GREEN, LED_BLUE);
InterruptIn Switch3 (SW3);

/* Interrupt handler for SW2. */
void SW3Handler () {
    static int counter = 16;
    
    if (++counter > 15) {
        Status.FlashRedBlue (); counter = 0;
    }
    else if (counter & 1) { 
        Status.StopBlinking  ();
    } else {  
        Status.SetColorA ((Primary::Color)(counter >> 1));
        Status.SetColorB (Primary::cColorPresetBlack);
        Status.StartBlinking ();
    }
}

int main() {
    printf ("\r\nTesting mbed Utils.\r\n");
    PrintLine ('-');
    
    Switch3.rise (&SW3Handler);
    //Status.StartBlinking ();
    
    while (true);
}
#endif  //< #if _Demo

#endif
