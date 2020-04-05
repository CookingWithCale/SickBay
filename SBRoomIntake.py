#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/sickbay.git
# @file    /SBRoomIntake.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>. """

from SBRoom import SBRoom

# A Room in real life you put put SBNodes into.
class SBRoomIntake(SBRoom):
  
  def __init__(self, SickBay, Command = None, Type="Room.Intake"):
    SBNode.__init__(self, SickBay, Type, Command)
  
  def Command(self, SickBay, Command):
    Result = self.CommandSuper(SickBay, Command)
    if Result == None: return Result
    while Result[0] == '>':
      Result = self.CommandSuper(SickBay, Command)
      if Result == None: return Result

    Patient = SBPatient(self)
    if not SBSickBay.IsValidKey(Key):
      return
    Child = SBHuman(SickBay, Arguments)
    self.Children.Add(Child)
  
  