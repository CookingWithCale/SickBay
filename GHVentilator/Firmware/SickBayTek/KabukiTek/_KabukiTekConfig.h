/** _ @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /_Config.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#ifndef KabukiTek_KabukiTekConfigDecl
#define KabukiTek_KabukiTekConfigDecl
#include <stdint.h>
#ifndef nullptr
#define nullptr 0
#endif
#ifndef KabukiTekLLLow
#define KabukiTekLLLow 0
#endif
#ifndef KabukiTekLLHigh
#define KabukiTekLLHigh 1
#endif
// Define LLLow and LLHigh before you #include "SBVentilator.hpp"
enum {
  LLLow  = KabukiTekLLLow, //< Logic-level Low.
  LLHigh = KabukiTekLLHigh, //< Logic-level High.
};
#undef KabukiTekLLLow
#undef KabukiTekLLHigh
#endif 
