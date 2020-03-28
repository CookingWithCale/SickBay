""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /human/human.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

# A model of a human.
def Human():
    name = ""               # The person's name
    sex = ""                # The sex of the person.
    height = 0.0            # The person's height.
    weight = 0.0            # The person's weight.

    c_weight_max = 1000     #
    
    def __init__(self):
        self.data = []
    
    def SetName (name):
        self.name = name
    
    def SetSex (sex):
        self.sex = sex
    
    def SetHeight (height):
        if (height < 0) return

        self.height = height

    def PrintStats ():
        "name:%s sex:%s height:%s weight:%s" % (self.name, self.sex, self.kind, self.value)
        print ("\nheight: " + height + "\nideal_weight: " + ideal_weight)
