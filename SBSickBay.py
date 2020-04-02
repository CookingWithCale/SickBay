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
from SBPrint import SBPrint
from SBVentilator import SBVentilator
from GHVentilator import GHVentilator
import sched, time, datetime

#Scheduler = sched.scheduler(time.time, time.sleep)
  
# The SickBay app object.
class SBSickBay(SBNode):
  # Constants
  StateMonitoring = 1     #< State: Monitoring.
  StateShuttingDown = 2   #< State: Shutting down.
  HelpString = (
    "\nSickBay is a tree and node system where you start out at in the root." +
    "\nTo list the contents of any SickBay Node type the word \"list\"." +
    "\nEach Node has a Node ID (NID), Type, Key, Name, Description, and " +
    "\nHelp string. You can search through the nodes and their children by " +
    "\nTyping \"search name John\" will search for any node with John in the " +
    "\nName.")

  def __init__(self):
    self.NIDCount = 0                 #< The total number of SBNodes.
    self.HeadCount = 0                #< The count of new Humans in the Room.
    self.DeviceCount = 0              #< The Device count
    self.RoomCount = 0                #< The Room count
    self.SearchCount = 0              #< The search count
    self.ProcedureCount = 0           #< The procedure count
    self.AppCount = 0                 #< The application count
    self.Top = self                   #< The currently selected node.
    self.Stack = []                   #< The stack of SBNodes.
    SBNode.__init__(self, self, "Type=\"SickBay\" Name=\"SickBay\" Description=\"Root Node with NID 0.\"")
    self.State = self.StateMonitoring #< The app state.
    self.Devices = []                 #< A list of Devices this SickBay supports.
    self.Add("Intake", SBRoom(self, "Name=\"Patient Intake\" Description=\"The Intake Room where you wait get get into the Hospital."))
    self.Add("ER", SBRoom(self, "Name=\"Emergency Room\" Description=\"The room with Patients who may need critical care."))
    self.Add("ICU", SBRoom(self, "Name=\"Intensive Care Unit\" Description=\"The room for Patients in need of critical care."))
    self.Add("Rooms", SBRoom(self, "Name=\"Patient Rooms\" Description=\"The Rooms where the Patients are in who aren't in the ER or ICU."))
    self.Add("Guests", SBRoom(self, "Name=\"Guest Room\" Description=\"The Room where guests start out in."))
    self.Add("Staff", SBRoom(self, "Name=\"Staff Room\" Description=\"The Room where all the Staff start out in."))
    self.Add("Devices", SBRoom(self, "Name=\"Device Room\" Description=\The Room where all of the unused devices are stored in."))
    self.SetupTest()
    self.ConsoleMain()
  
  # Checks if the given Key is valid.
  @staticmethod
  def IsValidKey(Key):
    if " " in Key or "." in Key:
      return False
    return True
  
  # Generates the next unique NID by incrementing NIDCount
  def NIDNext(self):
    Result = self.NIDCount
    self.NIDCount = Result + 1
    return Result
  
  # Generates the next unique Head Id by incrementing HeadCount
  def HeadCountNext(self):
    Result = self.NIDCount
    self.NIDCount = Result + 1
    return Result
  
  # Generates the next unique Device Id by incrementing DeviceCount
  def DeviceCountNext(self):
    Result = self.DeviceCount
    self.DeviceCount = Result + 1
    return Result
  
  # Generates the next unique Room Id by incrementing RoomCount
  def RoomCountNext(self):
    Result = self.RoomCount
    self.RoomCount = Result + 1
    return Result
  
  # Generates the next unique Search Id by incrementing SearchCount
  def SearchCountNext(self):
    Result = self.SearchCount
    self.SearchCount = Result + 1
    return Result
  
  # Generates the next unique Search Id by incrementing ProcedureCount
  def ProcedureCountNext(self):
    Result = self.ProcedureCount
    self.ProcedureCount = Result + 1
    return Result
  
  # Generates the next unique App Id by incrementing AppCount
  def AppCountNext(self):
    Result = self.AppCount
    self.AppCount = Result + 1
    return Result

  # Add Device
  def DevicesAdd(self, DeviceName):
    self.Devices.append(DeviceName)

  # Console main loop.
  def ConsoleMain(self):
    SBPrint.COut ("\n\nWelcome to SickBay.\n\nEnter \"?\" at any time to get help " +
           "\nor press Enter on the keyboard to update the stats"
           "\nor type \"exit\" to exit the console.\n")
    while True:
      self.Top.Path()
      UserInput = raw_input("> ").lower()
      if UserInput == "exit":
        return
      if UserInput == "":
        self.PrintStats()
      SBPrint.COut(self.Top.Path())
      SBPrint.COut(">")
      SBPrint.Print (self.Top.Command(self, UserInput))
      
  # Pushes an SBNode onto the stack.
  def Push(self, Node):
    Node.Push(self)
  
  # Pops an SBNode off the stack.
  def Pop(self):
    if len(self.Stack) == 0:
      return
    self.Top = self.Stack.pop()
  
  # Enters the monitoring state.
  def MonitorBegin(self):
    #Scheduler.enter(1, 1, self.Update, ())
    #Scheduler.run()
    SBPrint.COut("\n\nBeginning monitoring...")
  
  def Print(self):
    SBPrint.COut("\nSickBay:")
    SBNode.Print(self)

  # Handler for the init app state.
  def SetupTest (self):
    self.Print()
    SBPrint.COut ("\n\nAdding test patients...\n\n")
    self.PushHandle(self, "Name=\"Intake\"")
    Top = self.Top
    Top.Print()
    
    Top.Add ("DoeJohn1", SBHuman(self, "Sex=M Name=\"John Doe 1\" Weight=155.0 Height=70.0"))
    Top.Add ("DoeJohn2", SBHuman(self, "Name=\"John Doe 2\", Sex=M Weight=160.0 Height=75.0"))
    Top.Add ("DoeJohn3", SBHuman(self, "Name=\"John Doe 3\" Sex=M Weight=165.0 Height=80.0"))
    Top.Add ("DoeJohn4", SBHuman(self, "Name=\"John Doe 4\" Sex=M Weight=170.0 Height=85.0"))
    Top.Add ("DoeJohn5", SBHuman(self, "Name=\"John Doe 5\" Sex=M Weight=175.0 Height=90.0"))
    Top.Add ("DoeJohn6", SBHuman(self, "Name=\"John Doe 6\" Sex=M Weight=185.0 Height=95.0"))
    Top.Add ("DoeJohn7", SBHuman(self, "Name=\"John Doe 7\" Sex=M Weight=190.0 Height=100.0"))
    Top.Add ("DoeJohn8", SBHuman(self, "Name=\"John Doe 8\" Sex=M Weight=195.0 Height=105.0"))
    Top.Add ("DoeJane1", SBHuman(self, "Name=\"Jane Doe 1\" Sex=F Weight=120.0 Height=55.0"))
    Top.Add ("DoeJane2", SBHuman(self, "Name=\"Jane Doe 2\" Sex=F Weight=125.0 Height=60.0"))
    Top.Add ("DoeJane3", SBHuman(self, "Name=\"Jane Doe 3\" Sex=F Weight=130.0 Height=65.0"))
    Top.Add ("DoeJane4", SBHuman(self, "Name=\"Jane Doe 4\" Sex=F Weight=135.0 Height=70.0"))
    Top.Add ("DoeJane5", SBHuman(self, "Name=\"Jane Doe 5\" Sex=F Weight=140.0 Height=75.0"))
    Top.Add ("DoeJane6", SBHuman(self, "Name=\"Jane Doe 6\" Sex=F Weight=145.0 Height=80.0"))
    Top.Add ("DoeJane7", SBHuman(self, "Name=\"Jane Doe 7\" Sex=F Weight=150.0 Height=85.0"))
    Top.Add ("DoeJane8", SBHuman(self, "Name=\"Jane Doe 8\" Sex=F Weight=155.0 Height=90.0"))
    Top.Add ("GHV1", GHVentilator(self, "Name=\"Gravity Hookah Ventilator 1\""))
    Top.Add ("GHV2", GHVentilator(self, "Name=\"Gravity Hookah Ventilator 2\""))
    self.Command(self, "Intake.add")
    self.Command(self, "Intake.add Sex=M")
    self.Command(self, "Intake.add Weight=85")
    self.Command(self, "move ../../ER")
    self.Command(self, "list members")
    self.Command(self, "list children")
    self.Command(self, "list")
    self.Command(self, "0.list.*")
  
  # Handler for the Monitor app state.
  def StateMonitorHandle(self):
    for Child in self.Patients:
      Child.Children.PrintStats()
  
  def StateShutDownHandle(self):
    SBPrint.COut ("\n\nShutting down...")
    
  # Prints the most current and important stats to the Console.
  def PrintStats(self):
    SBPrint.COut ("\n\nTime: ")
    SBPrint.COut (str (datetime.datetime.now()))
    SBNode.PrintStats(self)
 
  # Function that is called every x seconds to update everything.
  def Update(self):
    #SBPrint.COut ("\n\nUpdate Time:", time.time())
    Handler = {
      1: self.StateMonitorHandle,
      2: self.StateShutDownHandle
    }
    # Get the function from switcher dictionary
    Key = Handler.get(self.State, lambda: "Invalid state")
    # Execute the function
    Key()
    self.PrintStats()
    #Scheduler.enter(1, 1, self.Update, ())

if __name__ == '__main__':
  SickBayConsole = SBSickBay()
  #unittest.main()
