""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /respiratory/ventilators/ventilator.gravity_hookah/gh_ventilator.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

def GHVentilator():
    type = "GH Ventilator"   # The only type of Ventilator we support right now.
    def __init__(self):
        self.data = []

    def PrintStatus ():
        print ("Foo")
