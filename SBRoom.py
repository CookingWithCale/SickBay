# !/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBRoom.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>. """

from COut import COut
from SBNode import SBNode

# A Room in real life you put put SBNodes into.
# Example
# ```BASH
# ><.Intake DoeJohn1 Name="John Doe 1"
# ><.ICU.Intake Name="John Doe 2"
# ><.Devices.Ventilators.GHVentilator.GHVA
# ><.Devices.GHVA.GHVA1.Move 0.*.DoeJohn1
# ```
class SBRoom(SBNode):
  
  def __init__(self, SickBay, Command = ""):
    SBNode.__init__(self, "Room", SickBay.RIDNext(), SickBay, Command)
    self.Meta["Directions"] = ""
    SickBay.RIDNext()

  def Directions(self):
    return self.Meta["Directions"]
  
  def DirectionsSet(self, Directions):
    self.Add("Directions", Directions)
  
  def Command(self, SickBay, Command = ""):
    Result = SBNode.CommandSuper(self, SickBay, Command)
    if Result == None:
      return Result
    return ""