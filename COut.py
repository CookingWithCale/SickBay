#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /COut.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.
import sys

# Constants
COutSpacesPerIndent = 2  #< The number of spaces per indentation level.

# SickBay Printing functions.
class COut:
    
  @staticmethod
  def Print(Item):
    sys.stdout.write(str(Item))
    return Item
    
  @staticmethod
  def Print2(Item1, Item2):
    String = Item1 + Item2
    COut.Print(String)
    return String
    
  @staticmethod
  def Print3(Item1, Item2, Item3):
    String = Item1 + Item2 + Item3
    COut.Print(String)
    return String
  
  @staticmethod
  def Repeat(Item = " ", Repeat = 0, StartingString = ""):
    String = StartingString + Item * Repeat
    COut.Print(String)
    return String

  # Prints the given Item indented by the given IndentationLevel
  @staticmethod
  def Indent(IndentationLevel = 0, Item = ""):
    SpaceCount = int(IndentationLevel * COutSpacesPerIndent)
    String = "\n"
    #Spaces *= SpaceCount  #< This doesn't work for some reason???
    for x in range(SpaceCount):
      String += " "
    String += Item
    COut.Print(String)
    return String
