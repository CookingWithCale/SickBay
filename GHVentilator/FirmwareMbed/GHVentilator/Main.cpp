/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /Main.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#define GHVDebug     1   //< Set to 0 or 1 to enable or disable debugging.

#include "GHVentilator.h"
using namespace SickBay;

int main () {
  int UpdatesPerSecond = 250;
  I2C I2CBus(A4, A5);
  GHVentilator GHV (UpdatesPerSecond, UpdatesPerSecond * 10, 
                    I2CBus, address, 0.25f, //<---- Pressure chamber hysteresis.
                      // +------------------------- Updates per second.
                      // |    +-------------------- Pulse oximiter pin.
                      // |    |   +---------------- Flow sensor interrupt pin.
                      // |    |   |   +------------ Solenoid Vavle.
                      // |    |   |   |   +-------- Status LED/Alarm.
                      // |    |   |   |   |    +--- PWM Servo
                      // v    v   v   v   v    v
    GHVentilatorChannel (200, A0, D0, D4, D8,  D12).This(),
    GHVentilatorChannel (200, A1, D1, D5, D9,  D13).This(),
    GHVentilatorChannel (200, A2, D2, D6, D10, D14).This(),
    GHVentilatorChannel (200, A3, D3, D7, D11, D15).This())
  );
}
