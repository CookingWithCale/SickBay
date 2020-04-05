# !/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBHumanRespiratory.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBNode import SBNode

# A model of a human heart.
class SBHumanRespiratory(SBNode):
  # Constants
  IRVMin = 0.0          # The min IRV value.
  IRVMax = 100.0        # The max IRV value.
  TVMin = 0.0           # The min TV value.
  TVMax = 100.0         # The max TV value.
  ERVMin = 0.0          # The min ERV value.
  ERVMax = 100.0        # The max ERV value.
  RVMin = 0.0           # The min RV value.
  RVMax = 100.0         # The max RV value.

  def __init__(self, Sex, SickBay, Command = None):
    SBNode.__init__(self, Command, "Respiratory", 1)
    # Inspiratory reserve volume is the amount of air that can be forcefully 
    # inspired after a normal inspiration.
    self.IRV = 3.0

    # Tidal volume is tThe volume of air which is circulated through inhalation 
    # and expiration during one normal respiration.
    self.TV = 0.5

    # Expiratory reserve volume is the volume of air which can be exhaled 
    # forcefully after a normal expiration.
    self.ERV = 1.2

    # Residual volume is the amount of air that remains in the lungs after 
    # normal expiration.
    self.RV = 1.2

    self.Description = ""        # A Description of this human's Respiratory system.

    if Sex == "M":
      self.VC = 4.6    #< Vital capacity
      self.IC = 3.5    #< Inspiratory capacity
      self.RFC = 2.3   #< Functional residual capacity
      self.TLC = 5.8   #< Total lung capacity
    elif Sex == "F":
      self.VC = 3.1
      self.IC = 2.4
      self.FRC = 1.8
      self.TLC = 4.2
    SickBay.Push(self)
    
  def IRVSet(self, IRV):
    if (IRV >= self.IRVMin and
      IRV <= self.IRVMax):
      self.IRV = IRV
    self.Update()
  
  def TVSet(self, TV):
    if (TV >= self.TVMin and 
        TV <= self.TVMax):
      self.TV = TV
    self.Update()
    
  def ERVSet(self, ERV):
    if (ERV >= self.ERVMin and 
        ERV <= self.ERVMax):
      self.ERV = ERV
    self.Update()
    
  def RVSet(self, RV):
    if (RV >= self.RVMin and 
        RV <= self.RVMax):
      self.RV = RV
    self.Update()
    
  def Update(self): 
    self.VC = self.IRV + self.TV + self.ERV
    self.IC = self.IRV + self.TV
    self.FRC = self.ERV + self.RV
    self.TLC = self.IRV + self.TV + self.ERV + self.RV

  def DescriptionSet (self, Description):
    self.Description = Description

  def PrintStats (self, Stats = "", SelfKey = ""):
    return Stats

  def PrintDetails (self, Details = ""):
    return "\nIRV:" + self.IRV + "\nTV:" + self.TV + "\nERV:" + \
           self.ERV + "\nVC: " + self.VC + "\nIC: " + self.IC + "\nFRC: " + self.FRC +\
           "\nTLC: " + self.TLC + \
           "\nDescription: \"" + self.Description + "\n\""
