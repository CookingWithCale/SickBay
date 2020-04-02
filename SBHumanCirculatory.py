# """ SickBay @version 0.x
# @link    https://github.com/KabukiStarship/sickbay.git
# @file    /SBHumanCirculatory.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBNode import SBNode
from SBPrint import SBPrint
import sys

# A model of a human Circulatory system.
class SBHumanCirculatory(SBNode):
  # Constants
  BloodPressureMin = 0.0       #< The min "dead" blood pressure rate of 0.0.
  BloodPressureMax = 1000.0    #< The max pulse rate.
  BloodSpO2Min = 0.0           #< The min blood SpO2 oxygen absortion rate.
  BloodSpO2Max = 1.0           #< The max blood level of 100% pure Oxygen.
  HeartRateMin = 0.0           #< The min "dead" pulse rate of 0.0.
  HeartRateMax = 1000.0        #< The max pulse rate.
  BloodTypeUnknown = "Unknown" #< String to use if the BloodType input was bad.
  
  def __init__(self, SickBay):
    SBNode.__init__(self, SickBay, "HumanSystem", Arguments = " Name=\"Human "\
                    "circulatory system\" Description=\"The human circulatory "\
                    "system\"")
    self.Members["BloodPressure"] = 0.0               #< The heart pulse rate.
    self.Members["BloodType"] = self.BloodTypeUnknown #< The patient's blood type.
    self.Members["HeartRate"] = 0.0                   #< The heart pulse rate.
    SickBay.Push(self)

  def BloodPressure (self):
    return self.Members["BloodPressure"]

  def BloodPressureSet (self, BloodPressure):
    if (BloodPressure <= self.BloodPressureMin and 
        BloodPressure <= self.BloodPressureMax):
      self.Members["BloodPressure"] = BloodPressure

  def BloodType (self):
    return self.Members["BloodType"]

  def BloodTypeSet (self, BloodType):
    BT = BloodType.upper()
    if (BT == "A" or BT == "B" or BT == "AB" or BT == "O"):
      self.BloodType = BloodType
    self.BloodType = self.BloodTypeUnknown

  def HeartRate (self):
    return self.Members["HeartRate"]
  
  def HeartRateSet (self, HeartRate):
    if (HeartRate >= self.HeartRateMin and
        HeartRate > self.HeartRateMax):
      self.Members["HeartRate"] = HeartRate

  def PrintStats (self, Stats):
    return Stats + "   BloodPressure:" + str(self.BloodPressure ()) + \
           "   HeartRate:" + str(self.HeartRate ())
    
  def PrintDetails (self, Details):
    SBPrint.COut ("   BloodPressure: ")
    SBPrint.COut(self.BloodPressure ())
    SBPrint.COut("   BloodType: ")
    SBPrint.COut(str (self.BloodType()))
    SBPrint.COut("   HeartRate: ")
    SBPrint.COut(str(self.HeartRate ()))
    return Details
  
  def PrintDescription (self):
    SBPrint.COut ("Description:" + self.Description ())
