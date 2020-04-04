# !/usr/bin/python
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
StringfTabSize = 2  #< The number of spaces per indentation level.

# String formating utilities
class Stringf:
  
  @staticmethod
  def Repeat(Repeat = 0, Item = " ", StartingString = ""):
    return StartingString + Item * Repeat

  @staticmethod
  def Indent(IndentLevel = 0, Item = "", StartingString = "\n"):
    SpaceCount = int(IndentLevel * StringfTabSize)
    return StartingString + (" " * SpaceCount) + Item

# SickBay Printing functions that print to the COut.
class COut:
    
  @staticmethod
  def Print(Item):
    sys.stdout.write(str(Item))
    return Item
    
  @staticmethod
  def Print2(Item1, Item2):
    String = str(Item1) + str(Item2)
    COut.Print(String)
    return String
    
  @staticmethod
  def Print3(Item1, Item2, Item3):
    String = str(Item1) + str(Item2) + str(Item3)
    COut.Print(String)
    return String
    
  @staticmethod
  def Print4(Item1, Item2, Item3, Item4):
    String = str(Item1) + str(Item2) + str(Item3) + str(Item4)
    COut.Print(String)
    return String
    
  @staticmethod
  def Print5(Item1, Item2, Item3, Item4, Item5):
    String = str(Item1) + str(Item2) + str(Item3) + str(Item4) + str(Item5)
    COut.Print(String)
    return String
  
  @staticmethod
  def Repeat(Repeat = 0, Item = " ", StartingString = ""):
    String = StartingString + Item * Repeat
    COut.Print(String)
    return String

  # Prints the given Item indented by the given IndentLevel
  @staticmethod
  def Indent(IndentLevel = 0, Item = "", StartingString = "\n"):
    String = Stringf.Indent(IndentLevel, Item, StartingString)
    COut.Print(String)
    return String
