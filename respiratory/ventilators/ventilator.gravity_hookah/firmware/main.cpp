/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /main.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2029 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#define _DebugGHV     1   //< Set to 0 or 1 to enable or disable debugging.

/* @note This firmware was for a water flow controller and is in the process of 
being modified. */

#include <mbedBug.h>

#include "ghv_channel.h"
using namespace sickbay;

FlowController channels[] = {
// Flow sensor ---v    v---- Solenoid
    FlowController (D3, D6, A0),
    FlowController (D4, D7, A1),
    FlowController (D5, D8, A2),
    FlowController (PC_13, D9, A3)
//                    Pot ---^
};

volatile int current_channel = -1;
volatile bool not_enough_air = false;

Ticker seconds_ticker,
    cycle_ticker;

using namespace sickbay;
using namespace mbedBug;

#if _DebugGHV
Ticker debug_ticker;

void demoTickerISR () {
    channels[current_channel].pulseFlowSensor ();
}
#endif  //< _DebugGHV

/* ISR called at the begining of each watering cycle. */
void Begincycle_tickerISR ()
{
    if (current_channel >= 0) // Then we are not done watering.
    {
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
            
            /// Reset the cycle timer to cycleTimeSeconds from now.
            
            cycle_ticker.detach ();
            begincycle_tickerISR ();
            cycle_ticker.attach (&begincycle_tickerISR, cycleTimeSeconds);
            not_enough_air = false;
        }
        return;
    }
    
    if (channels[current_channel].checkIfDoneWatering (current_channel + 1)) {
        if (--current_channel < 0) {
            if (not_enough_air) {
                printf ("Resetting cycle timer.\r\n\r\n");
                
                /// Reset the cycle timer to cycleTimeSeconds from now.
                
                cycle_ticker.detach ();
                begincycle_tickerISR ();
                cycle_ticker.attach (&begincycle_tickerISR, cycleTimeSeconds);
                not_enough_air = false;
            }
            return;
        }
        channels[current_channel].BreatheStart (current_channel + 1);
    }
}

int main () { 
    printf ("\r\n\n\n\n\n\n\n\n\n\n\n\n\r\nStarting sickbay...\n\r\n\r");

    seconds_ticker.attach (&secondTickerISR, 1.0f);
    
    begincycle_tickerISR (); //< Wont update for a while so call before attaching ISR.
    cycle_ticker.attach (&begincycle_tickerISR, cycleTimeSeconds);
    
    #if _DebugGHV
    debug_ticker.attach (&demoTickerISR, 1.0f/200.0f);
    #endif //< _DebugGHV
    
    while (1);  //< This is an IRQ driven application.
}
