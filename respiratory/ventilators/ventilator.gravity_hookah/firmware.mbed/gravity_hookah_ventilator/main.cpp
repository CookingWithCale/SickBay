/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /main.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2029 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#define GHV_DEBUG     1   //< Set to 0 or 1 to enable or disable debugging.

/* @note This firmware was for a water flow controller and is in the process of 
being modified. */

#include <mbedbug.h>

#include "ghv_channel.h"
using namespace sickbay;

GHVChannel channels[] = {
    //          +---------- Flow sensor
    //          |    +----- Solenoid
    //          v    v  v-- Pot 
    GHVChannel (D3, D6, A0),
    GHVChannel (D4, D7, A1),
    GHVChannel (D5, D8, A2),
    GHVChannel (PC_13, D9, A3)
};

volatile int current_channel = -1;
volatile bool not_enough_air = false;

Ticker seconds_ticker,
    cycle_ticker;

using namespace sickbay;
using namespace mbedbug;

#if GHV_DEBUG
Ticker debug_ticker;

void DemoTickerISR () {
    channels[current_channel].PulseFlowSensor ();
}
#endif  //< GHV_DEBUG

/* ISR called at the begining of each watering cycle. */
void BeginCycleTickerISR () {
    if (current_channel >= 0) { // Then we are not done watering.
        printf ("Not enough flow on channel %i to match timer!\r\n", 
            current_channel);
        not_enough_air = true;
        return;
    }
    
    not_enough_air = false;
    
    current_channel = cChannelCount - 1;
    printf ("Starting Watering Cycle...\n\r");
    channels[current_channel].BreatheStart (current_channel + 1);
}

/* ISR gets called every second to update the FlowChannel(s). */
void SecondTickerISR () {
    if (current_channel < 0) {
        if (not_enough_air) {
            printf ("Resetting cycle timer.\r\n");
            
            /// Reset the cycle timer to cCycleTimeSeconds from now.
            
            cycle_ticker.detach ();
            BeginCycleTickerISR ();
            cycle_ticker.attach (&BeginCycleTickerISR, cCycleTimeSeconds);
            not_enough_air = false;
        }
        return;
    }
    
    if (channels[current_channel].CheckIfDoneWatering (current_channel + 1)) {
        if (--current_channel < 0) {
            if (not_enough_air) {
                printf ("Resetting cycle timer.\r\n\r\n");
                
                /// Reset the cycle timer to cCycleTimeSeconds from now.
                
                cycle_ticker.detach ();
                BeginCycleTickerISR ();
                cycle_ticker.attach (&BeginCycleTickerISR, cCycleTimeSeconds);
                not_enough_air = false;
            }
            return;
        }
        channels[current_channel].BreatheStart (current_channel + 1);
    }
}

int main () { 
    printf ("\r\n\n\n\n\n\n\n\n\n\n\n\n\r\nStarting sickbay...\n\r\n\r");

    seconds_ticker.attach (&SecondTickerISR, 1.0f);
    
    BeginCycleTickerISR (); //< Wont update for a while so call before attaching ISR.
    cycle_ticker.attach (&BeginCycleTickerISR, cCycleTimeSeconds);
    
    #if GHV_DEBUG
    debug_ticker.attach (&DemoTickerISR, 1.0f/200.0f);
    #endif //< GHV_DEBUG
    
    while (1);  //< This is an IRQ driven application.
}
