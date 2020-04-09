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
    PinName FlowSensorPin, PinName SolenoidValvePin,
    PinName ServoPin, I2C& Bus, char BusAddress) :
    Ticks                (0),
    TicksExhale          (2),
    TicksInhale          (1),
    TicksPEEP            (0),
    TicksFlowLast        (0),
    TicksFlow            (0),
    Atmosphere           (Bus, BusAddress),
    Temperature          (Atmosphere.Temperature()),
    TemperatureReference (Temperature),
    Pressure             (Atmosphere.Pressure()),
    PressureReference    (PressureReference),
    PulseOximeter        (PulseOximeterPin),
    FlowSensor           (FlowSensorPin),
    Valve                (SolenoidValvePin),
    Servo                (ServoPin),
    ServoClosed          (0),
    ServoOpen            (0) {
    FlowSensor.rise(callback(this, &GHVentilatorChannel::TickFlow));
}

GHVentilatorChannel* GHVentilatorChannel::This() { return this; }

void GHVentilatorChannel::TurnOff () {
  Valve = 0;
  Ticks = 0;
}

void GHVentilatorChannel::TicksPEEPSet (int NewTicksPEEP, int TicksSecond) {
  TicksPEEP = NewTicksPEEP;
  if (Ticks < TicksExhale) Inhale ();
}

void GHVentilatorChannel::TicksInhaleExhaleSet (int NewTicksInhale, 
                                               int NewTicksExhale) {
  int Tick = Ticks;
  if (Tick == 0) {
    TicksInhale = NewTicksInhale;
    TicksExhale = NewTicksExhale;
  }
  TicksInhale = NewTicksInhale;
  TicksExhale = NewTicksExhale;
  if (Tick < 0) { // We're exhaling.
    if (Ticks > NewTicksExhale) {
        Ticks = NewTicksExhale;
        Inhale ();
    }
  }
  else if (Tick > 0) { // We're inhaling.
    if (Ticks > NewTicksInhale) {
        Ticks = NewTicksInhale;
        Exhale ();
    }
    
    return;
  }
}

void GHVentilatorChannel::Poll () {
  Pressure = Atmosphere.Pressure();
  Temperature = Atmosphere.Temperature ();
}

void GHVentilatorChannel::TickFlow () {
  ++TicksFlow;
}

void GHVentilatorChannel::Inhale () {
  Pressure = this->Pressure;
  if (Ticks < TicksExhale) { // We're in the PEEP state.
    if (Pressure > PressureReference) {
      DPrintf ("\n  ? Over pressure; entering PEEP state. <");
      if (Ticks < TicksExhale - TicksPEEP) Inhale ();
      return;
    }
    DPrintf ("\n  ? Exiting PEEP state. <");
  }
  DPrintf ("\n  ? Inhaling. <");
  Ticks = StateInhaling;
  Valve = 0;
}

void GHVentilatorChannel::Exhale () {
  DPrintf ("\n  ? Exhaling. <");
  Ticks = StateExhaling;
  Valve = 1;
  PrintLine ();
  TicksFlowLast = TicksFlow;
}

void GHVentilatorChannel::Tare (float PressureHysteresis) {
  PressureReference = Atmosphere.Pressure () * PressureHysteresis;
  TemperatureReference = Atmosphere.Temperature ();
}

int GHVentilatorChannel::Monitor () {
  return Ticks;
}

void GHVentilatorChannel::Update() {
  int Tick = Ticks;
  if (Tick < 0)
    if (--Tick < TicksExhale) {
      Ticks = Tick;
      Inhale ();
    }
  else if (Tick > 0)
    if (++Tick > TicksInhale) Exhale ();
  else return;
  Ticks = Tick;
}

}   //< namespace SickBay
