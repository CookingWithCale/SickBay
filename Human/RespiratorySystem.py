""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /RespiratorySystem/RespiratorySystem.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

# A model of a human heart.
class RespiratorySystem():
    IRVMin = 0.0          # The min IRV value.
    IRVMax = 100.0        # The max IRV value.

    TVMin = 0.0           # The min TV value.
    TVMax = 100.0         # The max TV value.

    ERVMin = 0.0          # The min ERV value.
    ERVMax = 100.0        # The max ERV value.

    RVMin = 0.0           # The min RV value.
    RVMax = 100.0         # The max RV value.

    # Inspiratory reserve volume is the amount of air that can be forcefully 
    # inspired after a normal inspiration.
    IRV = 3.0

    # Tidal volume is tThe volume of air which is circulated through inhalation 
    # and expiration during one normal respiration.
    TV = 0.5

    # Expiratory reserve volume is the volume of air which can be exhaled 
    # forcefully after a normal expiration.
    ERV = 1.2

    # Residual volume is the amount of air that remains in the lungs after 
    # normal expiration.
    RV = 1.2

    Description = ""        # A Description of the lungs.

    def __init__(self):

    def __init__(self, Sex):
      if Sex == "M":
        VC = 4.6    #< Vital capacity
        IC = 3.5    #< Inspiratory capacity
        RFC = 2.3   #< Functional residual capacity
        TLC = 5.8   #< Total lung capacity
      elif Sex == "F":
        VC = 3.1
        IC = 2.4
        FRC = 1.8
        TLC = 4.2

    def IRVSet(IRV):
      if (IRV >= IRVMin and
        IRV <= IRVMax):
        self.IRV = IRV
      Update()
    
    def TVSet(TV):
      if (TV >= TVMin and 
        TV <= TVMax):
        self.TV = TV
      Update()
    
    def ERVSet(ERV):
      if (ERV >= ERVMin and 
        ERV <= ERVMax):
        self.ERV = ERV
      Update()
    
    def RVSet(RV):
      if (RV >= RVMin and 
        RV <= RVMax):
        self.RV = RV
      Update()
    
    def Update(): 
      self.VC = IRV + TV + ERV
      self.IC = IRV + TV
      self.FRC = ERV + RV
      self.TLC = IRV + TV + ERV + RV

    def DescriptionSet (Description):
        self.Description = Description

    def PrintStats ():
        print ("\nIRV:" + self:IRV + "\nTV:" + TV + "\nERV:" + "\nVC: " + VC +
              "\nIC: " + IC + "\nFRC: " + FRC "\nTLC: " + TLC)

    def PrintDetails ():
        print ("\nIRV:" + self:IRV + "\nTV:" + TV + "\nERV:" + "\nVC: " + VC +
              "\nIC: " + IC + "\nFRC: " + FRC "\nTLC: " + TLC +
              "\nDescription: \"" + Description + "\n\"")

    def PrintDescription ():
        "\nDescription:" + Description
