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
    IRV_MIN = 0.0          # The min IRV value.
    IRV_MAX = 100.0        # The max IRV value.

    TV_MIN = 0.0           # The min TV value.
    TV_MAX = 100.0         # The max TV value.

    ERV_MIN = 0.0          # The min ERV value.
    ERV_MAX = 100.0        # The max ERV value.

    TV_MIN = 0.0           # The min RV value.
    TV_MAX = 100.0         # The max RV value.

    # Inspiratory reserve volume is the amount of air that can be forcefully 
    # inspired after a normal inspiration.
    irv = 3.0

    # Tidal volume is tThe volume of air which is circulated through inhalation 
    # and expiration during one normal respiration.
    tv = 0.5

    # Expiratory reserve volume is the volume of air which can be exhaled 
    # forcefully after a normal expiration.
    erv = 1.2

    # Residual volume is the amount of air that remains in the lungs after 
    # normal expiration.
    rv = 1.2

    description = ""        # A description of the lungs.

    def __init__(self):
        self.data = []

    # Sets the pulse
    # @return 0 upon success; -1 if too low; +1 if too high
    def pulse_set (pulse):
        if (pulse < cPulseMin) return -1
        if (pulse > cPulseMax) return 1
        self.pulse = pulse
        return 0

    def description_set (description):
        self.description = sex

    def print_stats ():
        "pulse:" + self.pulse

    def print_description ():
        "description:" + description
