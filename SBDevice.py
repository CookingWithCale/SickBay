#!/usr/bin/python
# -*- coding: utf-8 -*-
"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /SBDevice.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

from SBNode import SBNode

# A SickBay Device.
class SBDevice(SBNode):
  
  def __init__(self, SickBay, Handle = "", Name = "", Description = "", Help = ""):
    SBNode.__init__(self, SickBay, Handle, "Device", Name, Description, Help)
    pass
  