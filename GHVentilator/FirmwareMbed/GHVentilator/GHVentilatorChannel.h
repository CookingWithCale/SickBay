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
    
  int    Ticks,                //< Ticks since the beginning of the inhale.
         TicksExhale,          //< The period of the breathing.
         TicksInhale,          //< The tick count in the inhale duty cycle.
         TicksFlowInhale;      //< Flow sensor tick count on the last exhale.
  volatile int TicksFlowLast,  //< The previous saved count.
         TicksFlow;            //< Flow sensor pulse count.
  BMP280 Atmosphere;           //< The air Atmosphere going to the patient.
  float  PressureReference,    //< The pressure in the mask at one atmosphere.
         TemperatureReference; //< The refernce temperature,
  AnalogIn   PulseOximeter;    //< The 7-pin pulse oximeter pin.
  InterruptIn FlowSensor;      //< The flow sensor pin.
  DigitalOut Valve,            //< The Solenoid valve.
             Status;           //< The Status LED and optional alarm.
  PwmOut     Servo;            //< The Servo for reducing the pressrue.
  int        ServoClosed,      //< The min servo duty cycle of no air flow.
             ServoOpen;        //< The max servo duty cycle of an open tube.

  /* Constructs a smart waterer. */
  GHVentilatorChannel (PinName PulseOximeterPin,
                       PinName FlowSensorPin,
                       PinName SolenoidPin,
                       PinName StatusPin,
                       PinName ServoPin,
                       I2C& AtmosphereAddress, char I2CAddress);
    
  /* Returns a pointer to this. */
  GHVentilatorChannel* This();
    
  /* Sets the number of ticks on the inhale and exhale. */
  void TicksInhaleExhaleSet (int NewTicksInhale, int NewTicksExhale);
      
  /* BreatheStarts to the begining of the watering cycle. */
  void BreatheStart (int Index);
    
  /* Increments theflow rate sensor pulse counter. */
  void PulseFlowSensor ();
    
  /* Prints the state of object to the debug stream. */
  void Print (int Index);
    
  /* Polls the PulseOximeter and updates the target flow. */
  void Update (int Index);
    
  /* Updates the float rate. */
  bool CheckIfDoneBreathing (int Index);
    
  /* Opens the solenoid valve. */
  void Inhale ();
    
  /* Closes the solenoid valve. */
  void Exhale ();
    
  /* Handles any errors. */
  void HandleError ();
    
  /* Samples the Atmospheric pressure and temperature. */
  void Tare (float HysteresisPatient);
    
  /* Updates the channel with the DeviceTick. */
  void Update();
};
}   //< namespace SickBay
#endif
