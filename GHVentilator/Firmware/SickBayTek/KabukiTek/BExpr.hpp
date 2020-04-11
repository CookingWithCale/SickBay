/* Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /Print.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include "BExpr.h"

namespace _ {

BExpr* EvaluateNoOp (BExpr* Expr) { return Expr; }
       
BExpr::BExpr(BEvaluator Eval, void* Device, int Address, int Mask):
    Eval           (Eval ? Eval : EvaluateNoOp),
    Device         (Device),
    Address        (Address),
    Mask           (Mask),
    BytesOutLength (0),
    BytesInLength  (0) {}
} //< namespace _
