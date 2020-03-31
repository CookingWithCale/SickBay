#!/usr/bin/python
# -*- coding: utf-8 -*-
"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /SBVentilator.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

from SBDevice import SBDevice

# A SBVentilator to aid the human respiratory system.
# Values used to calculate the SBVentilator Tidal current come from:
# Setting the Tidal Volume In Adults Receiving Mechanical Ventilation.
# All other parameters come from Rapidly manufactured ventilator system 
# specification
class SBVentilator(SBDevice):
  # Constants
  # The minimum breath 1-to-1 duty cycle.
  BreathDutyCycleMin = 1.0 / (2.0 * 1.0)
  # The minimum breath 1-to-2 duty cycle.
  BreathDutyCycleDefault = 1.0 / (2.0 * 2.0)
  # The minimum breath 1-to-1 duty cycle.
  BreathDutyCycleMax = 1.0 / (2.0 * 3.0)
  # The minimum breath 1-to-1 duty cycle.
  BreathPeriodMin = 0.0
  # The default breath period of in for 2s and out for 4s (2-to-1 ratio default)
  BreathPeriodDefault = 6.0
  # The minimum breath period of 10.0 seconds.
  BreathPeriodMax = 10.0
  # The minimum Tidal current.
  TidalCurrentMin = 6.0
  # The minimum recommended Tidal Current.
  # Maximum tidal current to patient in ml/kg.
  # The maximum tidal volume has been dropped to 8 ml per kilogram
  # ideal or predicted body weight based on the patient’s height and sex
  # Source: 
  TidalCurrentMax = 8.0
  # minimum End Inspiratory plateau pressure
  # @units cm H2O
  EIPPMin = 0.0
  # @units cm H2O
  # Lung protection also places an equal importance on maintaining an 
  # end-inspiratory plateau pressure ≤ 30 cm H2O to avoid alveolar 
  # overdistention and lowering the targeted tidal volume below 8 ml/kg 
  # if that pressure is exceeded.
  EIPPMax = 30.0
    
  def __init__(self, NID, BreathDutyCycle = 0.5, BreathPeriod = 2.0, TidalCurrent = 0.0, EIPP = 0.0):
    SBDevice.__init__(self, "Device", "Ventilator")
    self.Type = ""                        #< The type of SBVentilator
    # The breath duty cycle where 0.5 is 50% duty cycle.
    self.BreathDutyCycle = BreathDutyCycle 
    self.BreathPeriod = BreathPeriod      #< The breath period in seconds.
    self.TidalCurrent = TidalCurrent      #< The tidal air current.
    self.EIPP = EIPP                      #< End Inspiratory plateau pressure.
  
  # Attaches a Patient to the SBVentilator.
  def AttachPatient(self, Patient):
    super().NodesAdd (Patient)
  
  # Detaches a Patient from the SBVentilator.
  def DetachPatient(self, Patient):
    super().NodesRemove (Patient)
  
  def BreathDutyCycleSet(self, BreathDutyCycle):
    if (BreathDutyCycle >= self.BreathDutyCycleMin and
        BreathDutyCycle <= self.BreathDutyCycleMax):
      self.BreathDutyCycle = BreathDutyCycle
  
  def BreathPeriodSet(self, BreathPeriod):
    if (BreathPeriod >= self.BreathPeriodMin and
        BreathPeriod <= self.BreathPeriodMax):
      self.BreathPeriod = BreathPeriod
    
  def TidalCurrentSet(self, TidalCurrent):
    if (TidalCurrent >= self.TidalCurrentMin and
        TidalCurrent <= self.TidalCurrentMax):
      self.TidalCurrent = TidalCurrent
    
  def EIPPSet(self, EIPP):
    if (EIPP >= self.EIPPMin and
        EIPP <= self.EIPPMax):
      self.EIPP = EIPP
