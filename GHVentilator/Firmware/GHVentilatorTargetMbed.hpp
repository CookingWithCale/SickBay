/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /TargetMbed.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef GHVentilatorTargetMbed
#define GHVentilatorTargetMbed

#define SickBayDebug 1
#define Platform PlatformMbed
#define GHVentilatorChannelCount 4

// Define LLLow and LLHigh before you #include "GHVentilator.hpp"
enum {
  LLHigh = 1, //< Logic-level High.
  LLLow  = 0, //< Logic-level Low.
};

#include "GHVentilator.hpp"
#include "BMP280.hpp"

namespace SickBay {
 

DigitalOut Blower(D2),
           Status(D3),
           Channel1Valve (D4);
DigitalIn ChannelFlowSensor (D5);
DigitalOut Channel2Valve (D6);
DigitalIn Channel2FlowSensor (D7);
DigitalOut Channel3Valve (D8);
DigitalIn Channel3FlowSensor (D9);
DigitalOut Channel4Valve (D10);
DigitalIn Channel4FlowSensor (D11);

void GHVentilator::BlowerTurnOff() {
  Blower = LLLow;
}

void GHVentilator::BlowerTurnOn() {
  Blower = LLHigh;
}

bool GHVentilator::IsOverPressure () { return Pressure > PressureMax; }

bool GHVentilator::IsUnderPressure () { return Pressure < PressureMax; }

void GHVentilator::Channel1ValveSet (int Value) {
  Channel1Valve = Value;
}

void GHVentilator::Channel2ValveSet (int Value) {
  Channel2Valve = Value;
}
void GHVentilator::Channel3ValveSet (int Value) {
  Channel3Valve = Value;
}
void GHVentilator::Channel4ValveSet (int Value) {
  Channel4Valve = Value;
}
#if GHVentilatorChannelCount >= 2
#endif
#if GHVentilatorChannelCount >= 3
#endif
#if GHVentilatorChannelCount >= 4
#endif

void GHVentilator::Run(){
  DPrintIndent (100, "Starting GHVentilator...\r\n\r\n");
  
  enum {
    TicksSecond = 250,
    TicksCalibrate = TicksSecond * 10, //< Calibrate for 10 seconds.
  };
  float ChamberPressureHysteresis = 1.25f, //< +/-25% goes up and down half-way.
        PatientPressureHysteresis = 1.01f; //< + 1% over 1 atmosphere.
  
  I2C Bus(A4, A5);
  int BusAddress = BMP280SlaveAddressDefault;
  
   // Pressure sensor for the air tank.
  BMP280 AtmosphereChamber(Bus, BusAddress);
  Pressure = AtmosphereChamber.Pressure ();
  Temperature = AtmosphereChamber.Temperature ();
  // Atmoshperic sensor to Patient 1.
  BMP280 Channel1Atmosphere(Bus, BusAddress + 1);
  Channels[0].Pressure = Channel1Atmosphere.Pressure ();
  Channels[0].Temperature = Channel1Atmosphere.Temperature ();
  #if GHVentilatorChannelCount >= 2
  // Atmoshperic sensor to Patient 2.
  BMP280 Channel2Atmosphere(Bus, BusAddress + 1);
  Channels[1].Pressure = Channel2Atmosphere.Pressure ();
  Channels[1].Temperature = Channel2Atmosphere.Temperature ();
  #endif
  #if GHVentilatorChannelCount >= 3
  // Atmoshperic sensor to Patient 3.
  BMP280 Channel3Atmosphere(Bus, BusAddress + 2);
  Channels[2].Pressure = Channel3Atmosphere.Pressure ();
  Channels[2].Temperature = Channel3Atmosphere.Temperature ();
  #endif
  #if GHVentilatorChannelCount >= 4
  // Atmoshperic sensor to Patient 4.
  BMP280 Channel4Atmosphere(Bus, BusAddress + 3);
  Channels[3].Pressure = Channel4Atmosphere.Pressure ();
  Channels[3].Temperature = Channel4Atmosphere.Temperature ();
  #endif
  
  Init (TicksSecond, TicksPEEP,
        ChamberPressureHysteresis, PatientPressureHysteresis);
  
  // Make sure you don't start the UpdateTicker until everything is setup to
  // enter the Configuration State.
  Ticker UpdateTicker;    //< The x times per second update ticker.
  UpdateTicker.attach (callback(this, &GHVentilator::Update), 
                       1.0f / float (TicksSecond));
  
  while (1) { // Poll the pressure and temperature.
    Temperature = AtmosphereChamber.Temperature ();
    Pressure  = AtmosphereChamber.Pressure();
    
    GHVentilatorChannel* Channel = &Channels[0];
    Channel->Temperature = Channel1Atmosphere.Temperature ();
    Channel->Pressure  = Channel1Atmosphere.Pressure();
    Channel = &Channels[1];
    #if GHVentilatorChannelCount >= 2
    Channel->Temperature = Channel2Atmosphere.Temperature ();
    Channel->Pressure  = Channel2Atmosphere.Pressure();
    #endif
    Channel = &Channels[2];
    #if GHVentilatorChannelCount >= 3
    Channel->Temperature = Channel3Atmosphere.Temperature ();
    Channel->Pressure  = Channel3Atmosphere.Pressure();
    #endif
    Channel = &Channels[3];
    #if GHVentilatorChannelCount >= 4
    Channel->Temperature = Channel4Atmosphere.Temperature ();
    Channel->Pressure  = Channel4Atmosphere.Pressure();
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