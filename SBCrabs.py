# !/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /SBCrabs.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>. Process
 
from Stringf import *
from SBNode import *
from SBDevice import *
from SBHuman import *
from SBRoom import *
from SBRoomIntakePatient import *
from SBRoomIntakeStaff import *
from SBVentilator import *
from GHVentilator import *
import sched, time, datetime

Scheduler = sched.scheduler(time.time, time.sleep)
  
# The Chinese Room Abstract Stack Machine (Crabs) A=A*B expression root.
class SBCrabs(SBRoom):
  # Constants
  StateMonitoring = 1     #< State: Monitoring.
  StateShuttingDown = 2   #< State: Shutting down.
  
  def __init__(self):
    self.NIDCount = 0                 #< The total number of SBNodes.
    self.HumanCount = 0               #< The count of new Humans in the Room.
    self.DeviceCount = 0              #< The SBDevice count.
    self.RoomCount = 1                #< The SBRoom count.
    self.MissionCount = 0             #< The Mission count.
    self.DepthCounter = 0             #< The number pushes since the of the Command.
    self.ModeStackRestore = False     #< Mode for Commands that start with a '.'
    self.Top = self                   #< The currently selected node.
    self.Stack = []                   #< The stack of SBNodes.
    self.Cursor = 0                   #< The cursor location in the current Crabs expression.
    self.State = self.StateMonitoring #< The Process state.
    self.Clipboard = None             #< Copy & paste clipboard.
    SBRoom.__init__(self, self, "Crabs")
    self.Test()

  # Function resest the DepthCounter.
  def DepthCounterReset(Self, Crabs, Command, Cursor):
    self.DepthCounter = 0
    return None
  
  # The height of the stack.
  def StackHeight(self):
    return len(self.Stack)
  
  # Pops a node off the stack.
  def Pop(self, Command = None, Cursor = 0):
    if len(self.Stack) == 0:
      return ""
    Top = self.Stack.pop()
    Top.COut("< @" + str(datetime.datetime.now()).replace(" ", ";") + "\n")
    Top.Command(self, Command, Cursor)
    self.Top = Top
    self.DepthCounter -= 1
  
  # Pops All of the nodes off of the stack.
  def PopAll(self, Command = None, Cursor = 0):
    self.Stack.clear ()
    self.StackHeight = 0
    self.DepthCounter = 0

  # Pushes this node onto the stack.
  def Push(self, Node, Command = None, Cursor = 0):
    if Node == None: return ">< Error Attempted to push a nil Node. <"
    self.COut("> -" + str(Node.NID) + " ")
    self.Stack.append(self.Top)
    self.Top = Node
    self.DepthCounter += 1
    return Node.Command(self, Command, Cursor)

  # Pushes this node onto the stack.
  def PushNID(self, NID, Command = None):
    Node = self.FindNID(NID)
    if Node == None: return ">< Error NID:" + NID + " doesn't exist! <\n"
    return self.Push(Node, Command)

  # Pushes this node onto the stack.
  def PushKey(self, Key, Command = None):
    #self.COut("> Pushing Key '" + Key + "' where Children are: " + self.Top.ListChildren())
    if Key in self.Children:
      Child = self.Children[Key]
      #self.COut("Found " + Key + " in Path '" + Child.Path() + "'")
      return self.Push(Child, Command, Cursor)
    return "Key not found."

  # Pushes this node onto the stack.
  def CommandStart(self, Node, Command = None, Cursor = 0):
    if Command[0] == ".":
      self.TopStart = 0
      Cursor += 1
    return self.Push(Node, Command, Cursor)
  
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
  
  # Generates the next unique Search Id by incrementing MissionCount
  def MIDNext(self):
    Result = self.MissionCount
    self.MissionCount = Result + 1
    return Result
  
  # Generates the next unique Process Id by incrementing ProcessCount
  def PIDNext(self):
    Result = self.ProcessCount
    self.ProcessCount = Result + 1
    return Result

  # Console main loop.
  def ConsoleMain(self):
    COut.Indent(100, "> ><", '\n', '\n')
    self.COut("? Welcome to SickBay and the Chinese Room Abstract Stack (Crabs) Machine. <")
    self.COut("Enter '?' at any time to get help ")
    self.COut("or press '!'")
    self.COut("or type 'exit' to exit the console.")
    while True:
      COut.Print2 ("\n", self.Top.Path())
      UserInput = raw_input("")#.lower()
      if UserInput == "exit":
        return
      Result = self.Do(UserInput)
      COut.Print(Result)
      #Result = self.Do(UserInput)
      #COut.Print(Result)
  
  # Enters the monitoring state.
  def MonitorBegin(self):
    Scheduler.enter(1, 1, self.Update, ())
    Scheduler.run()
    self.COut("Beginning monitoring...")
  
  # Prints the list of the members and followed by a timestamp
  def Print(self, String = ""):
    return SBNode.Print(self, String) + " @" + str (datetime.datetime.now())
  
  # Handler for the Monitor Process state.
  def StateMonitorHandle(self):
    for Child in self.Patients:
      Child.Children.PrintStats()
  
  def StateShutDownHandle(self):
    self.COut("Shutting down...")
 
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

  # Super-user Do.
  def Do(self, Command, Cursor = 0):
    return self.Command(self, Command, Cursor)
  
  def Test(self):
    self.COut("? Testing Crabs <\n\n")
    self.COut("? Done testing Crabs <\n\n")
