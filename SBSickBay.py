#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBSickBay.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.
 
from SBNode import SBNode
from SBDevice import SBDevice
from SBHuman import SBHuman
from SBRoom import SBRoom
from SBVentilator import SBVentilator
from GHVentilator import GHVentilator
import sched, time, datetime, sys

#Scheduler = sched.scheduler(time.time, time.sleep)
  
# The SickBay app object.
class SBSickBay(SBNode):
  # Constants
  StateMonitoring = 1     #< State: Monitoring.
  StateShuttingDown = 2   #< State: Shutting down.
  NIDCount = 0            #< The total number of SBNodes.
  HelpString = (
    "\nSickBay is a tree and node system where you start out at in the root." +
    "\nTo list the contents of any SickBay Node type the word \"list\"." +
    "\nEach Node has a Node ID (NID), Type, Handle, Name, Description, and " +
    "\nHelp string. You can search through the nodes and their children by " +
    "\nTyping \"search name John\" will search for any node with John in the " +
    "\nName.")

  def __init__(self):
    self.Top = self                   #< The currently selected node.
    SBNode.__init__(self, self, "Device", "SickBay", "Root", "Root Node with NID 0.")
    self.Stack = []                   #< The stack of SBNodes.
    self.State = self.StateMonitoring #< The app state.
    self.Devices = []                 #< A list of Devices this SickBay supports.
    self.Add("WR", SBRoom(self, "Waiting Room", "The ER Waiting Room."))
    self.Add("ERI", SBRoom(self, "Emergency Room Intake", "The Room where you wait get get into the ER."))
    self.Add("ER", SBRoom(self, "Emergency Room", "The room with Patients who may need critical care."))
    self.Add("ICU", SBRoom(self, "Intensive Care Unit", "The room for Patients in need of critical care."))
    self.Add("Room", SBRoom(self, "Patient Rooms", "The Rooms where the Patients are in who aren't in the ER or ICU."))
    self.Add("Guests", SBRoom(self, "Guest Room", "The Room where guests start out in."))
    self.Add("Staff", SBRoom(self, "Staff Room", "The Room where all the Staff start out in."))
    self.Add("Storage", SBRoom(self, "Storage Room.", "The Room where all of the unused devices are stored in."))
    self.SetupTest()
    self.ConsoleMain()
  
  def NIDNext(self):
    Result = self.NIDCount
    self.NIDCount = Result + 1
    return Result

  # Add Device
  def DevicesAdd(self, DeviceName):
    self.Devices.append(DeviceName)

  # Console main loop.
  def ConsoleMain(self):
    sys.stdout.write ("\n\nWelcome to SickBay.\n\nEnter \"?\" at any time to get help " +
           "\nor press Enter on the keyboard to update the stats"
           "\nor type \"exit\" to exit the console.")
    while True:
      UserInput = raw_input("\n> ").lower()
      if UserInput == "exit":
        return
      if UserInput == "":
        self.PrintStats()
      sys.stdout.write (self.Top.Command(self, UserInput))
      
  # Pushes an SBNode onto the stack.
  def Push(self, Node):
    self.Stack.append(self.Top)
    self.Top = Node
  
  # Pops an SBNode off the stack.
  def Pop(self):
    if len(self.Stack) == 0:
      return
    self.Top = self.Stack.pop()
  
  # Enters the monitoring state.
  def MonitorBegin(self):
    #Scheduler.enter(1, 1, self.Update, ())
    #Scheduler.run()
    print("\n\nBeginning monitoring...")
  
  def Print(self):
    print("\nSickBay:")
    SBNode.Print(self)

  # Handler for the init app state.
  def SetupTest (self):
    self.Print()
    sys.stdout.write ("\n\nAdding test patients.")
    self.PushHandle(self, "WR")
    Top = self.Top
    Top.Print()
    Top.Add ("DoeJohn1", SBHuman(self, "John Doe 1", "M", 155.0, 70.0))
    Top.Add ("DoeJohn2", SBHuman(self, "John Doe 2", "M", 160.0, 75.0))
    Top.Add ("DoeJohn3", SBHuman(self, "John Doe 3", "M", 165.0, 80.0))
    Top.Add ("DoeJohn4", SBHuman(self, "John Doe 4", "M", 170.0, 85.0))
    Top.Add ("DoeJohn5", SBHuman(self, "John Doe 5", "M", 175.0, 90.0))
    Top.Add ("DoeJohn6", SBHuman(self, "John Doe 6", "M", 185.0, 95.0))
    Top.Add ("DoeJohn7", SBHuman(self, "John Doe 7", "M", 190.0, 100.0))
    Top.Add ("DoeJohn8", SBHuman(self, "John Doe 8", "M", 195.0, 105.0))
    Top.Add ("DoeJane1", SBHuman(self, "Jane Doe 1", "F", 120.0, 55.0))
    Top.Add ("DoeJane2", SBHuman(self, "Jane Doe 2", "F", 125.0, 60.0))
    Top.Add ("DoeJane3", SBHuman(self, "Jane Doe 3", "F", 130.0, 65.0))
    Top.Add ("DoeJane4", SBHuman(self, "Jane Doe 4", "F", 135.0, 70.0))
    Top.Add ("DoeJane5", SBHuman(self, "Jane Doe 5", "F", 140.0, 75.0))
    Top.Add ("DoeJane6", SBHuman(self, "Jane Doe 6", "F", 145.0, 80.0))
    Top.Add ("DoeJane7", SBHuman(self, "Jane Doe 7", "F", 150.0, 85.0))
    Top.Add ("DoeJane8", SBHuman(self, "Jane Doe 8", "F", 155.0, 90.0))
    Top.Add ("GHV1", GHVentilator(self, "Gravity Hookah Ventilator 1"))
    Top.Add ("GHV2", GHVentilator(self, "Gravity Hookah Ventilator 2"))
  
  # Handler for the Monitor app state.
  def StateMonitorHandle(self):
    for Child in self.Patients:
      Child.Children.PrintStats()
  
  def StateShutDownHandle(self):
    sys.stdout.write ("\n\nShutting down...")
    
  # Prints the most current and important stats to the Console.
  def PrintStats(self):
    sys.stdout.write ("\n\nTime: ")
    sys.stdout.write (str (datetime.datetime.now()))
    SBNode.PrintStats(self)
 
  # Function that is called every x seconds to update everything.
  def Update(self):
    #sys.stdout.write ("\n\nUpdate Time:", time.time())
    Handler = {
      1: self.StateMonitorHandle,
      2: self.StateShutDownHandle
    }
    # Get the function from switcher dictionary
    Handle = Handler.get(self.State, lambda: "Invalid state")
    # Execute the function
    Handle()
    self.PrintStats()
    #Scheduler.enter(1, 1, self.Update, ())

if __name__ == '__main__':
  SickBayConsole = SBSickBay()
  #unittest.main()
