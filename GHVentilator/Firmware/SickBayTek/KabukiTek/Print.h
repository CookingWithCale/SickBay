/* Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /Print.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#ifndef MBEDBUG_DECL
#define MBEDBUG_DECL
#include <_Config.h>
#ifdef Debug
extern Serial pc;
#define DPrintf(...) pc.printf(__VA_ARGS__)
#define DPrintLine(Count, Token) PrintLine(Count, Token);
#define DPrintIndent(Count, Token) PrintIndent(Count, Token);
#else
#define DPrintf(...)
#define DPrintLine(Count, Token)
#define DPrintIndent(Count, Token)
#endif
namespace _ {

/* Prints a single char to the stdout. */
void Print (char Char);

/* Prints a line with the given token and number of columns to the debug
stream. */
void PrintLine (int Count = 80, char Token = '-', int HorizontalTabs = 1);

/* Prints a vertical tab with the given number of rows. */
void PrintIndent (const char* String, int Count = 10, char Token = ' ', 
                  int HorizontalTabs = 1);
}  //< _
#endif
