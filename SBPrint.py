#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBPrint.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

# Constants
SBPrintSpacesPerIndent = 2  #< The number of spaces per indentation level.

# SickBay Printing functions.
class SBPrint:
  
  # Prints the Item repeatedly NTimes
  @staticmethod
  def Repeat(NTimes, Item = " "):
    for X in range(NTimes):
      print(Item)
    return ""

  # Prints the given Item indented by the given IndentationLevel
  @staticmethod
  def Indent(IndentationLevel, Item = ""):
    SBPrint.Repeat(IndentationLevel * SBPrintSpacesPerIndent, " ")
    print(Item)
