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
    StateCalibrateEnterTicks = -1,
    StateRunningEnter = 1,
  };
  
  // The tick and negative calibrating positive running states.
  volatile int Ticks;
  int TicksMonitor,       //< The max ticks between the Device monitors.
    TicksSecond,          //< The number of Ticks per Second.
    TicksInhaleMin,       //< The min inhale ticks.
    TicksInhaleMax,       //< The max breath period of 20 seconds.
    TicksExhaleMin,       //< The min ticks in an exhale.
    TicksExhaleMax,       //< The max ticks in an exhale.
    TicksCalibration,     //< The number of ticks in the calibration state.
    ChannelsCount;        //< The number of GHVentilatorChannels.
  GHVentilatorChannel* Channels[ChannelCountMax];
  BMP280 Atmosphere;      //< Pressure sensor for the air tank.
  float Temperature,      //< The Temperature in the tank.
    TemperatureReference, //< The Temperature in the tank.
    Pressure,             //< The Pressure in the tank.
    PressureReference,    //< The Pressure when the device is tared.
    PressureMin,          //< The min Pressure.
    PressureMax,          //< The max Pressure.
    HysteresisChamber,    //< The pressure chamber hystersis +/- percent.
    HysteresisPatient;    //< The patient Hystersis percent muliplier.
  DigitalOut Blower,      //< A blower powered by a Solid State Relay.
             Status;      //< Status pin for outputing the Device status.
  Ticker UpdateTicker;    //< The x times per second update ticker.
  
  /* Constructs a GHV with 1 channel. */
  GHVentilator (int TicksPerSecond, int TicksPEEP, int TicksCalibration,
                I2C& Bus, char BusAddress,
                float PressureHysteresis,
                float HysteresisPatient,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A);
      
  /* Constructs a GHV with 2 channels. */
  GHVentilator (int TicksPerSecond, int TicksPEEP, int TicksCalibration,
                I2C& Bus, char BusAddress,
                float HysteresisChamber,
                float PressureHysteresis,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A,
                GHVentilatorChannel* B);
      
  /* Constructs a GHV with 3 channels. */
  GHVentilator (int TicksPerSecond, int TicksPEEP, int TicksCalibration,
                I2C& Bus, char BusAddress,
                float PressureHysteresis,
                float HysteresisPatient,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A,
                GHVentilatorChannel* B,
                GHVentilatorChannel* C);
      
  /* Constructs a GHV with 4 channels. */
  GHVentilator (int TicksPerSecond, int TicksCalibration, int TicksPEEP,
                I2C& Bus, char BusAddress,
                float PressureHysteresis,
                float HysteresisPatient,
                PinName BlowerPin, PinName StatusPin,
                GHVentilatorChannel* A,
                GHVentilatorChannel* B,
                GHVentilatorChannel* C,
                GHVentilatorChannel* D);
  
  /* Sets the TicksPEEP given 1/64 second > NewTicksPEEP < 1 second. */
  void TicksPEEPSet (int NewTicksPEEP);
  
  /* Enters the Calibration State. */
  void StateCalibrateEnter ();
  
  /* Enters the Calibration State. */
  void StateCalibrateExit ();
  
  /* Polls the hardware for changes. */ 
  void Poll();
  
  /* Monitors this Device and it's channels. */
  void Monitor ();
  
  /* Turns off the Device and all of it's chanels. */
  void TurnOff ();
  
  /* Turns on the Device and all of it's chanels to the Inhale state. */
  void TurnOnAll ();

  /* Gets the GHVentilatorChannel with the given Index. \
  @return Nil if the Index is out of bounds. */
  GHVentilatorChannel* Channel(int Index);
  
  /* Reads the Atmospher.Pressure() and Atmospher.Temperature () */
  void Tare(); 
  
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
