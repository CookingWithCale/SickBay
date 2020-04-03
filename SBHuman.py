#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/sickbay.git
# @file    /SBHuman.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBNode import SBNode
from SBHumanCirculatory import SBHumanCirculatory
from SBHumanRespiratory import SBHumanRespiratory
from Stringf import Stringf
import sys

# A model of a human.
class SBHuman(SBNode):
  HeightMin = 0.0         #< The minimum Height of a person is 0M.
  HeightMax = 10.0        #< The maximum Height of a person is 10M.
  WeightMin = 0.0         #< The minimum Weight of a person is 0KG.
  WeightMax = 1000000.0   #< The maximum Weight of a person is 1000KG.
  SexMale = 0             #< Sex is male.
  SexFemale = 1           #< Sex if female.
  
  def __init__(self, SickBay, Arguments = ""):
    SBNode.__init__(self, SickBay, Arguments)
    self.Add("Sex", "")         #< The Sex of the person.
    self.Add("Height", 0.0)     #< The person's Height.
    self.Add("Weight", 0.0)     #< The person's Weight.
    SickBay.Push(self)
    
    # The human's Circulatory system.
    self.Circulatory = SBHumanCirculatory(SickBay)

    # The human's Respiratory system.
    self.Respiratory = SBHumanRespiratory(SickBay, self.Meta["Sex"])

  def NameSet (self, Name):
    self.Name = Name

  def UIDSet (self, UID):
    self.UID = UID
  
  def SexSet(self, Sex):
    if Sex >= self.SexMale or Sex <= self.SexFemale:
      self.Sex = Sex
  
  def HeightSet (self, Height):
    if Height >= self.HeightMin and Height <= self.HeightMax:
      self.Height = Height
  
  def WeightSet (self, Weight):
    if Weight >= self.WeightMin and Weight <= self.WeightMax:
      self.Weight = Weight
  
  def IsMale (self): return self.Sex == "m"
  
  def IsFemale (self): return self.Sex == "f"
  
  # Returns the idea body weight of a person.
  def WeightIdeal(self):
    # Height calculations using centimeters.
    if self.IsMale():
      return 50.0 + 0.91 * (self.Height - 152.4)
    elif self.IsFemale(): 
      return 45.5 + 0.91 * (self.Height - 152.4)
    else: 
      return self.Weight
  
  def CirculatorySet(self, Circulatory):
    self.Circulatory = Circulatory
  
  def RespiratorySet(self, Respiratory):
    self.Respiratory = Respiratory

  def PrintStats (self, String = "", SelfKey = ""):
    if SelfKey is not None:
      String += SelfKey + "   "
    return String + "Name:" + self.Name () + "   NID:" + str(self.NID) +\
           self.Circulatory.PrintStats (String) +\
           self.Respiratory.PrintStats (String)
    
  # Prints all of the Details about the object except the Help.
  def PrintDetails (self, String = ""):
     String += "Name:" + self.Name () + " NID:" + self.NID + " Sex:" + self.Sex () + \
           " Height:" + self.Height () + " Weight:" + self.Weight () + \
           "\nDescription:\"" + self.Description () + "\n"
     self.Circulatory.PrintDetails (String)
     return self.Respiratory.PrintDetails (String)
