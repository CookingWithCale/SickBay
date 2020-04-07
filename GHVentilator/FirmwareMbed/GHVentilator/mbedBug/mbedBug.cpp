/** mbedbug @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /mbedbug.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#include "mbedBug.h"
namespace mbedBug {

void PrintLine (int Count, char Token) {
    char Buffer[Count + 1];
    memset (&Buffer[0], Token, Count);
    printf ("\r\n%s\r\n", Buffer);
}

void PrintIndent (const char* String, char Count, char Token) {
    char Buffer[Count + 1];
    memset (&Buffer[0], Token, Count);
    printf ("\r%s", Buffer);
}

}   //< namespace mbedBug
