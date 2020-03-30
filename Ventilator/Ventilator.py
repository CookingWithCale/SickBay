"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /Ventilator/Ventilator.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

import SickBayDevice
import GHVentilator

class Ventilator(SickBayDevice):
  # Constants
  # The minimum breath 1-to-1 duty cycle.
  BreathDutyCycleMin = 1.0 / (2.0 * 1.0)
  # The minimum breath 1-to-1 duty cycle.
  BreathDutyCycleMax = 1.0 / (2.0 * 3.0)
  # The minimum breath 1-to-1 duty cycle.
  BreathPeriodMin = 0.0
  # The minimum breath period of 10.0 seconds.
  BreathPeriodMax = 10.0
    
  def __init__(self):
    self.Type = ""               #< The type of Ventilator
    self.BreathDutyCycle = 0.5   #< The breath duty cycle where 0.5 is 50% duty cycle.
    self.BreathPeriod = 2.0      #< The breath period in seconds.
    self.TidalCurrent = 0.0      #< The tidal air current.
  
  def BreathDutyCycleSet(self, BreathDutyCycle):
    if (BreathDutyCycle >= self.BreathDutyCycleMin and
        BreathDutyCycle <= self.BreathDutyCycleMax):
      self.BreathDutyCycle = BreathDutyCycle
  
  def BreathPeriodSet(self, BreathPeriod):
    if (BreathPeriod >= self.BreathPeriodMin and
        BreathPeriod <= self.BreathPeriodMax):
      self.BreathPeriod = BreathPeriod
    
  def PrintStats(self):
    print("\nOK")
