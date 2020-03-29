""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /human/human.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

import CirculatorySystem as cs
import RespiratorySystem as rs

# A model of a human.
def Human():
    c_height_min = 0.0        # The minimum height of a person is 0M.
    c_height_max = 10.0       # The maximum height of a person is 10M.

    c_weight_min = 0.0        # The minimum weight of a person is 0G.
    c_weight_max = 1000000.0  # The maximum weight of a person is 1000KG.

    name = ""                 # The person's name
    uid = ""                  # The unique ID of the person.
    sex = ""                  # The sex of the person.
    height = 0.0              # The person's height.
    weight = 0.0              # The person's weight.

    # The human's Circulatory system.
    circulatory = cs.DefaultCirculatorySystem()

    # The human's Respiratory system.
    respiratory = rs.DefaultRespiratorySystem()
    
    def __init__(self):
        self.data = []

    def name_set (self, name):
        self.name = name

    def uid_set (self, uid):
        self.__uid = uid
    
    def sex_set(self, sex):
        if sex == "male" or sex == "female":
            self.__sex = sex
    
    def height_set (self, height):
        if height >= c_height_min and height <= c_height_max:
            self.__height = height
    
    def weight_set (self, weight):
        if weight >= c_weight_min and weight <= c_weight_max:
            self.__weight = weight
    
    def circulatory_set(self, circulatory):
        self.__circulatory = circulatory
    
    def respiratory_set(self, respiratory):
        self.__respiratory = respiratory

    def print_stats ():
        print ("name:" + self.name + " uid:" + self.uid)
        circulatory.print_stats ()
        respiratory.print_stats ()
        
    def print_description ():
        print ("name:" + self.name + " uid:" + self.uid + " sex:" + self.sex + 
               " height:" + self.height + " weight:" + self.weight)
        circulatory.print_description ()
        respiratory.print_description ()
