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
#include "GHVentilatorChannel.h"
namespace SickBay {

/* A Gravity Hookah Ventilator. */
class GHVentilator {
  public:
  
  enum {
    ChannelCountMax = 4,
    StateCalibratingPressureSensor = 0,
    StateRunning = 1,
  };
  
  // The tick and negative calibrating positive running states.
  int Ticks,
    TicksMax,            //< The max tick count before it gets reset.
    TicksSecond,         //< The number of Ticks per Second.
    TicksInhaleMin,      //< The min inhale ticks.
    TicksInhaleMax,      //< The max breath period of 20 seconds.
    TicksExhaleMin,      //< The min ticks in an exhale.
    TicksExhaleMax,      //< The max ticks in an exhale.
    TicksCalibration,    //< The number of ticks in the calibration state.
    ChannelsCount;       //< The number of GHVentilatorChannels.
  GHVentilatorChannel* Channels[ChannelCountMax];
  BMP280 Atmosphere;     //< Pressure sensor for the air tank.
  float Pressure,        //< The Pressure in the tank.
    PressureMin,         //< The min Pressure.
    PressureMax,         //< The max Pressure.
    PressureHysteresis;  //< The percent hystersis for the Pressure chamber.
  DigitalOut Blower;     //< A blower powered by a Solid State Relay.
  DigitalOut Status;     //< Status pin for outputing the Device status.
  Ticker UpdateTicker;   //< The x times per second update ticker.
  
  /* Constructs a GHV with 1 channel. */
  GHVentilator (int TicksPerSecond, int TicksCalibration,
                I2C& AtmosphereBus, char AtmosphereAddress,
                float PressureHysteresis,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A);
      
  /* Constructs a GHV with 2 channels. */
  GHVentilator (int TicksPerSecond, int TicksCalibration,
                I2C& AtmosphereBus, char AtmosphereAddress,
                float PressureHysteresis,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A,
                GHVentilatorChannel* B);
      
  /* Constructs a GHV with 3 channels. */
  GHVentilator (int TicksPerSecond, int TicksCalibration,
                I2C& AtmosphereBus, char AtmosphereAddress,
                float PressureHysteresis,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A,
                GHVentilatorChannel* B,
                GHVentilatorChannel* C);
      
  /* Constructs a GHV with 4 channels. */
  GHVentilator (int TicksPerSecond, int TicksCalibration,
                I2C& AtmosphereBus, char AtmosphereAddress,
                float PressureHysteresis,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A,
                GHVentilatorChannel* B,
                GHVentilatorChannel* C,
                GHVentilatorChannel* D);

  /* Gets the GHVentilatorChannel with the given Index. \
  @return Nil if the Index is out of bounds. */
  GHVentilatorChannel* Channel(int Index);
  
  /* Reads the Atmospher.Pressure() and Atmospher.Temperature () */
  void TarePressure(); 
  
  /* Sets the inhale and exhale ticks for the give channel Index. */
  int TicksInhaleExhaleSet (int Index, int TicksInhale, int TicksExhale);
  
  /* Starts the system. */   
  void Run ();
  
  /* Updates the main device and it's channels. */
  void Update ();
};

}   //< namespace SickBay
#endif
#undef GHVentilatorChannelsCount
