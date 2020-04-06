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

class SBRoomIntakePatient(SBRoom):
  
  # Creates a Duck.
  def __init__(self, Crabs, Type = "Room.Intake.Patient"):
    SBNode.__init__(self, Crabs, Type)
  
  # Adds a new child Duck.
  def PushDuck(self, Crabs, Key, Command):
    Child = SBHumanPatient(Crabs)
