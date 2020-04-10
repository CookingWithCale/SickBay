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

GHVentilatorChannel::GHVentilatorChannel () :
    Ticks         (0),
    TicksInhale   (0),
    TicksExhale   (0),
    PulseOximeter (0),
    Servo         (0),
    ServoClosed   (0),
    ServoOpen     (1) {}

void GHVentilatorChannel::Init (GHVentilator* Parent, int TicksInhale, 
                                int TicksExhale, float PressureHysteresis) {
  this->Parent             = Parent;
  this->TicksInhale        = TicksInhale;
  this->TicksExhale        = TicksExhale;
  this->PressureHysteresis = Pressure * PressureHysteresis;
}

GHVentilatorChannel* GHVentilatorChannel::This() { return this; }

void GHVentilatorChannel::TurnOff () {
  Parent->ChannelValveSet(this, LLLow);
  Ticks = 0;
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

void GHVentilatorChannel::TickFlow () {
  ++TicksFlow;
}

void GHVentilatorChannel::Inhale () {
  DPrintf ("\n  ? Inhaling. <");
  Ticks = StateInhaling;
  Parent->ChannelValveSet(this, LLHigh);
}

void GHVentilatorChannel::Exhale () {
  DPrintf ("\n  ? Exhaling. <");
  Ticks = StateExhaling;
  Parent->ChannelValveSet(this, LLLow);
  TicksFlowLast = TicksFlow;
}

}   //< namespace SickBay
