/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /ghv_channel.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2029 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once

#include <mbed.h>
#include <stdint.h>

#include "ghv_config.h"

namespace sickbay {

/* A channel going to on patient. */
class GHVChannel {
    public:

    /* Constructs a smart waterer. */
    GHVChannel (PinName sensorPin, PinName solenoidPin, AnalogIn potPin);
    
    /* Calculates the total flow in millilters. */
    int32_t CalcTotalFlow_mL ();
    
    /* Calculates the target flow in millilters. */
    int32_t CalcTargetFlow_mL ();
    
    /* Calculates the flow rate in millilters. */
    int32_t CalcFlowRate_mL ();
      
    /* BreatheStarts to the begining of the watering cycle. */
    void BreatheStart (int index);
    
    /* Increments theflow rate sensor pulse counter. */
    void PulseFlowSensor ();
    
    /* Prints the state of object to the debug stream. */
    void Print (int index);
    
    /* Polls the pot and updates the target flow. */
    void Update (int index);
    
    /* Updates the float rate. */
    bool CheckIfDoneWatering (int index);
    
    /* Opens the solenoid valve. */
    void OpenValve ();
    
    /* Closes the solenoid valve. */
    void CloseValve ();
    
    private:
    
    InterruptIn sensor;           //< The flow sensor pin.
    DigitalOut valve;             //< The solenoid valve pin.
    AnalogIn pot;                 //< The potentiometer pin.
    
    volatile uint16_t last_count, //< The previous saved count.
        count;                    //< Flow sensor pulse count.
    
    uint16_t pulse_target;        //< The terget pulse count.
    
    /* Calculates the pulse target value from the pot value. */
    inline uint16_t CalcPulseTarget ();
};

}   //< namespace sickbay
