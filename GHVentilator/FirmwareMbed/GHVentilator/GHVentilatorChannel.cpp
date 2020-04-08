/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /GHVentilatorChannel.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#include "GHVentilatorChannel.h"

#include <mbedBug.h>
using namespace mbedBug;

namespace SickBay {

GHVentilatorChannel::GHVentilatorChannel (PinName PulseOximeterPin, 
    PinName FlowSensorPin, PinName SolenoidValvePin, PinName StatusPin, 
    PinName ServoPin, I2C& AtmosphereBus, char AtmosphereAddress) :
    Ticks                (0),
    TicksExhale          (2),
    TicksInhale          (1),
    TicksFlowInhale      (0),
    TicksFlowLast        (0),
    TicksFlow            (0),
    Atmosphere           (AtmosphereBus, AtmosphereAddress),
    PulseOximeter        (PulseOximeterPin),
    FlowSensor           (FlowSensorPin),
    Valve                (SolenoidValvePin),
    Status               (StatusPin),
    Servo                (ServoPin),
    ServoClosed          (0),
    ServoOpen            (0) {
    FlowSensor.rise(callback(this, &GHVentilatorChannel::PulseFlowSensor));
}

GHVentilatorChannel* GHVentilatorChannel::This() { return this; }

void GHVentilatorChannel::TicksInhaleExhaleSet (int NewTicksInhale, 
                                               int NewTicksExhale) {
  int Tick = Ticks;
  if (Tick == 0) {
    TicksInhale = NewTicksInhale;
    TicksExhale = NewTicksExhale;
  }
  TicksInhale = NewTicksInhale;
  TicksExhale = NewTicksExhale;
  if (Tick > 0) { // We're inhaling.
    if (Ticks > NewTicksInhale) {
        Ticks = NewTicksInhale;
        Exhale ();
    }
    
    return;
  }
  if (Tick < 0) { // We're exhaling.
    if (Ticks > NewTicksExhale) {
        Ticks = NewTicksExhale;
        Inhale ();
    }
  }
}

void GHVentilatorChannel::PulseFlowSensor () {
  ++TicksFlow;
}

void GHVentilatorChannel::Inhale () {
  DPrintf ("\n? Checking PEEP. <");
  float Pressure = Atmosphere.Pressure();
  if (Pressure > PressureReference) {
    DPrintf ("\n? Over pressure. <");
    return;
  }
  DPrintf ("\n? Inhaling. <");
  int Tick = Ticks;
  Ticks = (Tick >= TicksExhale) ? Tick : 0;
  Ticks = 1;
  Valve = 1;
}

void GHVentilatorChannel::HandleError () {
  DPrintf ("> Error <");
  Status = 0;
}

void GHVentilatorChannel::Exhale () {
  DPrintf ("\n? Exhaling. <");
  Ticks = -1;
  Valve = 0;
  PrintLine ();
  int TicksInhaleLast = TicksFlowInhale;
  if (TicksInhale < TicksInhaleLast >> 1) {
    DPrintf ("\n? The air flow has been cut in half! <");
    HandleError();
  }
}

void GHVentilatorChannel::Tare (float HysteresisPatient) {
  PressureReference = Atmosphere.Pressure () + 
                      HysteresisPatient;
  TemperatureReference = Atmosphere.Temperature ();
}

void GHVentilatorChannel::Update() {
  int Tick = Ticks;
  if (Tick < 0)
    if (--Tick < TicksExhale) Inhale ();
  else if (Tick > 0)
    if (++Tick > TicksInhale) Exhale ();
  else return;
  Ticks = Tick;
}

}   //< namespace SickBay
