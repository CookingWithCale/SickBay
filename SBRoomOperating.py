# !/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBRoomOperating.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBRoom import SBRoom

# A SickBay Operating Room to that performs a Bang when popped.
class SBRoomOperating(SBRoom):
  
  def __init__(self, SickBay, Command = None, Type="Room.Operating"):
    SBRoom.__init__(self, SickBay, Command, Type)

  def Pop(self, SickBay, Command = ""):
    Bang = SBNode.Bang(self,SickBay)
    SBRoom.Pop(self, SickBay, Bang + Command)
