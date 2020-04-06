# !/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /SBSearch.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from SBNode import SBNode
import time

# A Crabs search results that doesn't have a NID.
class SBSearch(SBNode):
  
  def __init__(self, Parent, Type = "Search", TID = 0):
    SBNode.__init__(self, Parent, Type, TID)
    TimeOfSearch = time.time()
    self.Members["Created"] = TimeOfSearch
    Crabs.Push(self)
  