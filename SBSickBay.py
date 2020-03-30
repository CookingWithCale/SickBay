"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /SickBay.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """
 
import SBNode
import SBDevice
import Human
import Ventilator
import GHVentilator
import sched, time

Scheduler = sched.scheduler(time.time, time.sleep)
  
# The SickBay app object.
class SBSickBay(SBNode):
  # Constants
  StateMonitoring = 1     #< State: Monitoring.
  StateShuttingDown = 2   #< State: Shutting down.
  
  def __init__(self):
    print ("\n\nWelcome to SickBay.\n")
    super().__init__("Device", "SickBay", "Root", "The root scope.")
    self.Node = self               #< The currently selected node.
    self.Stack = []                #< The stack of SBNodes.
    self.Patients = []             #< The patients checked into SickBay.
    self.Devices = []              #< The devices in the SickBay.
    self.Patient = None            #< The currently selected patient.
    self.HumanOperator = ""        #< The SickBay operator.
    self.HumanOperatorSet()
    self.State = self.StateMonitoring    #< The app state.
    self.PatientsAddTestPatients()
    
    if (input == "1"):
      self.EditPatient()
    # self.MonitorBegin()
  
  def Push(self, NodeNew):
    self.Stack.append(self.Node)
    self.Node = NodeNew
  
  def Pop(self):
    if len(self.Stack) == 0:
      return
    self.Node = self.Stack.pop()
  
  def MonitorBegin(self):
    Scheduler.enter(1, 1, self.Update, ())
    Scheduler.run()
    
  def HumanOperatorSet(self):
    print("\nEnter new Operator name or type cancel: ")
    input = "Me" #raw_input("")
    if (input.lower() == "cancel"):
      return
    self.HumanOperator = input
    print ("\nSwitching to HumanOperator: " + self.HumanOperator)
  
  # Adds a patient to the Patients.
  def PatientsAdd(self, Name, Sex, Height, Weight):
    self.Patients.append(Human(Name, Sex, Height, Weight))

  # Handler for the init app state.
  def PatientsAddTestPatients (self):
    print ("\n\nAdding test patients.")
    self.Patients.append ("John Doe 1", "M", 170.0, 70.0)
    self.Patients.append ("John Doe 2", "M", 180.0, 75.0)
    self.Patients.append ("John Doe 3", "M", 190.0, 80.0)
    self.Patients.append ("John Doe 4", "M", 200.0, 85.0)
    self.Patients.append ("Jane Doe 1", "F", 120.0, 55.0)
    self.Patients.append ("Jane Doe 2", "F", 130.0, 60.0)
    self.Patients.append ("Jane Doe 3", "F", 140.0, 65.0)
    self.Patients.append ("Jane Doe 4", "F", 150.0, 70.0)

    self.Devices.append (GHVentilator())
  
  # Handler for the Monitor app state.
  def StateMonitorHandle(self):
    for Patient in self.Patients:
      Patient.PrintStats()
  
  def StateShutDownHandle(self):
    print ("\n\nShutting down...")
    
  # Prints the most current and important stats to the Console.
  def PrintStats(self):
    for Patient in self.Patients:
      Patient.PrintStats()
 
  # Function that is called every x seconds to update everything.
  def Update(self):
    print ("\n\nUpdate Time:", time.time())
    Handler = {
      1: self.StateMonitorHandle,
      2: self.StateShutDownHandle
    }
    # Get the function from switcher dictionary
    Handle = Handler.get(self.State, lambda: "Invalid state")
    # Execute the function
    Handle()
    self.PrintStats()
    Scheduler.enter(1, 1, self.Update, ())

if __name__ == '__main__':
  SickBayConsole = SickBay()
    #unittest.main()
