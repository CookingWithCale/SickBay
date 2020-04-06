# !/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /GHVentilator.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at <https://mozilla.org/MPL/2.0/>.

from GHVentilatorChannel import *

# A Gravity Hookah Ventilator
class GHVentilator(SBDevice):

  # Creates a Duck.
  def __init__(self, Crabs, TID, Type ="Device.Ventilator.GHVentilator"):
    SBDevice.__init__(self, Crabs, TID, Type)
