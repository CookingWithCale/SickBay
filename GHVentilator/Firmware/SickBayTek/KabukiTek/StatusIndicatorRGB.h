/* Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /StatusIndicatorRGB.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#ifndef MbedBugStatusIndicatorRGBDecl
#define MbedBugStatusIndicatorRGBDecl
#include "_Config.h"
#define CREATE_RGB_STATUS_LED \
static StatusIndicatorRGB<0,1> Status (RED_LED, GREEN_LED, BLUE_LED);\

#define Assert(statement, message) {\
  if (!(statement)) {\
  printf("Assert: %s\r\n%s, line %d\r\n", #message, __FILE__, __LINE__)\
  Status.HandleAssert ()\
  while (true)\
  }\
}

namespace Primary {

typedef enum {
  ColorPresetBlack   = 0,
  ColorPresetRed   = 1,
  ColorPresetYellow  = 2,
  ColorPresetGreen   = 3,
  ColorPresetCyan   = 4,
  ColorPresetBlue  = 5,
  ColorPresetMagenta = 6,
  ColorPresetWhite   = 7
} Color;
}   //< namespace Primary

namespace _ {
  
/* The onboard mbed RGB LED.
Some boards have PWM on the RGB LED, some don't. This class uses DigitalOut(s). 
There are 8 potential combinations  of Color without PWM (@see Wiki 
"Color Space").

@code
StatusIndicatorRGB<0, 1> stausLED (RED_LED, GREEN_LED, BLUE_LED);  //< Use <0, 1> if you're LED is active low.
StatusIndicatorRGB<1, 0> stausLED (p0, p1, p2);  //< Use <0, 1> if you're LED is active high.

statusLED.SetColorA (Color::);

@endcode
*/
template <int On, int Off>
class StatusIndicatorRGB {
  public:
  
  enum {
    BrightnessDefault = 128
  };
  
  float Frequency;  //< The Frequency of the blinking.
  
  DigitalOut Red,   //< ColorPresetRed LED on the mbed board.
     Green,         //< ColorPresetGreen LED on the mbed board.
     Blue;          //< ColorPresetBlue LED on the mbed board.
  
  Ticker Blinker;   //< Ticker for blinking the LEDs.
  
  uint8_t Color,    //< The current Color.
    ColorA,     //< Blink Color A.
    ColorB;     //< Blink Color B.
  
  /* Simple constructor. */
  StatusIndicatorRGB (PinName RedLED, PinName GreenLED, PinName BlueLED, float BinkDelay = 0.2f)
  :   Frequency (Frequency),
    Red   (RedLED),
    Green   (GreenLED),
    Blue  (BlueLED),
    Blinker   (),
    Color   (Color::ColorPresetBlack),
    ColorA  (Color::ColorPresetBlack),
    ColorB  (Color::ColorPresetBlack) {
    Red = Green = Blue = 1;
  }
  
  /* Updates the RGB status LED "frame": Color. */
  void Update () {
    switch (Color) {
      case Color::ColorPresetBlack  : Red = 1; Green = 1; Blue = 1; return;
      case Color::ColorPresetRed  : Red = 0; Green = 1; Blue = 1; return;
      case Color::ColorPresetYellow : Red = 0; Green = 0; Blue = 1; return;
      case Color::ColorPresetGreen  : Red = 1; Green = 0; Blue = 1; return;
      case Color::ColorPresetCyan   : Red = 1; Green = 0; Blue = 0; return;
      case Color::ColorPresetBlue   : Red = 1; Green = 1; Blue = 0; return;
      case Color::ColorPresetMagenta: Red = 0; Green = 1; Blue = 0; return;
      case Color::ColorPresetWhite  : Red = 0; Green = 0; Blue = 0; return;
    }
  }
  
  /* Sets ColorA. */
  void SetColorA (Primary::Color Value) {
    ColorA = Value; 
  }
  
  /* Sets ColorB. */
  void SetColorB (Primary::Color Value) {
    ColorB = Value; 
  }
  
  /* Turns off the Blinker. */
  void TurnOff () {
    Red = Green = Blue = 1;
  }
  
  /* Turns on the Blinker. */
  void TurnOn () { 
    Color = ColorA; 
    Update ();
  }
  
  /* Sets the Color of the Blinker. */
  void ColorsSet (Primary::Color ColorA, Primary::Color ColorB = Primary::ColorPresetBlack)
  {
    ColorA = ColorA;
    ColorB = ColorB;
  }
  
  void FlashRedBlue ()
  /* Starts flashing Red and Blue lights. */
  {
    ColorA = Primary::ColorPresetRed;
    ColorB = Primary::ColorPresetBlue;
    StartBlinking ();
  }
  
  void StartBlinking ()
  /* Starts blinking. */
  {
    Blinker.attach (this, &StatusIndicatorRGB::Blink, Frequency);
    Color = ColorA;
    Update ();
  }
  
  /* Stops blinking and turns off the LED. */
  void StopBlinking  () {
    TurnOff ();
    Blinker.detach ();
    Color = Primary::ColorPresetBlack;
    Update ();
  }
  
  /* Starts blinking and turns on Color A. */
  void StopBlinkingA () {
    Color = ColorA;
    Blinker.detach ();
  }
  
  /* Starts blinking and turns on Color B. */
  void StopBlinkingB () {
    Color = ColorB;
    Blinker.detach ();
  }
  
  
  /* Sets the Blink Frequency. */
  void FrequencySet (float Value) {
    Frequency = Value;
    Blinker.attach (this, &StatusIndicatorRGB::Blink, Value);
  }
  
  /* Handler for the Assert macro. */
  void HandleAssert () {
    FlashRedBlue ()
  }

  private:
  
  /* Blinks the status RGB LED on the mbed board between ColorA and ColorB. */
  void Blink () { 
    Color = (Color == ColorA) ? ColorB : ColorA;   
    Update ();
  }
};
}

// _D_e_m_o_____________________________________________________________________

#if 0   //< Set to non-zero to run this demo.

using namespace _;

StatusIndicatorRGB Status (LED_RED, LED_GREEN, LED_BLUE);
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
    Status.SetColorB (Primary::ColorPresetBlack);
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
