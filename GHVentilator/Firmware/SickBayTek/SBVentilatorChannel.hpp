/** SickBay Tek @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /Devices/Tek/SBVentilatorChannel.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#include "SBVentilatorChannel.h"

namespace SickBay {

SBVentilatorChannel::SBVentilatorChannel () :
    Ticks         (0),
    TicksInhale   (0),
    TicksExhale   (0),
    PulseOximeter (0),
    Servo         (0),
    ServoClosed   (0),
    ServoOpen     (1) {}

void SBVentilatorChannel::Init (SBVentilator* Parent, int TicksInhale, 
                                int TicksExhale, float PressureHysteresis) {
  this->Parent             = Parent;
  this->TicksInhale        = TicksInhale;
  this->TicksExhale        = TicksExhale;
  this->PressureHysteresis = Pressure * PressureHysteresis;
}

SBVentilatorChannel* SBVentilatorChannel::This() { return this; }

void SBVentilatorChannel::TurnOff () {
  Parent->ChannelValveSet(this, LLLow);
  Ticks = 0;
}

void SBVentilatorChannel::TicksInhaleExhaleSet (int NewTicksInhale, 
                                                int NewTicksExhale) {
  int Tick = Ticks;
  if (Tick == 0) {
    TicksInhale = NewTicksInhale;
    TicksExhale = NewTicksExhale;
  }
  TicksInhale = NewTicksInhale;
  TicksExhale = NewTicksExhale;
  if (Tick < 0) { // StateExhaling.
    if (Ticks > NewTicksExhale) {
      Ticks = NewTicksExhale;
      Inhale ();
    }
  }
  else if (Tick > 0) { // StateInhaling.
    if (Ticks > NewTicksInhale) {
      Ticks = NewTicksInhale;
      Exhale ();
    }
    return;
  }
}

void SBVentilatorChannel::TickFlow () {
  ++TicksFlow;
}

void SBVentilatorChannel::Inhale () {
  DPrintf ("\n  ? Inhaling. <");
  Ticks = StateInhaling;
  Parent->ChannelValveSet(this, LLHigh);
}

void SBVentilatorChannel::Exhale () {
  DPrintf ("\n  ? Exhaling. <");
  Ticks = StateExhaling;
  Parent->ChannelValveSet(this, LLLow);
  TicksFlowLast = TicksFlow;
}

}   //< namespace SickBay
