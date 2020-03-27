/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /ghv_channel.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2029 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include "ghv_channel.h"

#include <mbedBug.h>
using namespace mbedBug;

static volatile int secondCount = 0;

namespace sickbay {

GHVChannel::GHVChannel (PinName sensor_pin, PinName solenoid_valve_pin, 
    AnalogIn potPin)
:   sensor        (sensor_pin),
    valve         (solenoid_valve_pin),
    pot           (potPin),
    lastCount     (0),
    count         (0),
    pulse_target   (CalcPulseTarget ()) {
    sensor.rise(this, &GHVChannel::PulseFlowSensor);
    
}

int32_t ConvertGallonsToMillileters (float value) {
    return PulsesPerLiter * (int32_t)(value * 3785.41f);
}

int32_t GHVChannel::CalcTotalFlow_mL () {
    return (count * 1000) / PulsesPerLiter;
}

int32_t GHVChannel::CalcTargetFlow_mL () {
    return (pulse_target * 1000) / PulsesPerLiter;
}

int32_t GHVChannel::CalcFlowRate_mL () {
    return ((count - lastCount) * 1000) / PulsesPerLiter;
}

void GHVChannel::BreatheStart (int index) {
    lastCount = secondCount = count = 0;
     
    if (pulse_target == 0) {
        printf ("Cnannel %i is off.\r\n", index);
        return;
    }
    
    openValve ();
}

void GHVChannel::update (int index) {
    uint16_t value = CalcPulseTarget ();
            
    /// Check for pot noise and 
    if ((value < (pulse_target - cPotNoiseThreshold)) ||
        (value > (pulse_target + cPotNoiseThreshold))) {
        pulse_target = value;
    }
    
    if (pulse_target == 0) {
        printf ("Turning off channel %i\r\n", index);
        closeValve ();
        return;
    }
    
    printf ("| %2i | %3i | %16u | %15u | %16u |\r\n", index, secondCount, 
        CalcFlowRate_mL (), CalcTotalFlow_mL (), CalcTargetFlow_mL ());
    //printf ("- %8i - %16i - %15i - %16i -\r\n", value,
    //    count - lastCount, count, pulse_target);
}

bool GHVChannel::checkIfDoneWatering (int index) {
    ++secondCount;
    Update (index);
    
    /// Check if hit target flow yet.
    
    if (count >= pulse_target) {
        secondCount = 0;
        closeValve ();
        return true;
    }
    lastCount = count;
    return false;
}

void GHVChannel::PulseFlowSensor () {
    ++count;
}

void GHVChannel::OpenValve () {
    printf ("Opening valve.");
    valve = 1;
    
    PrintLine ();
    printf ("| Ch | sec | Flow Rate (mL/s) | Total Flow (ml) | Target Flow "
        "(ml) |\r\n");
}

void GHVChannel::CloseValve ()
{
    printf ("Closing valve.");
    valve = 0;
    PrintLine ();
}

uint16_t GHVChannel::CalcPulseTarget ()
{
    int32_t value = pot.read_u16 ();
    
    /// Update pot and target flow (note: using integer math to multiply by 
    /// number between 0.0 - 1.0.).
    ///
    /// |---- +Va
    /// |---- Max pot reading = Vmax
    /// |---- Pot ADC reading = Vpot
    /// |---- Min pot reading = Vmin
    /// |____ Ground
    ///
    /// 0.0 <= (Vpot - Vmin) / (Vmax - Vmin) <= 1.0
    ///
    
    value -= cMinPotReading;
    
    if (value < 0) value = 0;
    
    value = (value * cMaxPulsesPerCycle) / 
        cPotADCRange;
    
    return (uint16_t)value;
}

}   //< namespace sickbay
