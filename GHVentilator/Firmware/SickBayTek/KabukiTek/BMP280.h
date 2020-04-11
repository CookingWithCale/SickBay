/** Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /BMP280.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef BME280MbedDecl
#define BME280MbedDecl
#include "_Config.h"
#include <BExpr.h>
 
//#define _DEBUG
// default Address with SDO High 0x77
// Address with SDO LOW 0x76
#define BMP280SlaveAddressDefault (0x77)

namespace _ {

/* A BME280 atmospheric pressure, temperature, and humidity sensor.
Data sheet @link https://bit.ly/2Vi7i50 */
class BMP280 {
  public:

  enum {
    // The default I2C slave Address of a BMP280.
    AddressDefault  = BMP280SlaveAddressDefault,
    AddressSpiCS0 = -1, //< If using SPI, -1 is CS0, -2 is CS1, and so on.
    IOLengthMax   = 18, //< The maximum length of a BArgsIn or Response.
  };
  
  BExpr   Expr;    //< The I2C, Serial, Interproces, etc bus this is on.
  int32_t t_fine;  //< ???

  /* Creates a BME280 instance connected to the I2C pins and Address. */
  BMP280();

  /* Initializes the BMP280.
  @param SlaveAddress (option) I2C-bus Address (default: 0x77) */
  void Init(BEvaluator Eval, void* Device, 
            int Address = BMP280SlaveAddressDefault,
            int Mask = 0);

  /* Read the current temperature in degrees Celsius times 100. */
  int32_t Temperature();

  /* The current pressure in hectopascal times 100. */
  uint32_t Pressure();
  
  private:
  
  uint16_t dig_T1,
                  dig_P1,
                  dig_H1,
                  dig_H3;
  int16_t  dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, 
                  dig_P7, dig_P8, dig_P9, dig_H2, dig_H4, dig_H5, dig_H6;
};
} //< namespace _
#undef BMP280SlaveAddressDefault
#endif
 