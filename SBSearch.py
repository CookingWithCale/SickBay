#!/usr/bin/python
# -*- coding: utf-8 -*-
"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /SBSearch.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

from SBNode import SBNode
import time

# A SickBay search results.
class SBSearch(SBNode):
  
  def __init__(self, SickBay, SickBay.SearchCountNext(), Key = "Search", 
              Name = "Untitled search", Description = "Search results", Help = ""):
    TimeOfSearch = time.time()
    self.Members["Created"] = TimeOfSearch
    SBNode.__init__(self, SickBay, Key, "Search", Name, Description, Help)
    SickBay.Push(self)
  