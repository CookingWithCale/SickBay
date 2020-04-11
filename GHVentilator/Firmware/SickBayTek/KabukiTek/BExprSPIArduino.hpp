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
#include "BExpr.h"
#include <Arduino.h>

Expr* EvaluateSPI (Expr* Expr) {
  int BytesInLength = Expr->BytesInLength,
      BytesOutLength = Expr->BytesOutLength;
  char* BytesIn = Expr->BytesIn,
      * BytesInEnd = BytesIn +  Expr->BytesInLength;
  char* BytesOut = Expr->BytesOut,
      * BytesOutEnd = BytesOut +  Expr->BytesOutLength;
  while (BytesIn < BytesInEnd && BytesOut < BytesOutEnd) {
    char BytesInByte;
    if (BytesIn < BytesInEnd) BytesInByte = *BytesIn++;
    else BytesInByte = 0;
    char BytesOutByte = SPI.transfer (BytesInByte);
    if (BytesOut < BytesOutLength) *BytesOut++ = BytesOutByte;
  }
  Expr->BytesOutLength = BytesOutEnd - BytesOut;
  return Expr;
}

#undef ExprBytesInLengthMax
#undef ExprBytesOutLengthMax
#endif