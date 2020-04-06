#!/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /SBDeviceMbedSerial.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBDevice import *
from mbedRPC import *
import serial

# An Mbed device controlled via a Serial Port.
# Windows code
# serdev = 15

# Mac code
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
class SBDeviceMbedSerial(SBNode):
  
  # Creates a Duck.
  def __init__(self, Crabs, TID, Type = "Device.Mbed.Serial"):
    SBDevice.__init__(self, Crabs, TID, Type)
    self.Meta["Port"] = 15
    pass
  
  def RW(self):
    s = serial.Serial(serdev)
    s.write("hello")
    s.close()
