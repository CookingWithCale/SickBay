#!/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /Stringf.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.
import sys

# Constants
StringfSpacesPerIndent = 2  #< The number of spaces per indentation level.

# SickBay Printing functions.
class Stringf:
    
  @staticmethod
  def COut(Item):
    sys.stdout.write(str(Item))
    return Item
    
  @staticmethod
  def COut1(Item1, Item2):
    String = Item1 + Item2
    Stringf.COut(String)
    return String
    
  @staticmethod
  def COut2(Item1, Item2, Item3):
    String = Item1 + Item2 + Item3
    Stringf.COut(String)
    return String
  
  @staticmethod
  def Repeat(Item = " ", Repeat = 0, StartingString = ""):
    String = StartingString + Item * Repeat
    Stringf.COut(String)
    return String

  # Prints the given Item indented by the given IndentationLevel
  @staticmethod
  def Indent(IndentationLevel = 0, Item = ""):
    SpaceCount = int(IndentationLevel * StringfSpacesPerIndent)
    String = "\n"
    #Spaces *= SpaceCount  #< This doesn't work for some reason???
    for x in range(SpaceCount):
      String += " "
    return String + Item
