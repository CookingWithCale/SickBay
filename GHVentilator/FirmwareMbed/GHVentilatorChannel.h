/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /GHVentilatorChannel.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#ifndef GHVentilatorChannelDecl
#define GHVentilatorChannelDecl
#include "GHVentilatorConfig.h"
#include "BMP280.h"

namespace SickBay {

/* A Gravity Hookah Ventilator channel for one patient. */
class GHVentilatorChannel {
  public:
  
  enum {
    StateInhaling = 1,         //< The value for the init Ticks inhale value.
    StateExhaling = -1,        //< The value for the init Ticks exhale value.
  };
    
  volatile int Ticks;          //< Ticks since the beginning of the inhale.
  int    TicksExhale,          //< The period of the breathing.
         TicksInhale,          //< The tick count in the inhale duty cycle.
         TicksPeep;            //< The max ticks between an exhale and inhale.
  volatile int TicksFlowLast,  //< The previous inhale TicksFlow count.
         TicksFlow;            //< Flow sensor pulse TicksFlow count.
  BMP280 Atmosphere;           //< The air Atmosphere going to the patient.
  float  Temperature,          //< The Temperature of the patients breath.
         TemperatureReference, //< The refernce temperature,
         Pressure,             //< The pressure in the patient's mask.
         PressureReference;    //< The pressure in the mask at one atmosphere.
  AnalogIn   PulseOximeter;    //< The 7-pin pulse oximeter pin.
  InterruptIn FlowSensor;      //< The flow sensor pin.
  DigitalOut Valve;            //< The Status LED and optional alarm.
  PwmOut     Servo;            //< The Servo for reducing the pressrue.
  int        ServoClosed,      //< The min servo duty cycle of no air flow.
             ServoOpen,        //< The max servo duty cycle of an open tube.
             Status;           //< The channel Status.
             
  /* Constructs a smart waterer. */
  GHVentilatorChannel (PinName PulseOximeterPin,
                       PinName FlowSensorPin,
                       PinName SolenoidPin,
                       PinName ServoPin,
                       I2C& Bus, char BusAddress);
    
  /* Returns a pointer to this. */
  GHVentilatorChannel* This();
  
  /* Turns off this channel. */
  void TurnOff ();
  
  /* Turns on the this chanel. */
  void TurnOn ();
  
  /* Polls the hardware for changes. */
  void Poll();
    
  /* Sets the number of ticks on the inhale and exhale. */
  void TicksInhaleExhaleSet (int NewTicksInhale, int NewTicksExhale);
      
  /* BreatheStarts to the begining of the watering cycle. */
  void BreatheStart (int Index);
    
  /* Increments theflow rate sensor pulse counter. */
  void TickFlow ();
    
  /* Prints the state of object to the debug stream. */
  void Print (int Index);
    
  /* Updates the float rate. */
  bool CheckIfDoneBreathing (int Index);
    
  /* Opens the solenoid valve. */
  void Inhale ();
    
  /* Closes the solenoid valve. */
  void Exhale ();
    
  /* Samples the Atmospheric pressure and temperature. */
  void Tare (float PressureHysteresis);
  
  /* Monitor the channel for if errors. */
  int Monitor ();
    
  /* Updates the channel with the DeviceTick. */
  void Update();
};
}   //< namespace SickBay
#endif
