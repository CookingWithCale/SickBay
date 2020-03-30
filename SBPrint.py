""" SickBay @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /SBPrint.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

class SBPrint:
  
  @staticmethod
  def Indent(self, IndentationCount):
    for X in range(0, IndentationCount):
      print(" ")
    return ""

  @staticmethod
  def Indent(IndentationCount, Item):
    SBPrintIndent(IndentationCount)
    print(Item)

  @staticmethod
  def IndentLine(IndentationCount):
    print("\n")
    return SBPrintIndent(IndentationCount)

  @staticmethod
  def IndentLine(IndentationCount, Item):
    SBPrintIndentLine(IndentationCount)
    print(Item)
