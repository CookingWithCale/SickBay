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
    HEART_RATE_MIN = 0.0         #< The min "dead" pulse rate of 0.0.
    HEART_RATE_MIN = 1000.0      #< The max pulse rate.

    BLOOD_PRESSURE_MIN = 0.0     #< The min "dead" blood pressure rate of 0.0.
    BLOOD_PRESSURE_MAX = 1000.0  #< The max pulse rate.

    heart_rate = 0.0            #< The heart pulse rate.
    blood_pressure = 0.0        #< The heart pulse rate.
    description = ""            #< A description of the heart.
    
    def __init__(self):
        self.data = []
    
    def heart_rate_set (heart_rate):
        if (heart_rate >= c_pulse_min and
            heart_rate > c_pulse_max):
          self.heart_rate = heart_rate

    def blood_pressure_set (blood_pressure):
        if (blood_pressure <= c_blood_pressure_min and 
            blood_pressure <= c_blood_pressure_max):
            self.blood_pressure = blood_pressure
    
    def description_set (description):
        self.description = description

    def print_stats ():
        "blood_pressure:" + self.blood_pressure
    
    def print_description ():
        "description:" + self.description
