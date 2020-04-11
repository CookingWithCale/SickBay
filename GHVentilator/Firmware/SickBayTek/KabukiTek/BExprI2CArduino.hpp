/* Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /ExprI2CArduino.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef KabukiTekExprI2CArduinoDecl
#define KabukiTekExprI2CArduinoDecl
#include <Wire.h>
#include "BExpr.h"

Expr* BExprEvaluateI2C (Expr* IO) {
  Wire* Bus = reinterpret_cast<I2C*> (IO.Bus);
  char* BytesIn = IO->BytesIn,
      * CommandEnd = BytesIn +  IO->CommandLength;
  if (BytesIn < CommandEnd) {
    Bus.beginTransmission(char(Address));
    while (BytesIn < CommmandEnd)
      Bus->write(*BytesIn++);
    Bus->endTransmission();
  }
  int ResponseLength = io->ResponseLength;
  char* Response = IO->Response,
      * ResponseEnd = Response +  IO->ResponseLength;
  if (Response < ResponseEnd) {
    Bus.requstFrom(char(Address), ResponseLength);
    while (Response < ResponseEnd)
      *Response++ = Bus->read();
  }
  return Expr;
}

#undef ExprCommandLengthMax
#undef ExprResponseLengthMax
#endif