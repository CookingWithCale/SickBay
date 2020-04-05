#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/sickbay.git
# @file    /SBDeviceHumanMonitorBloodPressure.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBDevice import *

# A SickBay Device.
class SBDeviceMonitorHumanBloodPressure(SBDevice):
  
  def __init__(self, SickBay, Command = None, Type = "Device.Monitor.Human.BloodPressure"):
    SBDevice.__init__(self, SickBay, Command, Type)
