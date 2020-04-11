/** Kabuki Tek @version 0.x
@link  https://github.com/KabukiStarship/KabukiTek.git
@file  /BMP280.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#include <BMP280.h>

namespace _ {
BMP280::BMP280() :
    t_fine(0) {}
    
void BMP280::Init(BEvaluator Eval, void* Device, int Address, int Mask) {
    Expr.Eval     = Eval;
    Expr.Device   = Device;
    Expr.Address  = Address;
    Expr.Mask     = Mask;
    char* BytesIn = Expr.BytesIn;
 
    //Expr.OI (0, 0xf2 , //< ctrl_hum 
    //         0x01)->Evaluate (); //< Humidity oversampling x1
    
    // Temparature oversampling x1, Pressure oversampling x1, Normal mode.
    //char TOSX1POSX1NM = 0x27;
    
    Expr.OI (0, 0xf4 /* ctrl_meas */, 
             0b01010111 /* Temparature oversampling x2 010, Pressure  
                           oversampling x16 101, Normal mode 11 */
            )->Evaluate();
 
    Expr.OI (0, 0xf5 /* config */, 
             0b10111100 /* Standby 1000ms, Filter x16 */)->Evaluate ();
 
    Expr.OI(6, 0x88 /*read dig_T regs */)->Evaluate ();
 
    dig_T1 = (BytesIn[1] << 8) | BytesIn[0];
    dig_T2 = (BytesIn[3] << 8) | BytesIn[2];
    dig_T3 = (BytesIn[5] << 8) | BytesIn[4];
 
    Expr.OI(18, 0x8E /* read dig_P regs */)->Evaluate ();
 
    dig_P1 = (BytesIn[ 1] << 8) | BytesIn[ 0];
    dig_P2 = (BytesIn[ 3] << 8) | BytesIn[ 2];
    dig_P3 = (BytesIn[ 5] << 8) | BytesIn[ 4];
    dig_P4 = (BytesIn[ 7] << 8) | BytesIn[ 6];
    dig_P5 = (BytesIn[ 9] << 8) | BytesIn[ 8];
    dig_P6 = (BytesIn[11] << 8) | BytesIn[10];
    dig_P7 = (BytesIn[13] << 8) | BytesIn[12];
    dig_P8 = (BytesIn[15] << 8) | BytesIn[14];
    dig_P9 = (BytesIn[17] << 8) | BytesIn[16];
 
    /*
    Expr.OI(1, 0xA1)->Evaluate (); //< Read dig_H regs
    Expr.OI(7, 0xE1)->Evaluate (); //< Read dig_H regs

    dig_H1 = BytesIn[0];
    dig_H2 = (BytesIn[2] << 8) | BytesIn[1];
    dig_H3 = BytesIn[3];
    dig_H4 = (BytesIn[4] << 4) | (BytesIn[5] & 0x0f);
    dig_H5 = (BytesIn[6] << 4) | ((BytesIn[5]>>4) & 0x0f);
    dig_H6 = BytesIn[7];
*/
}
 
int32_t BMP280::Temperature() {
    Expr.OI(3, 0xfa)->Evaluate();
 
    int32_t temp_raw = (Expr.BytesOut[0] << 12) | (Expr.BytesOut[1] << 4) | 
                       (Expr.BytesOut[2] >> 4);
    int32_t temp1, temp2,temp;
 
    temp1 =((((temp_raw >> 3) - (dig_T1 << 1))) * dig_T2) >> 11;
    temp2 =(((((temp_raw >> 4) - dig_T1) * 
            ((temp_raw >> 4) - dig_T1)) >> 12) * dig_T3) >> 14;
    t_fine = temp1+temp2;
    temp = (t_fine * 5 + 128) >> 8;
    return temp;
}
 
uint32_t BMP280::Pressure() {
    Expr.OI (3, 0xf7)->Evaluate ();
 
    int32_t BytesOut = (Expr.BytesOut[1] << 12) | (Expr.BytesOut[2] << 4) | 
                       (Expr.BytesOut[3] >> 4);
    
    int32_t var1, var2;
    uint32_t Result;
 
    var1 = (t_fine >> 1) - 64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * dig_P6;
    var2 = var2 + ((var1 * dig_P5) << 1);
    var2 = (var2 >> 2) + (dig_P4 << 16);
    var1 = (((dig_P3 * (((var1 >> 2)*(var1 >> 2)) >> 13)) >> 3) +  
           ((dig_P2 * var1) >> 1)) >> 18;
    var1 = ((32768 + var1) * dig_P1) >> 15;
    if (var1 == 0) {
        return 0;
    }
    Result = (((1048576 - BytesOut) - (var2 >> 12))) * 3125;
    if(Result < 0x80000000) {
        Result = (Result << 1) / var1;
    } else {
        Result = (Result / var1) * 2;
    }
    var1 = ((int32_t)dig_P9 * ((int32_t)(((Result >> 3) * 
            (Result >> 3)) >> 13))) >> 12;
    var2 = (((int32_t)(Result >> 2)) * (int32_t)dig_P8) >> 13;
    return (Result + ((var1 + var2 + dig_P7) >> 4));
}
} //< namespace _
