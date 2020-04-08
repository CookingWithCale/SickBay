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

void UpdateHandler() {
}

GHVentilatorChannel::GHVentilatorChannel (PinName SensorPin, 
    AnalogIn PulseOximeterPin, PinName SolenoidValvePin, PinName Status, 
    PinName Servo) :
    Ticks         (0),
    TicksInhale   (1),
    TicksExhale   (2),
    TicksFlowLast (0),
    TicksFlow     (0),
    TicksFlowInhale (0),
    ReferencePressure (Atmosphere.Pressure()),
    ReferenceTemperature (Atmosphere.Temperature()),
    ServoClosed   (0),
    ServoOpen     (0),
    Sensor        (SensorPin),
    Valve         (SolenoidValvePin),
    PulseOximeter (PulseOximeterPin),
    CountLast     (0),
    TicksFlow     (0),
    PulseTarget   (CalcPulseTarget ()) {
    Tare ();
    Sensor.rise(callback(this, &GHVentilatorChannel::PulseFlowSensor));
}

GHVentilatorChanel* GHVentilatorChanel::This(){ return this; }

void GHVentilatorChanel::TicksInhaleExhaleSet (int NewTicksInhale, 
                                               int NewTicksExhale) {
  Tick = Ticks;
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
  if (Pressure > ReferencePressure) {
    DPrintf ("\n? Over pressure. <");
    return;
  }
  DPrintf ("\n? Inhaling. <");
  Ticks = (Tick >= TicksExhale) ? Ticks : 0;
  Ticks = 1;
  Valve = 1;
}

void GHVentilator::HandleError () {
  Status = 0
}

void GHVentilatorChannel::Exhale () {
  DPrintf ("\n? Exhaling. <");
  Ticks = -1;
  Valve = 0;
  PrintLine ();
  TicksInhaleLast = TicksFlowInhale;
  if (TicksInHale < TicksInhaleLast >> 1) {
    DPrintf ("\n? The air flow has been cut in half! <");
    HandleError();
  }
}

void GHVentilatorChannel::Tare () {
  ReferencePressure = Atmosphere.Pressure () + 
                      GHVentilatorPressureHysteresis
  ReferenceTemperature = Atmosphere.Temperature () + 
                         GHVentilatorTemperatureHysteresis
}

void GHVentilatorChannel::Update() {
  int Tick = Ticks;
  if (Tick < 0)
    if (--Tick < TicksExhale) Inhale (Tick);
  else if (Tick > 0)
    if (++Tick > TicksInhale) Exhale (Tick); ++Tick;
  else return;
  Ticks = Tick;
}

}   //< namespace SickBay
