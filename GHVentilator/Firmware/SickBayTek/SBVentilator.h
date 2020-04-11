/** SickBay Tek @version 0.x
@link  https://github.com/KabukiStarship/SickBay.git
@file  /SBVentilator.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SBVentilatorDecl
#define SBVentilatorDecl
#include "SBVentilatorChannel.h"
namespace SickBay {

/* A SickBay Ventilator. */
class SBVentilator {
  public:
  
  enum {
    StateOff = 0,         //< Both Machine calibrating and off states.
    StateCalibrate = 0,   //< The Calibrate state where the Tick is 0.
    StateRising = 1,      //< The Running state first Tick.
    StateSinking = -1,    //< The Running state first Tick.
    StatusCodeCount = 1,  //< The number of status codes.
    ChannelCount = SBVentilatorChannelCount,  //< Number of ventilator channels.
  };
  
  volatile int Status;    //< The status of the Device.
  // The tick and negative calibrating positive running states.
  volatile int Ticks;
  int TicksMonitor,       //< The max ticks between the Device monitor updates.
    TicksSecond,          //< The number of Ticks per Second.
    TicksInhaleMin,       //< The min inhale ticks.
    TicksInhaleMax,       //< The max breath period of 20 seconds.
    TicksExhaleMin,       //< The min ticks in an exhale.
    TicksExhaleMax,       //< The max ticks in an exhale.
    TicksPEEP,            //< The max number of PEEP Ticks before inhaling.
    TicksCalibration;     //< The number of ticks in the calibration state.
  int32_t Temperature,    //< The Temperature in the tank.
    TemperatureReference; //< The Temperature in the tank.
  uint32_t Pressure,      //< The Pressure in the tank.
    PressureReference,    //< The Pressure when the device is tared.
    PressureMin,          //< The min Pressure.
    PressureMax,          //< The max Pressure.
    HysteresisChamber,    //< The pressure chamber hystersis +/- delta.
    HysteresisPatient;    //< The patient Hystersis + delta.
  SBVentilatorChannel Channels[ChannelCount];
  
  /* Sets some of the varaibles to default requiring a call to Init. */
  SBVentilator ();
  
  /* Initializes the ventilator with the given values. */
  void Init (int TicksPerSecond, int TicksCalibration,
             float PressureHysteresis, float HysteresisPatient);
  
  /* Enters the Calibration State. */
  void StateCalibrateEnter ();
  
  /* Enters the Calibration State. */
  void StateCalibrateExit ();
  
  /* Returns true if the Chamber is over-pressure. */
  bool IsOverPressure ();
  
  /* Returns true if the Chamber is under-pressure. */
  bool IsUnderPressure ();
  
  /* Turns on the blower fan. */
  void BlowerTurnOn ();
  
  /* Turns off the blower fan. */
  void BlowerTurnOff ();
  
  /* Turns the Blower off and sets the Ticks to StateSinking. */
  void StateSinkingEnter ();
  
  /* Turns the Blower On and sets the Ticks to StateRising. */
  void StateRisingEnter ();
  
  /* Sets the TicksPEEP given 1/64 second > NewTicksPEEP < 1 second. */
  void TicksPEEPSet (int NewTicksPEEP);
  
  /* Enters the Off State. */
  void StateCalibrateOff ();
  
  /* Monitors this Device and it's channels. */
  void Monitor ();
  
  /* Turns off the Device and all of it's chanels. */
  void TurnOff ();
  
  /* Turns on the Device and all of it's chanels to the Inhale state. */
  void TurnOnAll ();
  
  /* Reads the Atmospher.Pressure() and Atmospher.Temperature () */
  void Tare(); 
  
  /* Sets the inhale and exhale ticks for the give channel Index. */
  int TicksInhaleExhaleSet (int Index, int TicksInhale, int TicksExhale);
  
  /* Calls on of the Channel1ValveSet through Channel4ValveSet functions. */
  void ChannelValveSet (SBVentilatorChannel* Channel, int Value);
  
  /* Sets the Channel 1 solenoid valve to the given Value. */
  void Channel1ValveSet (int Value);
  //#if SBVentilatorChannelCount >= 2
  /* Sets the Channel 2 solenoid valve to the given Value. */
  void Channel2ValveSet (int Value);
  //#endif
  //#if SBVentilatorChannelCount >= 3
  /* Sets the Channel 3 solenoid valve to the given Value. */
  void Channel3ValveSet (int Value);
  //#endif
  //#if SBVentilatorChannelCount >= 4
  /* Sets the Channel 4 solenoid valve to the given Value. */
  void Channel4ValveSet (int Value);
  //#endif
  
  /* Updates the main device and it's channels. */
  void Update ();
  
  /* Main program loop. */
  void Run ();
  
};

}   //< namespace SickBay
#endif
#undef SBVentilatorChannelCount
#undef SBVentilatorStateRising
#undef SBVentilatorStateSinking
