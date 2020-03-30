"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /SickBay.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

import Human
import Ventilator

def SickBay():
  # The SickBay app object.
  class SickBay:
    # Constants
    StateInit = 0          #< State: Init.
    StateMonitor = 1       #< State: Monitoring.
    StateShutDown = 1      #< State: Shutting down.
    
    def __init__(self):
    State = StateInit      #< The app state.
    Patients = []          #< The List of patients.
    Patient = None         #< The current selected patient.
    Patients.append()
  
    # Adds a patient to the Patients.
    def PatientsAdd(self, Name, Sex, Height, Weight):
      Patients.append(Human(Name, Sex, Height, Weight))

    # Handler for the init app state.
    def StateInitHandle (self):
      print ("\nWelcome to SickBay")
      print ("\n\nAdding test patients.")
      Patients.append ("John Doe 1", "M", 1.7, 70)
      Patients.append ("John Doe 2", "M", 1.8, 75)
      Patients.append ("John Doe 3", "M", 1.9, 80)
      Patients.append ("John Doe 4", "M", 2.0, 85)
      Patients.append ("Jane Doe 1", "F", 1.2, 55)
      Patients.append ("Jane Doe 2", "F", 1.3, 60)
      Patients.append ("Jane Doe 3", "F", 1.4, 65)
      Patients.append ("Jane Doe 4", "F", 1.5, 70)
  
    # Handler for the Monitor app state.
    def StateMonitorHandle(self):
      for Patient in Patients:
        Patient.PrintStats()
  
    def StateShutDownHandle(self):
      print ("\n\nShutting down...")

    # Main program entry point.
    def Run(self, Argument):
      Handler = {
        1: StateInitHandle,
        2: StateMonitorHandle,
        3: StateShutDownHandle
      }
      # Get the function from switcher dictionary
      Handle = Handler.get(Argument, lambda: "Invalid State")
      # Execute the function
      Handle()
    
    # Prints all of the Patient's stats.
    def PrintStats(self):
      for Patient in Patients:
        Patient.PrintStats()
