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
import sys

# SickBay Printing functions.
class SBPrint:
    
  @staticmethod
  def COut(Item):
    sys.stdout.write(str(Item))
    return Item
    
  @staticmethod
  def COut1(Item1, Item2):
    String = Item1 + Item2
    SBPrint.COut(String)
    return String
    
  @staticmethod
  def COut2(Item1, Item2, Item3):
    String = Item1 + Item2 + Item3
    SBPrint.COut(String)
    return String
  
  @staticmethod
  def Repeat(Item = " ", Repeat = 0, StartingString = ""):
    String = StartingString + Item * Repeat
    SBPrint.COut(String)
    return String

  # Prints the given Item indented by the given IndentationLevel
  @staticmethod
  def Indent(Item = "", IndentationLevel = 0):
    return "\n" + (IndentationLevel * " ") + Item
