#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBRoom.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>. """

from SBNode import SBNode

# A Room in real life you put put SBNodes into.
class SBRoom(SBNode):
  
  def __init__(self, SickBay, Command = ""):
    SBNode.__init__(self, SickBay, Command)
    self.Members["Directions"] = ""
    SickBay.RoomCountNext()

  def Directions(self):
    return self.Members["Directions"]
  
  def DirectionsSet(self, Directions):
    self.Add("Directions", Directions)
  
  def Command(self, SickBay, Command):
    Key = Command.split(".", 1)
    if len(Key) != 3 and " " not in Key[1]:
      pass
