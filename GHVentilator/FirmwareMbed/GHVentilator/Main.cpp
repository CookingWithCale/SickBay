/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /Main.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#define GHVDebug     1   //< Set to 0 or 1 to enable or disable debugging.

#include <mbedBug.h>
 
#include "GHVentilator.h"
using namespace SickBay;

int main () {
  I2C I2CBus(A4, A5);
                  // + ------------------------ Number of updates per second.
                  // v
  GHVentilator GHV (250, I2CBus, address,
                      // +------------------------- Updates per second.
                      // |    +-------------------- Flow sensor interrupt pin.
                      // |    |   +---------------- Pulse oximiter pin.
                      // |    |   |   +------------ Solenoid Vavle.
                      // |    |   |   |   +-------- Status LED/Alarm.
                      // |    |   |   |   |    +--- PWM Servo
                      // v    v   v   v   v    v
    GHVentilatorChannel (200, D0, A0, D4, D8,  D12).This(),
    GHVentilatorChannel (200, D1, A1, D5, D9,  D13).This(),
    GHVentilatorChannel (200, D2, A2, D6, D10, D14).This(),
    GHVentilatorChannel (200, D3, A3, D7, D11, D15).This())
  );
}
