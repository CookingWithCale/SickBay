/* Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /ExprI2CMbed.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef KabukiTekExprI2CMbedDecl
#define KabukiTekExprI2CMbedDecl
#include <mbed.h>
#include "BExpr.h"

namespace _ {

BExpr* EvaluateI2C (BExpr* Expr) {
  I2C* Bus = reinterpret_cast<I2C*> (Expr->Device);
  Bus->write(char(Expr->Address), Expr->BytesIn, Expr->BytesInLength);
  Bus->read(char(Expr->Address), Expr->BytesOut, Expr->BytesOutLength);
  return Expr;
}

template<int SDA, int SCL>
I2C* I2CBus () {
    static I2C Bus (SDA, SCL);
    return &Bus;
}
} //< namespace _

#undef ExprBytesInLengthMax
#undef ExprBytesOutLengthMax
#endif