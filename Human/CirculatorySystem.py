""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /CirculatorySystem/CirculatorySystem.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

# A model of a human Circulatory system.
def CirculatorySystem():
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
    BloodPressure = 0.0          #< The heart pulse rate.
    BloodType = BloodTypeUnknown #< The patient's blood type.
    HeartRate = 0.0              #< The heart pulse rate.
    Description = ""             #< A Description of the heart.

  def BloodPressureSet (BloodPressure):
    if (BloodPressure <= BloodPressureMin and 
        BloodPressure <= BloodPressureMax):
      self.BloodPressure = BloodPressure

  def BloodTypeSet (BloodType):
    if (BloodType <= BloodTypeUnknown and 
        BloodType <= BloodTypeO):
      self.BloodType = BloodType
  
  def BloodTypeString():
      return {
          0: "Unknown",
          1: "A",
          2: "B",
          3: "AB",
          4: "O"
      }
  
  def HeartRateSet (HeartRate):
    if (HeartRate >= HeartRateMin and
        HeartRate > HeartRateMax):
      self.HeartRate = HeartRate
    
  def DescriptionSet (Description):
    self.Description = Description

  def PrintStats ():
    print ("\nBloodPressure:" + self.BloodPressure +
           "\nHeartRate:" + self.HeartRate)
    
  def PrintDetails ():
    print ("\nBloodPressure: " + self.BloodPressure +
           "\nBloodType: " + self.BloodType +
           "\nHeartRate: " + self.HeartRate)
  
  def PrintDescription ():
    print ("Description:" + self.Description)
