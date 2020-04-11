/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /SBVentilator/Firmware/TargetMbed.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SBVentilatorMbed
#define SBVentilatorMbed
#include <_KabukiTek.hpp>
#include <BMP280.hpp>
#include <BExprI2CMbed.hpp>
using namespace _;

#include "SBVentilator.hpp"

#define SickBayDebug 1
#define Platform PlatformMbed
#define SBVentilatorChannelCount 4

namespace SickBay {
 

DigitalOut Blower(D2),
           Status(D3),
           Channel1Valve (D4);
DigitalIn  ChannelFlowSensor (D5);
DigitalOut Channel2Valve (D6);
DigitalIn  Channel2FlowSensor (D7);
DigitalOut Channel3Valve (D8);
DigitalIn  Channel3FlowSensor (D9);
DigitalOut Channel4Valve (D10);
DigitalIn  Channel4FlowSensor (D11);

void SBVentilator::BlowerTurnOff() {
  Blower = LLLow;
}

void SBVentilator::BlowerTurnOn() {
  Blower = LLHigh;
}

bool SBVentilator::IsOverPressure () { return Pressure > PressureMax; }

bool SBVentilator::IsUnderPressure () { return Pressure < PressureMax; }

void SBVentilator::Channel1ValveSet (int Value) {
  Channel1Valve = Value;
}

void SBVentilator::Channel2ValveSet (int Value) {
  Channel2Valve = Value;
}
void SBVentilator::Channel3ValveSet (int Value) {
  Channel3Valve = Value;
}
void SBVentilator::Channel4ValveSet (int Value) {
  Channel4Valve = Value;
}
#if SBVentilatorChannelCount >= 2
#endif
#if SBVentilatorChannelCount >= 3
#endif
#if SBVentilatorChannelCount >= 4
#endif

void SBVentilator::Run(){
  DPrintIndent (100, "Starting SBVentilator...\r\n\r\n");
  
  enum {
    TicksSecond = 250,
    TicksCalibrate = TicksSecond * 10, //< Calibrate for 10 seconds.
  };
  DPrintf("\nInitalizing system with %d ticks per second.", TicksSecond);
  float ChamberPressureHysteresis = 1.25f, //< +/-25% goes up and down half-way.
        PatientPressureHysteresis = 1.01f; //< + 1% over 1 atmosphere.
  
  I2C Bus(A4, A5);
  int BMP280Address = BMP280::AddressDefault;
  
  // Pressure sensor for the air tank.
  BMP280 Atmosphere0;
  Atmosphere0.Init(EvaluateI2C, &Bus, BMP280Address);
  Pressure = Atmosphere0.Pressure ();
  Temperature = Atmosphere0.Temperature ();
  // Atmoshperic sensor to Patient 1.
  BMP280 Atmosphere1;
  Atmosphere1.Init(EvaluateI2C, &Bus, BMP280Address + 1);
  Channels[0].Pressure = Atmosphere1.Pressure ();
  Channels[0].Temperature = Atmosphere1.Temperature ();
  #if SBVentilatorChannelCount >= 2
  // Atmoshperic sensor to Patient 2.
  BMP280 Atmosphere2;
  Atmosphere2.Init (EvaluateI2C, &Bus, BMP280Address + 2);
  Channels[1].Pressure = Atmosphere2.Pressure ();
  Channels[1].Temperature = Atmosphere2.Temperature ();
  #endif
  #if SBVentilatorChannelCount >= 3
  // Atmoshperic sensor to Patient 3.
  BMP280 Atmosphere3;
  Atmosphere3.Init(EvaluateI2C, &Bus, BMP280Address + 3);
  Channels[2].Pressure = Atmosphere3.Pressure ();
  Channels[2].Temperature = Atmosphere3.Temperature ();
  #endif
  #if SBVentilatorChannelCount >= 4
  // Atmoshperic sensor to Patient 4.
  BMP280 Atmosphere4;
  Atmosphere4.Init (EvaluateI2C, &Bus, BMP280Address + 4);
  Channels[3].Pressure = Atmosphere4.Pressure ();
  Channels[3].Temperature = Atmosphere4.Temperature ();
  #endif
  
  Init (TicksSecond, TicksPEEP,
        ChamberPressureHysteresis, PatientPressureHysteresis);
  
  // Make sure you don't start the UpdateTicker until everything is setup to
  // enter the Configuration State.
  Ticker UpdateTicker;    //< The x times per second update ticker.
  UpdateTicker.attach (callback(this, &SBVentilator::Update), 
                       1.0f / float (TicksSecond));
  
  while (1) { // Poll the sensors.
    Temperature = Atmosphere0.Temperature ();
    Pressure  = Atmosphere0.Pressure();
    
    SBVentilatorChannel* Channel = &Channels[0];
    Channel->Temperature = Atmosphere1.Temperature ();
    Channel->Pressure  = Atmosphere1.Pressure();
    Channel = &Channels[1];
    #if SBVentilatorChannelCount >= 2
    Channel->Temperature = Atmosphere2.Temperature ();
    Channel->Pressure  = Atmosphere2.Pressure();
    #endif
    Channel = &Channels[2];
    #if SBVentilatorChannelCount >= 3
    Channel->Temperature = Atmosphere3.Temperature ();
    Channel->Pressure  = Atmosphere3.Pressure();
    #endif
    Channel = &Channels[3];
    #if SBVentilatorChannelCount >= 4
    Channel->Temperature = Atmosphere4.Temperature ();
    Channel->Pressure  = Atmosphere4.Pressure();
    #endif
  }
}
/*
void RemoteTicksSecondSetHandle(Arguments* input, Reply* output) {
  // Arguments are already parsed into argv array of char*
  DDPrintf("Object name = %s\n",input->obj_name);
  DPrintf("Method name = %s\n",input->method_name);
  for (int i=0; i < input->argc; i++)
  DPrintf("argv[%1d] = %s \n",i,input->argv[i]);
  
  // Alternatively the arguments can be recovered as the types expected
  // by repeated calls to getArg()
  int arg0 = input->getArg<int>();  // Expecting argv[0] to be int
  DPrintf("Expecting argv[0] to be int = %d\n",arg0);
  int arg1 = input->getArg<int>();  // Expecting argv[1] to be int
  DPrintf("Expecting argv[1] to be int = %d\n",arg1);
 
  // The output parameter string is generated by calls to putData, which separates them with spaces.
  output->putData(arg0);
  output->putData(arg1);
}
 
void HandleTicksInhaleExhaleSet(Arguments* input, Reply* output) {
  DPrintf("\n? Object name=\"%s\" method_name=\"%s\" <",input->obj_name,input->method_name);
  for (int i=0; i < input->argc; i++)
    DPrintf("argv[%1d] = %s \n",i,input->argv[i]);
  
  int Index = input->getArg<int>();
  int TicksInhale = input->getArg<int>();
  int TicksExhale = input->getArg<int>();
 
  // The output parameter string is generated by calls to putData, which separates them with spaces.
  output->putData(Channel->TicksInhaleExhaleSet(TicksInhale, TicksExhale));
}


RPCFunction TicksSecondSet(&HandleTicksSecondSet, "TicksSecondSet"),
            InhaleExhaleTicksSet(&HandleTicksInhaleExhaleSet, "InhaleTicksSet");
          */  
} //< namespace SickBay
#endif