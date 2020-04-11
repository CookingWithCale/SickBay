/** Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /Debouncer.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef KabukiTek
/** Dr Marty's switch debounce algorihm for shift registers and GPIO pins.
In order to use this class, simply feed the constructor the address of the 
memory you want to store the debounced data too. This allows the debounced 
General Purpose Inputs (GPI) and shift register inputs to to be packed into
a single array of bytes so they can be quickly polled.

@code
// 100Hz polling example with one 74HC165 shift register and GPI Port.

#include "mbed.h"
#include "debouncer.hpp"

SPI Spi1 (D11, D12, D13);
DigitalOut Spi1CS (D10);
    
Ticker PollInputsTicker;
PortIn GPIPort (PortA);

char InputStates[5];
Debouncer<int> GPIPortDebouncer ((int*)&InputStates[0]);
Debouncer<char> ShiftRegisterDebouncer (&InputStates[4]);

void PollInputsHandler () {
    Spi1CS = 1;
    char shift = ShiftRegisterDebouncer.Debounce (Spi1.write (0));
    int portA = GPIPortDebouncer.Debounce (GPIPort);
    Spi1CS = 0;
}

int main() {
    PollInputsTicker.attach (&PollInputsHandler, 1.0f / 100.0f);
    Spi1.format (8,3);
    Spi1.frequency (115200);
    while (true) ;
}
@endcode */
template <typename T>
class Debouncer {
    public:
    
    /* Constructor. */
    Debouncer (T* StateAddress, T Mask = (~(0))):
        one   (0),
        two   (0),
        three (0),
        mask  (0),
        state (StateAddress) {
    }
    
    /* Debounces the input and returns an XOR of changes.
    Using an XOR of the previous state shows you which button states
    have changed. */
    inline T Debounce (T sample) {
      T previousState = *state,
        currentState = previousState & (one | two | three) | (one & two & three);
      *state = currentState;
      three = two;
      two = one;
      one = sample;
      return (previousState ^ currentState) & mask;
    }
    
    private:
    
    T one,        //< Sample t - 1.
      two,        //< Sample t - 2.
      three,      //< Sample t - 3.
      mask;       //< Mask for the state.
    
    T* state;     //< Pointer to the state.
};
 
#define _Debug      0
#if _Debug
 
#include "mbed.h"
#include "Debouncer.hpp"
 
#define _BaudRate   115200
 
Serial pc(USBTX, USBRX);
 
SPI Spi1 (D11, D12, D13);
 
DigitalOut Spi1CS (D10),
    RedLED   (LED_RED),
    GreenLED (LED_GREEN),
    BlueLED  (LED_BLUE);
    
uint8_t states[5];
    
PortIn GPIPort (PortA);
 
Debouncer<int> GPIPortDebouncer ((int*)&states[0], 
                                       (int)0b00011110000001111111111111111111);
Debouncer<uint8_t> ShiftRegisterDebouncer (&states[5]);
    
void PollInputsHandler () {
    Spi1CS = 1;
    char dataIn = ShiftRegisterDebouncer.Debounce (Spi1.write (0));
    int portA = GPIPortDebouncer.Debounce (GPIPort);
    if (dataIn & 0b001) RedLED   = RedLED   == 0 ? 1 : 0;
    if (dataIn & 0b010) GreenLED = GreenLED == 0 ? 1 : 0;
    if (dataIn & 0b100) BlueLED  = BlueLED  == 0 ? 1 : 0;
    Spi1CS = 0;
    pc.printf ("%x%x", dataIn, portA);
}
 
int main() {
    static const float updateInterval = 0.010f;
    pc.baud (_BaudRate);
    pc.printf ("\n\r\n====================================================\n\r", 
        1.0f / updateInterval);
    RedLED = GreenLED = BlueLED = 1;
    
    Spi1CS = 0;
    Spi1.format (8,3);
    Spi1.frequency (_BaudRate);
    
    while (true) ;
}
#endif  //< FASTDEBOUNCE_DEBUG