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
#include <mbed.h>

Expr* EvaluateSPIBus (Expr* Expr) {
  SPI* Bus = reinterpret_cast<SPI*> (Device->Device);
  int ArgsInLength = Expr->ArgsInLength,
      ArgsOutLength = Expr->ArgsOutLength;
  char* BytesIn = Expr->BytesIn,
      * ArgsInEnd = BytesIn +  Expr->ArgsInLength;
  char* ArgsOut = Expr->ArgsOut,
      * ArgsOutEnd = ArgsOut +  Expr->ArgsOutLength;
  while (BytesIn < ArgsInEnd && ArgsOut < ArgsOutEnd) {
    char ArgsInByte;
    if (BytesIn < ArgsInEnd) ArgsInByte = *BytesIn++;
    else ArgsInByte = 0;
    char ArgsOutByte = SPI->write (ArgsInByte);
    if (ArgsOut < ArgsOutLength) *ArgsOut++ = ArgsOutByte;
  }
  Expr->ArgsOutLength = ArgsOutEnd - ArgsOut;
  return Expr;
}

template<int MOSI = D1, int MISO = D0, int Address = 0, int Mask = 0>
SPI* SPIBus () {
    static SPI Bus (SDA, SCL);
    return &Bus;
}

#undef ExprArgsInLengthMax
#undef ExprArgsOutLengthMax
#endif