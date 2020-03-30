""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /RespiratorySystem/RespiratorySystem.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

# A model of a human heart.
def RespiratorySystem():
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
        self.data = []

    def IRVSet(IRV):
        if (IRV >= IRVMin and
            IRV <= IRVMax):
            self.IRV = IRV
    
    def TVSet(TV):
        if (TV >= TVMin and 
            TV <= TVMax):
            self.TV = TV
    
    def ERVSet(ERV):
        if (ERV >= ERVMin and 
            ERV <= ERVMax):
            self.ERV = ERV
    
    def RVSet(RV):
        if (RV >= RVMin and 
            RV <= RVMax):
            self.RV = RV

    def DescriptionSet (Description):
        self.Description = Description

    def PrintStats ():
        "\nIRV:" + self:IRV + "\nTV:" + TV + "\nERV:" + 

    def PrintDescription ():
        "\nDescription:" + Description
