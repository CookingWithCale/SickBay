# !/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBSickBay.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>. Process
 
from Stringf import *
from SBNode import SBNode
from SBDevice import SBDevice
from SBHuman import SBHuman
from SBRoom import SBRoom
from SBVentilator import *
from GHVentilator import *
import sched, time, datetime

Scheduler = sched.scheduler(time.time, time.sleep)
  
# The SickBay Process object.
class SBSickBay(SBNode):
  # Constants
  StateMonitoring = 1     #< State: Monitoring.
  StateShuttingDown = 2   #< State: Shutting down.
  
  def __init__(self):
    self.NIDCount = 0                 #< The total number of SBNodes.
    self.HumanCount = 0                #< The count of new Humans in the Room.
    self.DeviceCount = 0              #< The SBDevice count
    self.RoomCount = 0                #< The SBRoom count
    self.SearchCount = 0              #< The SBSearch count
    self.OperationCount = 0           #< The Procedure count
    self.ProcessCount = 0             #< The Process count
    self.Top = self                   #< The currently selected node.
    self.PushCount = 0                #< The number pushes since the of the Command.
    self.ModeStackRestore = False     #< Mode for Commands that start with a '.'
    self.Stack = []                   #< The stack of SBNodes.
    SBNode.__init__(self, self, "Type=\"SickBay\" Name=\"SickBay\" " \
                                "Description=\"Root Node with NID 0.\"")
    self.Pop()
    self.State = self.StateMonitoring #< The Process state.
    self.Add(self, "Intake", SBRoom(self, "Name=\"Patient Intake\" Description=\"The Intake Room where you wait get get into the Hospital.\""))
    self.Add(self, "ER", SBRoom(self, "Name=\"Emergency Room\" Description=\"The room with Patients who may need critical care.\""))
    self.Add(self, "ICU", SBRoom(self, "Name=\"Intensive Care Unit\" Description=\"The room for Patients in need of critical care.\""))
    self.Add(self, "Rooms", SBRoom(self, "Name=\"Patient Rooms\" Description=\"The Rooms where the Patients are in who aren't in the ER or ICU.\""))
    self.Add(self, "Guests", SBRoom(self, "Name=\"Guest Room\" Description=\"The Room where guests start out in.\""))
    self.Add(self, "Staff", SBRoom(self, "Name=\"Staff Room\" Description=\"The Room where all the Staff start out in.\""))
    self.Add(self, "Devices", SBRoom(self, "Name=\"Device Room\" Description=\"The Room where all of the unused devices are stored in.\""))
    self.SetupTest()
    self.ConsoleMain()
  
  def StackHeight(self):
    return len(self.Stack)

  # Handler for the init Process state.
  def SetupTest (self):
    SBNode.COut(self, "\n> Setting up test data... StackHeight:" + str(len(self.Stack)) + " <")
    SBNode.COut(self, "\n> Printing root path (Should read \"><.\") \"" + self.Path() + "\" <")
    self.Print()
    SBNode.COut(self, "\n> Pushing Intake onto the stack. <")
    self.PushKey("Intake")
    Top = self.Top
    SBNode.COut(self, "\n> Printing Top (should be Intake) with Key \"" + 
                 Top.Key () + "\" Path:\"" + Top.Path() + "\"")
    Top.COut(Top.List())
    
    Top.Add (self, "DoeJohn1", SBHuman(self, "Sex=M Name=\"John Doe 1\" Weight=155.0 Height=70.0"))
    SBNode.COut(self, "\nWorks here!.\n")
    Top.Print()
    Top.Add (self, "DoeJohn2", SBHuman(self, "Name=\"John Doe 2\", Sex=M Weight=160.0 Height=75.0"))
    Top.Add (self, "DoeJohn3", SBHuman(self, "Name=\"John Doe 3\" Sex=M Weight=165.0 Height=80.0"))
    Top.Add (self, "DoeJohn4", SBHuman(self, "Name=\"John Doe 4\" Sex=M Weight=170.0 Height=85.0"))
    Top.Add (self, "DoeJohn5", SBHuman(self, "Name=\"John Doe 5\" Sex=M Weight=175.0 Height=90.0"))
    Top.Add (self, "DoeJohn6", SBHuman(self, "Name=\"John Doe 6\" Sex=M Weight=185.0 Height=95.0"))
    Top.Add (self, "DoeJohn7", SBHuman(self, "Name=\"John Doe 7\" Sex=M Weight=190.0 Height=100.0"))
    Top.Add (self, "DoeJohn8", SBHuman(self, "Name=\"John Doe 8\" Sex=M Weight=195.0 Height=105.0"))
    Top.Add (self, "DoeJane1", SBHuman(self, "Name=\"Jane Doe 1\" Sex=F Weight=120.0 Height=55.0"))
    Top.Add (self, "DoeJane2", SBHuman(self, "Name=\"Jane Doe 2\" Sex=F Weight=125.0 Height=60.0"))
    Top.Add (self, "DoeJane3", SBHuman(self, "Name=\"Jane Doe 3\" Sex=F Weight=130.0 Height=65.0"))
    Top.Add (self, "DoeJane4", SBHuman(self, "Name=\"Jane Doe 4\" Sex=F Weight=135.0 Height=70.0"))
    Top.Add (self, "DoeJane5", SBHuman(self, "Name=\"Jane Doe 5\" Sex=F Weight=140.0 Height=75.0"))
    Top.Add (self, "DoeJane6", SBHuman(self, "Name=\"Jane Doe 6\" Sex=F Weight=145.0 Height=80.0"))
    Top.Add (self, "DoeJane7", SBHuman(self, "Name=\"Jane Doe 7\" Sex=F Weight=150.0 Height=85.0"))
    Top.Add (self, "DoeJane8", SBHuman(self, "Name=\"Jane Doe 8\" Sex=F Weight=155.0 Height=90.0"))
    Top.Add (self, "GHV1", GHVentilator(self, "Name=\"Gravity Hookah Ventilator 1\""))
    Top.Add (self, "GHV2", GHVentilator(self, "Name=\"Gravity Hookah Ventilator 2\""))
    SBNode.COut(self, "\nDone adding test patients...\n")
    #self.Command(self, "Intake.add")
    #self.Command(self, "Intake.add Sex=M")
    #self.Command(self, "Intake.add Weight=85")
    #self.Command(self, "move ../../ER")
    #self.Command(self, "list members")
    #self.Command(self, "list children")
    #self.Command(self, "list")
    #self.Command(self, "0.list.*")
  
  # Pops a node off the stack.
  def Pop(self, Command = ""):
    SBNode.COut(self, "\n< > Popped -" + str(self.NID) + " <")
    if len(self.Stack) == 0:
      return ""
    Top = self.Stack.pop()
    Top.Command(self, Command)
    self.Top = Top
    self.PushCount -= 1

  # Pushes this node onto the Crabs stack.
  def Push(self, Node, Command = ""):
    if Node == None: return "> Error Attempted to push a nil Node. <"
    SBNode.COut(self, "\n> -" + str(Node.NID) + " ")
    self.Stack.append(self.Top)
    self.Top = Node
    self.PushCount += 1
    Result = Node.Command(self, Command)
    SBNode.COut(self, "> Pushed -" + str(Node.NID) + " <")
    return Result

  # Pushes this node onto the Crabs stack.
  def PushKey(self, Key, Command = ""):
    #SBNode.COut(self, "\n> Pushing Key \"" + Key + "\" where Children are: " + self.Top.ListChildren())
    if Key in self.Children:
      Child = self.Children[Key]
      #SBNode.COut(self, "\nFound " + Key + " in Path \"" + Child.Path() + "\"")
      return self.Push(Child, Command)
    return "Key not found."

  # Pushes this node onto the Crabs stack.
  def CommandStart(self, Node, Args = ""):
    if Args[0] == ".":
      self.TopStart = 0
      Args = Args[1:]
    return self.Push(Node, Args)
  
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
  
  # Generates the next unique Head Id by incrementing HumanCount
  def HIDNext(self):
    Result = self.NIDCount
    self.NIDCount = Result + 1
    return Result
  
  # Generates the next unique Device Id by incrementing DeviceCount
  def DIDNext(self):
    Result = self.DeviceCount
    self.DeviceCount = Result + 1
    return Result
  
  # Generates the next unique Room Id by incrementing RoomCount
  def RIDNext(self):
    Result = self.RoomCount
    self.RoomCount = Result + 1
    return Result
  
  # Generates the next unique Search Id by incrementing SearchCount
  def SIDNext(self):
    Result = self.SearchCount
    self.SearchCount = Result + 1
    return Result
  
  # Generates the next unique Search Id by incrementing OperationCount
  def OIDCount(self):
    Result = self.OperationCount
    self.OperationCount = Result + 1
    return Result
  
  # Generates the next unique Process Id by incrementing ProcessCount
  def PIDNext(self):
    Result = self.ProcessCount
    self.ProcessCount = Result + 1
    return Result

  # Console main loop.
  def ConsoleMain(self):
    COut.Print("\nWelcome to SickBay.\n" + self.PrintStats() +\
                  "\nEnter \"?\" at any time to get help " + \
                  "\nor press Enter on the keyboard to update the stats" + \
                  "\nor type \"exit\" to exit the console.\n")
    while True:
      COut.Print ("\n" + self.Top.Path())
      UserInput = raw_input("").lower()
      if UserInput == "exit":
        return
      COut.Print(self.Top.CommandStart(self, self, UserInput))
  
  # Enters the monitoring state.
  def MonitorBegin(self):
    Scheduler.enter(1, 1, self.Update, ())
    Scheduler.run()
    SBNode.COut(self, "\nBeginning monitoring...")
  
  # Prints the list of the members and followed by a timestamp
  def Print(self, String = ""):
    return SBNode.Print(self, String) + " @" + str (datetime.datetime.now())
  
  # Handler for the Monitor Process state.
  def StateMonitorHandle(self):
    for Child in self.Patients:
      Child.Children.PrintStats()
  
  def StateShutDownHandle(self):
    SBNode.COut(self, "\nShutting down...")
 
  # Function that is called every x seconds to update everything.
  def Update(self):
    Handler = {
      1: self.StateMonitorHandle,
      2: self.StateShutDownHandle
    }
    # Get the function from switcher dictionary
    Key = Handler.get(self.State, lambda: "Invalid state")
    # Execute the function
    Key()
    self.PrintStats()
    Scheduler.enter(1, 1, self.Update, ())

if __name__ == '__main__':
  SickBayConsole = SBSickBay()
