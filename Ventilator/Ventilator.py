"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /Ventilator/Ventilator.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

import GHVentilator

# The minimum breath 1-to-1 duty cycle.
VentilatorBreathDutyCycleMin = 1.0 / (2.0 * 1.0)

# The minimum breath 1-to-1 duty cycle.
VentilatorBreathDutyCycleMin = 1.0 / (2.0 * 3.0)

# The minimum breath 1-to-1 duty cycle.
VentilatorBreathPeriod = 0.0

# The minimum breath 1-to-1 duty cycle.
VentilatorBreathDutyCycleMin = 1.0 / (2.0 * 3.0)

class Ventilator:
  Type = ""               #< The type of Ventilator
  BreathDutyCycle = 0.5   #< The breath duty cycle where 0.5 is 50% duty cycle.
  BreathPeriod = 2.0      #< The breath period in seconds.
  TidalCurrent = 0.0      #< The tidal air current.

  def __init__():
    self.data = []
  
  def BreathDutyCycleSet(BreathDutyCycle)
    if (BreathDutyCycle >= BreathDutyCycleMin and
        BreathDutyCycle <= BreathDutyCycleMax):
        self.BreathDutyCycle = BreathDutyCycle
  
  def BreathPeriodSet(BreathPeriod):
    if (BreathPeriod >= BreathPeriodMin and
        BreathPeriod <= BreathPeriodMax):
        self.BreathPeriod = BreathPeriod
