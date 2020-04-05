#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBDeviceMbedHTTP.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBDevice import *
from mbedRPC import *

# A SickBay Device.
class SBDeviceMbedHTTP(SBNode):
  
  def __init__(self, SickBay, Command = "", Type = "Device"):
    SBNode.__init__(self, SickBay, Command, Type)
  
  def Connect(self, IPAddress):
    mbed = HTTPRPC(IPAddress)
  
  def RS(self):
    x = DigitalOut(mbed, "led1")   # pass in the name of that object you wish to write to
    x.write(1)
    x.read()
