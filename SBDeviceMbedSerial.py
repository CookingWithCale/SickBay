#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBDeviceMbed.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBNode import SBNode
from mbedRPC import *
import serial

# A SickBay Device.
class SBDeviceMbedSerial(SBNode):
  
  def __init__(self, SickBay, Type = "DeviceMbedSerial", Command = ""):
    SBNode.__init__(self, SickBay, Type, SickBay.DeviceCountNext(), Command)
    pass
  
serdev = 15
s = serial.Serial(serdev)
s.write("hello")
s.close()
  def 

# import serial
# serdev = '/dev/tty.usbmodem1912'
# s = serial.Serial(serdev)
# s.write("hello")
# s.close()
# or when on a Linux/unix system (in this case /dev/ttyACM0):

# import serial
# serdev = '/dev/ttyACM0'
# s = serial.Serial(serdev)
# s.write("hello")
# s.close()