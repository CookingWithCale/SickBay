/** Kabuki Tek Toolkit @version 0.x
@link  https://github.com/KabukiStarship/KabukiToolkitTek.git
@file  /BMP280.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#include "BMP280.h"

BMP280::BMP280(I2C &Bus, char BusAddress) :
    Bus(Bus),
    BusAddress(BusAddress<<1),
    t_fine(0)
{
    Initialize();
}
    
void BMP280::Initialize()
{
    char cmd[18];
 
    //cmd[0] = 0xf2; // ctrl_hum
    //cmd[1] = 0x01; // Humidity oversampling x1
    //Bus.write(BusAddress, cmd, 2);
 
    cmd[0] = 0xf4; // ctrl_meas
    //cmd[1] = 0x27; // Temparature oversampling x1, Pressure oversampling x1, Normal mode
    cmd[1] = 0b01010111; // Temparature oversampling x2 010, Pressure oversampling x16 101, Normal mode 11
    Bus.write(BusAddress, cmd, 2);
 
    cmd[0] = 0xf5; // config
    cmd[1] = 0b10111100; // Standby 1000ms, Filter x16
    Bus.write(BusAddress, cmd, 2);
 
    cmd[0] = 0x88; // read dig_T regs
    Bus.write(BusAddress, cmd, 1);
    Bus.read(BusAddress, cmd, 6);
 
    dig_T1 = (cmd[1] << 8) | cmd[0];
    dig_T2 = (cmd[3] << 8) | cmd[2];
    dig_T3 = (cmd[5] << 8) | cmd[4];
 
    //DPrintf("dig_T = 0x%x, 0x%x, 0x%x\n\r", dig_T1, dig_T2, dig_T3);
    //DPrintf("dig_T = %d, %d, %d\n\r", dig_T1, dig_T2, dig_T3);
 
    cmd[0] = 0x8E; // read dig_P regs
    Bus.write(BusAddress, cmd, 1);
    Bus.read(BusAddress, cmd, 18);
 
    dig_P1 = (cmd[ 1] << 8) | cmd[ 0];
    dig_P2 = (cmd[ 3] << 8) | cmd[ 2];
    dig_P3 = (cmd[ 5] << 8) | cmd[ 4];
    dig_P4 = (cmd[ 7] << 8) | cmd[ 6];
    dig_P5 = (cmd[ 9] << 8) | cmd[ 8];
    dig_P6 = (cmd[11] << 8) | cmd[10];
    dig_P7 = (cmd[13] << 8) | cmd[12];
    dig_P8 = (cmd[15] << 8) | cmd[14];
    dig_P9 = (cmd[17] << 8) | cmd[16];
 
    //DPrintf("dig_P = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", 
    //        dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, 
    //        dig_P9);
 
  /*  cmd[0] = 0xA1; // read dig_H regs
    Bus.write(BusAddress, cmd, 1);
    Bus.read(BusAddress, cmd, 1);
     cmd[1] = 0xE1; // read dig_H regs
    Bus.write(BusAddress, &cmd[1], 1);
    Bus.read(BusAddress, &cmd[1], 7);

    dig_H1 = cmd[0];
    dig_H2 = (cmd[2] << 8) | cmd[1];
    dig_H3 = cmd[3];
    dig_H4 = (cmd[4] << 4) | (cmd[5] & 0x0f);
    dig_H5 = (cmd[6] << 4) | ((cmd[5]>>4) & 0x0f);
    dig_H6 = cmd[7];
 
    DPrintf("dig_H = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", dig_H1, dig_H2, 
            dig_H3, dig_H4, dig_H5, dig_H6);
*/
}
 
int32_t BMP280::Temperature() {
    int32_t temp_raw;
    char cmd[4];
 
    cmd[0] = 0xfa; // temp_msb
    Bus.write(BusAddress, cmd, 1);
    Bus.read(BusAddress, &cmd[1], 3);
 
    temp_raw = (cmd[1] << 12) | (cmd[2] << 4) | (cmd[3] >> 4);
    //DPrintf("\r\ntemp_raw:%d",temp_raw);
 
    int32_t temp1, temp2,temp;
 
    temp1 =((((temp_raw >> 3) - (dig_T1 << 1))) * dig_T2) >> 11;
    temp2 =(((((temp_raw >> 4) - dig_T1) * ((temp_raw >> 4) - dig_T1)) >> 12) * dig_T3) >> 14;
    //DPrintf("   temp1:%d   temp2:%d",temp1, temp2);
    t_fine = temp1+temp2;
    //DPrintf("   t_fine:%d",t_fine);
    temp = (t_fine * 5 + 128) >> 8;
    //DPrintf("   tempf:%f", float(temp) / 100.0);
    return temp;
}
 
uint32_t BMP280::Pressure() {
    char cmd[4];
 
    cmd[0] = 0xf7; // press_msb
    Bus.write(BusAddress, cmd, 1);
    Bus.read(BusAddress, &cmd[1], 3);
 
    int32_t Response = (cmd[1] << 12) | (cmd[2] << 4) | (cmd[3] >> 4);
    
    int32_t var1, var2;
    uint32_t press;
 
    var1 = (t_fine >> 1) - 64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * dig_P6;
    var2 = var2 + ((var1 * dig_P5) << 1);
    var2 = (var2 >> 2) + (dig_P4 << 16);
    var1 = (((dig_P3 * (((var1 >> 2)*(var1 >> 2)) >> 13)) >> 3) + ((dig_P2 * var1) >> 1)) >> 18;
    var1 = ((32768 + var1) * dig_P1) >> 15;
    if (var1 == 0) {
        return 0;
    }
    press = (((1048576 - Response) - (var2 >> 12))) * 3125;
    if(press < 0x80000000) {
        press = (press << 1) / var1;
    } else {
        press = (press / var1) * 2;
    }
    var1 = ((int32_t)dig_P9 * ((int32_t)(((press >> 3) * (press >> 3)) >> 13))) >> 12;
    var2 = (((int32_t)(press >> 2)) * (int32_t)dig_P8) >> 13;
    return (press + ((var1 + var2 + dig_P7) >> 4));
}