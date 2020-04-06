# !/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /SickBay.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>. Process
 
from SBCrabs import *
  
# The SickBay root.
class SickBay(SBCrabs):
  
  def __init__(self, Command = None):
    SBCrabs.__init__(self)
    self.Meta["Name"] = "Crabs"
    self.Meta["Description"] ="Crabs Node with NID 0."
    N = SBRoomIntakePatient(self)
    N.Meta["Name"] = "Patient Intake"
    N.Meta["Description"] = "The Intake Room where you wait get get into the Hospital."
    self.Add(self, "Intake", N)
    self.Add(self, "Staff", SBRoomIntakeStaff(self), 
             '"Name="Staff Room" Description="The Room where all the Staff start out in."') 
    self.Add(self, "ER", SBRoom(self),
             'Name="Emergency Room" Description="The room with Patients who may need critical care."')
    self.Add(self, "ICU", SBRoom(self),
             'Name="Intensive Care Unit" Description="The room for Patients in need of critical care."')
    self.Add(self, "Rooms", SBRoom(self),
             '"Name="Patient Rooms" Description="The Rooms where the Patients are in who aren\'t in the ER or ICU."')
    self.Add(self, "Guests", SBRoom(self),
             '"Name="Guest Room" Description="The Room where guests start out in."')
    self.Add(self, "Devices", SBRoom(self), 
             '"Name="Device Room" Description="The Room where all of the unused devices are stored in."')
    self.Test()
    self.ConsoleMain()
  
  def Test(self):
    SBCrabs.Test(self)
    self.COut ('> SickBay Test')
    self.Do("Intake > ?")
    self.COut ('\n<')
  
if __name__ == '__main__':
  SickBay = SickBay()
