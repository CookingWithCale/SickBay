#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBHumanPatient.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from HumanPatient import SB

class SBHumanPatient(SBNode):
  
  def __init__(self, SickBay, Type = "HumanPatient", Command = ""):
    SBNode.__init__(self, SickBay, Type, SickBay.ProcessCountNext(), Command)
