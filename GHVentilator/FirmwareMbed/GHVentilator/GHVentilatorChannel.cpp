/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /GHVentilatorChannel.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#include "GHVentilatorChannel.h"

#if _DebugSickBay
static const float HoursBetweenWateringTimes = 0.0020;   //f;  //< This is 3.6 seconds.
#else
static const float HoursBetweenWateringTimes = 0.5f;   //0.0015f;  //< This is 3.6 seconds.
#endif

enum {
  MaxLitersPerCycle = 4,      //< The max amount of liters per cycle
  PulsesPerLiter = 450,       //< The number of flow sensor pulses per liter.
  MaxPulsesPerCycle = MaxLitersPerCycle * PulsesPerLiter,
}
#include <mbedbug.h>
using namespace mbedBug;
Ticker UpdateTicker;

static volatile int SecondCount = 0;

namespace SickBay {


GHVentilatorChannel::GHVentilatorChannel (PinName SensorPin, 
    AnalogIn PulseOximeterPin, PinName SolenoidValvePin, PinName Status, 
    PinName Servo)
:   DutyCycle     (0.0f),
    Period        (0.0f),
    PulseTarget   (0),
    Sensor        (SensorPin),
    Valve         (SolenoidValvePin),
    PulseOximeter (PulseOximeterPin),
    CountLast     (0),
    TicksFlow    (0),
    PulseTarget   (CalcPulseTarget ()) {
    Sensor.rise(callback(this, &GHVentilatorChannel::PulseFlowSensor));
    
}

GHVentilatorChanel* GHVentilatorChanel::This(){ return this; }

void GHVentilatorChannel::PulseFlowSensor () {
  ++TicksFlow;
}

void GHVentilatorChannel::Inhale () {
  D_PRINTF ("\n? Checking PEEP. <");
  float Pressure = Atmosphere.Pressure();
  if (Pressure > ReferencePressure) {
    D_PRINTF ("\n? Over pressure. <");
  }
  D_PRINTF ("\n? Inhaling. <");
  Ticks = (Tick >= TicksExhale) ? Ticks : 0;
  Ticks = 0;
  Valve = 1;
}

void GHVentilatorChannel::Exhale () {
    D_PRINTF ("? Exhaling. <");
    Ticks = 0;
    Valve = 0;
    PrintLine ();
}

void GHVentilatorChannel::Tare () {
  ReferencePressure = Atmosphere.Pressure ()
  ReferenceTemperature = Atmosphere.Temperature ()
}

void GHVentilatorChannel::Update() {
  auto Tick = ++Ticks;
  if (Tick > TicksExhale) Inhale ();
  else if (Tick > TicksInhale) Exhale ();
}

}   //< namespace SickBay
