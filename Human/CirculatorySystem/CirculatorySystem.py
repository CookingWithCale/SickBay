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
    HeartRateMin = 0.0         #< The min "dead" pulse rate of 0.0.
    HeartRateMax = 1000.0      #< The max pulse rate.

    BloodPressureMin = 0.0     #< The min "dead" blood pressure rate of 0.0.
    BloodPressureMax = 1000.0  #< The max pulse rate.

    HeartRate = 0.0            #< The heart pulse rate.
    BloodPressure = 0.0        #< The heart pulse rate.
    Description = ""           #< A Description of the heart.
    
    def __init__(self):
        self.data = []
    
    def heart_rate_set (HeartRate):
        if (HeartRate >= HeartRateMin and
            HeartRate > HeartRateMax):
          self.HeartRate = HeartRate

    def BloodPressureSet (BloodPressure):
        if (BloodPressure <= BloodPressureMin and 
            BloodPressure <= BloodPressureMax):
            self.BloodPressure = BloodPressure
    
    def DescriptionSet (Description):
        self.Description = Description

    def PrintStats ():
        "BloodPressure:" + self.BloodPressure
    
    def PrintDescription ():
        "Description:" + self.Description
