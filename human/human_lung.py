""" Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /human/human.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

# A model of a human heart.
def HumanHeart():
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

    cPulseMin = 0           # The min pulse rate of 0 which is dead.
    cPulseMax = 1000        # The max pulse rate.
    
    def __init__(self):
        self.data = []
    
    # Sets the pulse
    # @return 0 upon success; -1 if too low; +1 if too high
    def SetPulse (pulse):
        if (pulse < cPulseMin) return -1
        if (pulse > cPulseMax) return 1
        self.pulse = pulse
        return 0
    
    def SetDescription (description):
        self.description = sex

    def PrintStats ():
        "pulse:" + self.pulse
    
    def PrintDescription ():
        "description:" + description
