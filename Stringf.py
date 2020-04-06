# !/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /Stringf.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.
import sys

# Constants
StringfTabSize = 1  #< The number of spaces per indentation level.

# String formating utilities
class Stringf:
  
  @staticmethod
  def Repeat(Repeat = 0, Item = " ", StartingString = ""):
    return StartingString + Item * Repeat
  
  # Indents to Item the given IndentLevel * StringfTabSize.
  # @param StartingString The string to print first that starts with a new line 
  #   char.
  @staticmethod
  def Indent(IndentLevel = 0, Item = "", StartingString = "\n", Delimiter = " "):
    SpaceCount = int(IndentLevel * StringfTabSize)
    return StartingString + (Delimiter * SpaceCount) + Item

  # Skips the leading whitespace as cursor value.
  def SkipWhitespace(String, Cursor = 0):
    if String == None or Cursor >= len(String): return Cursor
    Char = String[Cursor]
    while Char < ' ':
      Cursor += 1
      if Cursor >= len(String): return Cursor
      Char = String[Cursor]
    return Cursor
  
  # Gets the Cursor index of the next whitespace, nil-term char, or 
  # non-printable character.
  @staticmethod
  def TokenNext(String, Cursor = 0):
    if String == None or Cursor >= len(String): return Cursor
    #print('\n? Scanning String="' + String + '" Cursor=' + str(Cursor) + 
    #      ' Token="')
    Char = String[Cursor]
    while Char > ' ':
      sys.stdout.write(Char)
      Cursor += 1
      if Cursor >= len(String): return Cursor
      Char = String[Cursor]
    #print('" <')
    return Cursor
  
  # Peeks the next int or float from the betting of the String.
  # @pre You must string the leading whitespace before calling this function.
  # @return 0 if the String doesn't start with a int or a float,
  #         a positive number of characters means it's an int, and
  #         a negative number of characters means it's a float
  @staticmethod
  def PeekNumber(String, Cursor = 0):
    if String == None or Cursor >= len(String): return Cursor
    CursorStart = Cursor
    Char = String[Cursor]
    if Char == '-':
      Cursor += 1
      Char = String[Cursor]
    IsInt = True
    if Char == '.': 
      IsInt = False
      Cursor += 1
      Char = String[Cursor]
    while Char >= '0' and Char <= '9':
      Cursor += 1
      Char = String[Cursor]
    if Char < ' ' and IsInt:
      return Cursor - CursorStart
    if Char == '.':
      # Scanning fraction part of the decimal.
      Cursor += 1
      Char = String[Cursor]
      while Char >= '0' and Char <= '9':
        Cursor += 1
        Char = String[Cursor]
    if Char == 'E' or Char == 'e':
      Cursor += 1
      Char = String[Cursor]
      if Char == '-':
        Cursor += 1
        Char = String[Cursor]
      if Char < '0' or Char > '9': return 0
      while Char >= '0' and Char <= '9':
        Cursor += 1
        Char = String[Cursor]
      if Char > ' ': return None
    return -(Cursor - CursorStart)

  # Peeks at the value to see if it's a string or a token
  # @pre You must string the leading whitespace before calling this function.
  # @return 0 if the String doesn't start with a String or Token,
  #         a positive number of characters means it's a String, and
  #         a negative number of characters means it's a Token.
  def PeekString(self, String, Cursor, End):
    if String == None or Cursor >= len(String): return None
    Char = String[Cursor]
    Quote = "'"
    if Char == '"':
      Quote = '"'
    if Char == Quote:
      Cursor += 1
      Char = String[Cursor]
      if Char < ' ': 
        print("><> ? Found end of string before the end of quote. <")
        return 0
      while Char != Quote:
        Cursor += 1
        Char = String[Cursor]
        if Char < ' ': return 0
      return Cursor
    Cursor = Stringf.SkipWhitespace(String, Cursor)
    TokenEnd = Stringf.TokenNext(String, Cursor)
    if Cursor == TokenEnd: return 0
    return -(TokenEnd - Cursor)
    
# Crabs Printing functions that print to the COut.
class COut:
    
  @staticmethod
  def Print(Item):
    if Item: sys.stdout.write(str(Item))
    return Item
    
  @staticmethod
  def PrintLn(Item):
    sys.stdout.write('\n')
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
  def Indent(IndentLevel = 0, Item = "", StartingString = "\n", Delimiter = " "):
    String = Stringf.Indent(IndentLevel, Item, StartingString, Delimiter)
    COut.Print(String)
    return String
