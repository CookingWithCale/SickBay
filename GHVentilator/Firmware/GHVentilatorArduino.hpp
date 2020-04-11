/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /SBVentilator/Firmware/SBVentilatorArduino.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SBVentilatorArduino
#define SBVentilatorArduino
#include "_KabukiTek.hpp"
#include "BMP280.hpp"
#include "SBVentilator.hpp"
#include <Wire.h>
namespace SickBay {

int GHVentilatorRun(){
  Wire Bus(A4, A5);
  char ChamberAddress = BMP280SlaveAddressDefault;
  return 0;
}
} //< namespace SickBay
#endif
