/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /GHVentilatorConfig.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <cstdint>
#include <mbed.h>
namespace SickBay {

enum {
  PulseOximeterNoiseThreshold = 350, //< Noise threshold of the ADC input.
  PulseOximeterRangeMin = 30000,     //< The min ADC input reading.
  PulseOximeterRangeMax = 0xffff,     //< The max ADC input reading.
  PulseOximeterRange = (PulseOximeterRangeMax - PulseOximeterRangeMin),
  // The seconds between each cycle.
};

}   //< sickbay
