/* Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /Print.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef KabukiTekExprDecl
#define KabukiTekExprDecl
#include "_Config.h"
#ifndef BExprBytesInLengthMax
#define BExprBytesInLengthMax 16
#endif
#ifndef BExprBytesOutLengthMax
#define BExprBytesOutLengthMax 16
#endif

namespace _ {
class BExpr;
}

/* A Byte-in-byte-out expression evaluator operating on the Device. */
typedef _::BExpr* (*BEvaluator)(_::BExpr* Expr);

namespace _ {
    
/* BEvaluator that does nothing. */
BExpr* EvaluateNoOp (BExpr* Expr);

/* A Byte-in-Byte-out expression. */   
class BExpr {
  public:
  
  enum {
    BytesInLengthMax = BExprBytesInLengthMax,
    BytesOutLengthMax = BExprBytesInLengthMax,
  };
  
  BEvaluator Eval;      //< The BEvaluator for this Expression.
  void* Device;         //< The Device this is being evaluated on.
  int   Address,        //< The I2C, SPI CS, Crabs Device, etc Address.
        Mask,           //< The SPI CS, Crabs Device, etc Address Mask.
        BytesOutLength,  //< The length of the expected response.
        BytesInLength;   //< The length of the BytesIn being written.
  char  BytesOut[BytesOutLengthMax], //< A syncronous BytesOut to a BytesIn.
        BytesIn[BytesInLengthMax];   //< A BytesIn for a sync or async BytesOut.
  
  /* Stores the default values or non-default parameters. */
  BExpr(BEvaluator Eval = EvaluateNoOp, void* Device = nullptr, 
        int Address = nullptr, int Mask = 0);
  
  /* Evaluates this Expr on the given Device. */
  inline BExpr* Evaluate () { return Eval(this); }
  
  /* Ammends the given String to the BytesIn. */
  inline BExpr* Ammend (const char* BytesInString) {
    if (!BytesInString) return this;
    int BytesOutLength = this->BytesOutLength;
    char* Cursor = BytesOut + BytesOutLength;
    char Char = *BytesInString++;
    while (Char) {
      *Cursor = Char;
      Char = *BytesInString++;
    }
    return this;
  }
  
  inline BExpr* Ammend (char A) {
    ++this->BytesOutLength;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    return this;
  }
  
  inline BExpr* Ammend (char A, char B) {
    this->BytesOutLength += 2;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    *Cursor = B;
    return this;
  }
  
  inline BExpr* Ammend (char A, char B, char C) {
    this->BytesOutLength += 3;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    *Cursor++ = B;
    *Cursor = C;
    return this;
  }
  
  inline BExpr* Ammend (char A, char B, char C, char D) {
    this->BytesOutLength += 4;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    *Cursor++ = B;
    *Cursor++ = C;
    *Cursor = D;
    return this;
  }
  
  inline BExpr* Ammend (char A, char B, char C, char D, char E) {
    this->BytesOutLength += 5;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    *Cursor++ = B;
    *Cursor++ = C;
    *Cursor++ = D;
    *Cursor = E;
    return this;
  }
  
  inline BExpr* Ammend (char A, char B, char C, char D, char E, char F) {
    this->BytesOutLength += 6;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    *Cursor++ = B;
    *Cursor++ = C;
    *Cursor++ = D;
    *Cursor++ = E;
    *Cursor = F;
    return this;
  }
  
  inline BExpr* Ammend (char A, char B, char C, char D, char E, char F, 
                            char G) {
    this->BytesOutLength += 7;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    *Cursor++ = B;
    *Cursor++ = C;
    *Cursor++ = D;
    *Cursor++ = E;
    *Cursor++ = F;
    *Cursor = G;
    return this;
  }
  
  inline BExpr* Ammend (char A, char B, char C, char D, char E, char F, 
                            char G, char H) {
    this->BytesOutLength += 8;
    char* Cursor = BytesOut + BytesOutLength;
    *Cursor++ = A;
    *Cursor++ = B;
    *Cursor++ = C;
    *Cursor++ = D;
    *Cursor++ = E;
    *Cursor++ = F;
    *Cursor++ = G;
    *Cursor = H;
    return this;
  }

  inline BExpr* OI (int BytesOutLength) {
    this->BytesOutLength = BytesOutLength;
    return this;
  }
  
  inline BExpr* OI (int BytesOutLength, char A) {
    this->BytesInLength = 1;
    return Ammend (A);
  }
  
  inline BExpr* OI (int BytesOutLength, char A, char B) {
    this->BytesInLength = 2;
    return Ammend (A, B);
  }
  
  inline BExpr* OI (int BytesOutLength, char A, char B, char C) {
    this->BytesInLength = 3;
    return Ammend (A, B, C);
  }
  
  inline BExpr* OI (int BytesOutLength, char A, char B, char C, char D) {
    this->BytesInLength = 4;
    return Ammend (A, B, C, D);
  }
  
  inline BExpr* OI (int BytesOutLength, char A, char B, char C, char D, 
                    char E) {
    this->BytesInLength = 5;
    return Ammend (A, B, C, D, E);
  }
  
  inline BExpr* OI (int BytesOutLength, char A, char B, char C, char D, 
                    char E, char F) {
    this->BytesInLength = 6;
    return Ammend (A, B, C, D, E, F);
  }
  
  inline BExpr* OI (int BytesOutLength, char A, char B, char C, char D, 
                    char E, char F, char G) {
    this->BytesInLength = 7;
    return Ammend (A, B, C, D, E, F, G);
  }
  
  inline BExpr* OI (int BytesOutLength, char A, char B, char C, char D, 
                    char E, char F, char G, char H) {
    this->BytesInLength = 8;
    return Ammend (A, B, C, D, E, F, G, H);
  }
};
} //< namespace _
#undef BExprBytesInLengthMax
#undef BExprBytesOutLengthMax
#endif