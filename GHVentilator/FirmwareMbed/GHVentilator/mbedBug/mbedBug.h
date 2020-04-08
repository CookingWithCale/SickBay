/** mbedbug @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /mbedbug.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#ifndef MBEDBUG_DECL
#define MBEDBUG_DECL
#include <mbedBugConfig.h>
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
namespace mbedBug {

/* Prints a line with the given token and number of columns to the debug
stream. */
void PrintLine (int Count = 80, char Token = '-');

/* Prints a vertical tab with the given number of rows. */
void PrintIndent (const char* String, int Count = 10, char Token = ' ');
}  //< mbedBug
#endif
