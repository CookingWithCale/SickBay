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
#include <stdint.h>
#include <mbed.h>
#ifndef nullptr
#define nullptr 0
#endif
namespace mbedbug {

/* Prints a line with the given token and number of columns to the debug
stream. */
void PrintLine (int ColumnWidth = 80, char Token = '-');

/* Prints a vertical tab with the given number of rows. */
void PrintVerticalTab (int NumRows = 10);
}
#endif
