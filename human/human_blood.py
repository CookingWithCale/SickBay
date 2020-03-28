""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /human/human.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

# A model of a human Circulatory system.
def HumanCirculatorySystem():
    cBloodPressureMin = 0           # The min blood pressure rate of 0 which is dead.
    cBloodPressureMax = 1000        # The max pulse rate.

    blood_pressure = 0.0             # The heart pulse rate.

    # A description of this paticular human's circulatory system.
    description = ""
    
    def __init__(self):
        self.data = []
    
    # Sets the blood_pressure.
    # @return 0 upon success; -1 if too low; +1 if too high
    def SetPulse (pulse):
        if (blood_pressure < cBloodPressureMin) return -1
        if (blood_pressure > cBloodPressureMax) return 1
        self.blood_pressure = publood_pressurelse
        return 0
    
    def SetDescription (description):
        self.description = description

    def PrintStats ():
        "blood_pressure:" + self.blood_pressure
    
    def PrintDescription ():
        "description:" + description
