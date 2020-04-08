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
  int Address = BMP280SlaveAddressDefault;
  GHVentilator GHV (UpdatesPerSecond, 
                    UpdatesPerSecond * 10, //<-- Calibration tick count.
                    I2CBus, Address, 
                    0.25f, //<------------------ Pressure chamber hysteresis %.
                    0.01f, // <----------------- Patient pressure hysteresis,
                    D0,    // <----------------- Blower pin.
                    D1,    // <----------------- Status pin.
                      // +---------------------- Pulse oximiter pin.
                      // |   +------------------ Flow sensor interrupt pin.
                      // |   |    +------------- Solenoid Vavle.
                      // |   |    |    +-------- Status LED/Alarm.
                      // |   |    |    |    +--- PWM Servo
                      // v   v    v    v    v
    GHVentilatorChannel (A0, D3,  D4,  D5,  D6,  I2CBus,Address+1).This(),
    GHVentilatorChannel (A1, D7,  D8,  D9,  D10, I2CBus,Address+2).This(),
    GHVentilatorChannel (A2, D11, D12, D13, D14, I2CBus,Address+3).This(),
    GHVentilatorChannel (A3, D15, PC_8, PC_6, PC_5, I2CBus,Address+4).This()
  );
}
