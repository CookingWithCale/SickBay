/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /ghv_config.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2029 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <cstdint>
#include <mbed.h>
namespace sickbay {
#if _DebugSickBay
static const float cHoursBetweenWateringTimes = 0.0020;   //f;  //< This is 3.6 seconds.
#else
static const float cHoursBetweenWateringTimes = 0.5f;   //0.0015f;  //< This is 3.6 seconds.
#endif

enum {
  cChannelCount = 4,            //< The number of water channels.
  cMaxLitersPerCycle = 4,      //< The max amount of liters per cycle
  cPulsesPerLiter = 450,       //< The number of flow sensor pulses per liter.
  cMaxPulsesPerCycle = cMaxLitersPerCycle * cPulsesPerLiter,
  cPotNoiseThreshold = 350,    //< Adjust noise threshold of the ADC inputs.
  cMinPotReading = 30000,      //< The min ADC input reading.
  cMaxPotReading = 0xffff,     //< The max ADC input reading (64K on mbed)
  cPotADCRange = (cMaxPotReading - cMinPotReading),
  // The seconds between each cycle.    
  cCycleTimeSeconds = (int)(cHoursBetweenWateringTimes * 60.0f * 60.0f),
};

}   //< sickbay
