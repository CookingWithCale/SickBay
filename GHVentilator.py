#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /GHVentilator.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBVentilator import SBVentilator

class GHVentilator(SBVentilator):
  def __init__(self, SickBay, Arguments = ""):
    SBVentilator.__init__(self, SickBay, "DeviceVentilatorGH", Arguments)
    self.Members["BreathDutyCycle"] = 0.5   #< The breath duty cycle where 0.5 is 50% duty cycle.
    self.Members["BreathPeriod"] = 2.0      #< The breath period in seconds.
    self.Members["TidalCurrent"] = 0.0      #< The tidal air current.
