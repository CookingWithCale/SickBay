/** Gravity Hookah Ventilator @version 0.x
@link  https://github.com/KabukiStarship/SickBay.git
@file  /GHVentilator.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef GHVentilatorDecl
#define GHVentilatorDecl
#include <mbedBug.h>
using namespace mbedBug;
#include "GHVentilatorChannel.h"
namespace SickBay {
    
#define GHVentilatorPressureHysteresisPercent 0.25f //< +/- 25% histesis.

/* A Gravity Hookah Ventilator. */
template<int ChannelCount>
class GHVentilator {
  public:
  
  enum {
    ChannelCountMax = 4,
    StateCalibratingPressureSensor = 0,
    StateRunning = 1,
  };
  
  // The tick and negative calibrating positive running states.
  int Ticks,
    TicksMax,        //< The max tick count before it gets reset.
    TicksSecond,     //< The number of Ticks per Second.
    TicksInhaleMin,  //< The min inhale ticks.
    TicksInhaleMax,  //< The max breath period of 20 seconds.
    TicksExhaleMin,  //< The min ticks in an exhale.
    TicksExhaleMax,  //< The max ticks in an exhale.
    TicksCalibration;//< The number of ticks in the calibration state.
  float PressureMin, //< The min Pressure.
    PressureMax,     //< The max Pressure.
    Pressure,        //< The Pressure in the tank.
    ServoMin,        //< The min servo value.
    ServoMax;        //< The max servo value.
  /* The amount the Pressure needs to change to count as having changed. */
  float PressureChangeDelta;
  //< The GHV channels.
  GHVentilatorChannel Channels[ChannelCountMax];
  BMP280 Atmosphere;   //< Pressure sensor for the air tank.
  DigitalOut Blower;   //< A blower powered by a Solid State Relay.
  
  GHVentilator (int TicksPerSecond, int TicksCalibration,
                I2C& I2CBus, char SlaveAddress,
      PinName BlowerPin, PinName StatusPin,
      GHVentilatorChannel A);
      
  GHVentilator (int TicksPerSecond, int TicksCalibration,
      I2C& I2CBus, char SlaveAddress,
      PinName BlowerPin, PinName StatusPin,
      GHVentilatorChannel A,
      GHVentilatorChannel B);
      
  GHVentilator (int TicksPerSecond, int TicksCalibration,
      I2C& I2CBus, char SlaveAddress,
      PinName BlowerPin, PinName StatusPin,
      GHVentilatorChannel A,
      GHVentilatorChannel B,
      GHVentilatorChannel C);
      
  GHVentilator (int TicksPerSecond, I2C& I2CBus, char SlaveAddress,
      PinName BlowerPin, PinName StatusPin,
      GHVentilatorChannel A,
      GHVentilatorChannel B,
      GHVentilatorChannel C,
      GHVentilatorChannel D);

  /* Gets the GHVentilatorChannel with the given Index. \
  @return Nil if the Index is out of bounds. */
  GHVentilatorChannel* Channel(int Index);
      
  void ChannelSet (int ChannelIndex, float DutyCycle = 0.0f, 
       float Period = 0.0f);
  /* Reads the Atmospher.Pressure() and Atmospher.Temperature () */
  void TarePressure(); 
  
  int TicksInhaleExhaleSet (int TicksInhale, int TicksExhale);
  
  /* Starts the system. */   
  int Run ();
  
  /* Updates the main device and it's channels. */
  void Update ();
};

void HanleTicksSecondSet(Arguments* input, Reply* output);
void HanleInhaleTicksSet(Arguments* input, Reply* output);

RPCFunction TicksSecondSet(&DoGetData, "TicksSecondSet"),
            InhaleTicksSet(&DoGetData, "InhaleTicksSet"),
            ExhaleTicksSet(&DoGetData, "ExhaleTicksSet");
 
void RemoteTicksSecondSetHandle(Arguments* input, Reply* output);
 
void HandleTicksInhaleExhaleSet(Arguments* input, Reply* output);

}   //< namespace SickBay
#endif
