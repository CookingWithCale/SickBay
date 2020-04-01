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
#import sched, time

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
    SBNode.Add(self, SBRoom(self, "WR", "Waiting Room", "The ER Waiting Room."))
    SBNode.Add(self, SBRoom(self, "ERI", "Emergency Room Intake", "The Room where you wait get get into the ER."))
    SBNode.Add(self, SBRoom(self, "ER", "Emergency Room", "The room with Patients who may need critical care."))
    SBNode.Add(self, SBRoom(self, "ICU", "Intensive Care Unit", "The room for Patients in need of critical care."))
    SBNode.Add(self, SBRoom(self, "Room", "Patient Rooms", "The Rooms where the Patients are in who aren't in the ER or ICU."))
    SBNode.Add(self, SBRoom(self, "Guests", "Guest Room", "The Room where guests start out in."))
    SBNode.Add(self, SBRoom(self, "Staff", "Staff Room", "The Room where all the Staff start out in."))
    SBNode.Add(self, SBRoom(self, "Storage", "Storage Room.", "The Room where all of the unused devices are stored in."))
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
    print ("\n\nWelcome to SickBay.\n\nEnter \"?\" at any time to get help.\n")
    while True:
      UserInput = raw_input("\n> ").lower()
      print (self.Top.Command(self, UserInput))
      
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

  # Handler for the init app state.
  def SetupTest (self):
    self.Print()
    print ("\n\nAdding test patients.")
    
    WR = SBNode.Get(self, "WR")
    WR.NodesAdd (SBHuman(self.NIDNext(), "John Doe 1", "M", 170.0, 70.0))
    WR.NodesAdd (SBHuman(self.NIDNext(), "John Doe 2", "M", 180.0, 75.0))
    WR.NodesAdd (SBHuman(self.NIDNext(), "John Doe 3", "M", 190.0, 80.0))
    WR.NodesAdd (SBHuman(self.NIDNext(), "John Doe 4", "M", 200.0, 85.0))
    WR.NodesAdd (SBHuman(self.NIDNext(), "Jane Doe 1", "F", 120.0, 55.0))
    WR.NodesAdd (SBHuman(self.NIDNext(), "Jane Doe 2", "F", 130.0, 60.0))
    WR.NodesAdd (SBHuman(self.NIDNext(), "Jane Doe 3", "F", 140.0, 65.0))
    WR.NodesAdd (SBHuman(self.NIDNext(), "Jane Doe 4", "F", 150.0, 70.0))
    WR.NodesAdd (GHVentilator(self.NIDNext()))
  
  # Handler for the Monitor app state.
  def StateMonitorHandle(self):
    for Patient in self.Patients:
      Patient.PrintStats()
  
  def StateShutDownHandle(self):
    print ("\n\nShutting down...")
    
  # Prints the most current and important stats to the Console.
  def PrintStats(self):
    for N in self.Nodes:
      N.PrintStats()
 
  # Function that is called every x seconds to update everything.
  def Update(self):
    #print ("\n\nUpdate Time:", time.time())
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
