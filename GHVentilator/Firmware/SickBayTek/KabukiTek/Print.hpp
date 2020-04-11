/* Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /Print.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#include <iostream>
#include "Print.h"
namespace _ {
    
void Print(char Character) {
  std::cout << Character;
}

void PrintRepeat (int Count, char Token) {
    for (; Count > 0; --Count) Print (Token);
}

void PrintLine (int Count, char Token, int HorizontalTabs) {
    PrintRepeat(HorizontalTabs, '\n');
    PrintRepeat(Count, Token);
}

void PrintIndent (const char* String, char Count, char Token, 
                  int HorizontalTabs) {
    PrintRepeat(HorizontalTabs, '\n');
    PrintRepeat(Count, Token);
}

}   //< namespace _
