"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /Human/Human.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

import CirculatorySystem
import RespiratorySystem

# A model of a human.
class Human():
  HeightMin = 0.0         #< The minimum Height of a person is 0M.
  HeightMax = 10.0        #< The maximum Height of a person is 10M.
  WeightMin = 0.0         #< The minimum Weight of a person is 0G.
  WeightMax = 1000000.0   #< The maximum Weight of a person is 1000KG.
  SexMale = 0             #< Sex is male.
  SexFemale = 1           #< Sex if female.
  
  def __init__(self, Name, UID, Sex, Height, Weight):
    self.Name = Name      #< The person's Name
    self.UID = UID        #< The unique ID of the person.
    self.Sex = Sex        #< The Sex of the person.
    self.Height = Height  #< The person's Height.
    self.Weight = Weight  #< The person's Weight.

    # The human's Circulatory system.
    self.Circulatory = CirculatorySystem()

    # The human's Respiratory system.
    self.Respiratory =  RespiratorySystem()

  def NameSet (self, Name):
    self.Name = Name

  def UIDSet (self, UID):
    self.UID = UID
  
  def SexSex(self, Sex):
    if Sex >= SexMale or Sex <= SexFemale:
      self.Sex = Sex
  
  def HeightSet (self, Height):
    if Height >= HeightMin and Height <= HeightMax:
      self.Height = Height
  
  def WeightSet (self, Weight):
    if Weight >= WeightMin and Weight <= WeightMax:
      self.Weight = Weight
  
  def CirculatorySet(self, Circulatory):
    self.Circulatory = Circulatory
  
  def RespiratorySet(self, Respiratory):
    self.Respiratory = Respiratory

  def PrintStats ():
    print ("Name:" + self.Name + " UID:" + self.UID)
    self.Circulatory.PrintStats ()
    self.Respiratory.PrintStats ()
      
  def PrintDetails ():
    print ("Name:" + self.Name + " UID:" + self.UID + " Sex:" + self.Sex + 
           " Height:" + self.Height + " Weight:" + self.Weight
           "\nDescription:\"" + self.Description + "\n")
    self.Circulatory.PrintDetails ()
    self.Respiratory.PrintDetails ()
      
  def PrintDescription ():
    print ("\nDescription:\"" + self.Description + "\n")
    self.Circulatory.PrintDescription ()
    self.Respiratory.PrintDescription ()