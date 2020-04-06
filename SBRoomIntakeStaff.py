#!/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /SBRoomStaff.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBRoom import *

# An HumanStaff factory Room
class SBRoomIntakeStaff(SBRoom):
  
  def __init__(self, Crabs, Type = "Room.Intake.Staff"):
    SBNode.__init__(self, Crabs, Type)
  
  def PushDuck(self, Crabs, Key, Command):
    Children = SBNode.Chidren
    Child = SBHumanStaff(Crabs, Type)
    Children[Key] = Child
    return None
