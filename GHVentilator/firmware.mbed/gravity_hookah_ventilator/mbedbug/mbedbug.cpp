/** mbedbug @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /mbedbug.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#include "mbedbug.h"
namespace mbedbug {

void PrintLine (int numColumns, char token) {
    char buffer[numColumns + 1];
    memset (&buffer[0], token, numColumns);
    printf ("\r\n%s\r\n", buffer);
}

void printLine (char numRows) {
    char buffer[numRows + 1];
    memset (&buffer[0], '\n', numRows);
    printf ("\r%s", buffer);
}

}   //< namespace mbedbug
