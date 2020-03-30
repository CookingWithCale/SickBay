""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /CirculatorySystem/CirculatorySystem.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

# A model of a human Circulatory system.
class CirculatorySystem():
  # Constants
  BloodPressureMin = 0.0     #< The min "dead" blood pressure rate of 0.0.
  BloodPressureMax = 1000.0  #< The max pulse rate.
  BloodTypeUnknown = 0       #< BloodType Unknown
  BloodTypeA = 1             #< BloodType A
  BloodTypeB = 2             #< BloodType B
  BloodTypeAB = 3            #< BloodType AB
  BloodTypeO = 4             #< BloodType O
  HeartRateMin = 0.0         #< The min "dead" pulse rate of 0.0.
  HeartRateMax = 1000.0      #< The max pulse rate.
    
  def __init__(self):
    self.BloodPressure = 0.0          #< The heart pulse rate.
    self.BloodType = self.BloodTypeUnknown #< The patient's blood type.
    self.HeartRate = 0.0              #< The heart pulse rate.
    self.Description = ""             #< A Description of the heart.

  def BloodPressureSet (self, BloodPressure):
    if (BloodPressure <= self.BloodPressureMin and 
        BloodPressure <= self.BloodPressureMax):
      self.BloodPressure = BloodPressure

  def BloodTypeSet (self, BloodType):
    if (BloodType <= self.BloodTypeUnknown and 
        BloodType <= self.BloodTypeO):
      self.BloodType = BloodType
  
  def BloodTypeString(self):
    return {
      0: "Unknown",
      1: "A",
      2: "B",
      3: "AB",
      4: "O"
    }
  
  def HeartRateSet (self, HeartRate):
    if (HeartRate >= self.HeartRateMin and
        HeartRate > self.HeartRateMax):
      self.HeartRate = HeartRate
    
  def DescriptionSet (self, Description):
    self.Description = Description

  def PrintStats (self):
    print ("\nBloodPressure:" + self.BloodPressure +
           "\nHeartRate:" + self.HeartRate)
    
  def PrintDetails (self):
    print ("\nBloodPressure: " + self.BloodPressure +
           "\nBloodType: " + self.BloodType +
           "\nHeartRate: " + self.HeartRate)
  
  def PrintDescription (self):
    print ("Description:" + self.Description)
