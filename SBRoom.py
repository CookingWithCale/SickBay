# !/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /SBRoom.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>. """

from Stringf import *
from SBNode import *

# A Room in real life you put put SBNodes into.
# Example
# ```BASH
# ><.Intake DoeJohn1 Name="John Doe 1"
# ><.ICU.Intake Name="John Doe 2"
# ><.Devices.Ventilators.GHVentilator.GHVA
# ><.Devices.GHVA.GHVA1.Move 0.*.DoeJohn1
# ```
class SBRoom(SBNode):
  
  # Constructs a Duck 
  def __init__(self, Crabs, Type ="Room"):
    SBNode.__init__(self, Crabs, Crabs.RIDNext (), Type)
    self.Meta["Directions"] = ""

  def Directions(self):
    return self.Meta["Directions"]
  
  def DirectionsSet(self, Directions):
    self.Add("Directions", Directions)
  
  def Command(self, Crabs, Command = None, Cursor = 0):
    Result = SBNode.CommandSuper(self, Crabs, Command, Cursor)
    if Result == None:
      return Result
    return ""
  