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
#include <stdint.h>
#ifndef GHVentilatorChannelCount
#error You must define the GHVentilatorChannelCount before including \
       "GHVentilator.hpp"
#endif
namespace SickBay {
    
class GHVentilator;

/* A Gravity Hookah Ventilator channel for one patient. */
class GHVentilatorChannel {
  public:
  
  enum {
    StateInhaling = 1,      //< The inhaling state is where Ticks < 0.
    StateOff = 0,           //< The off state is where Ticks = 0.
    StateExhaling = -1,     //< The exhaling state is where Ticks > 0.
  };
  
  GHVentilator* Parent;     //< The GHVentilator this is part of.
  int Ticks,                //< Ticks since the beginning of the inhale.
      TicksInhale,          //< The tick count in the inhale duty cycle.
      TicksExhale,          //< The period of the breathing.
      TicksFlow,            //< The number of flow sensor ticks.
      TicksFlowLast,        //< The previous inhale cycle TicksFlow count.
      PulseOximeter,        //< The 7-pin pulse oximeter value.
      Servo,                //< The Servo for reducing the pressrue.
      ServoClosed,          //< The min servo duty cycle of no air flow.
      ServoOpen;            //< The max servo duty cycle of an open tube.
  int32_t Temperature,      //< The Temperature of the patients breath.
      TemperatureReference; //< The refernce temperature upon Tare.
  uint32_t Pressure,        //< The pressure in the patient's mask.
      PressureReference,    //< About 1 atmosphere + the hysteresis delta.
      PressureHysteresis;   //< The hysteresis above the PressureReference. 
  
  /* Initializes the channel.
  @param PressureHysteresis 1.0 + the percent hysteresis up and down from the 
  center the 
  */
  void Init (GHVentilator* Parent, int TicksInhale, int TicksExhale, 
             float ChannelPressureHysteresis);
             
  /* Doesn't do anything and requires a call to . */
  GHVentilatorChannel ();
    
  /* Returns a pointer to this. */
  GHVentilatorChannel* This();
  
  void ChannelValveSet (GHVentilatorChannel* Channel, int Value);
  
  /* Turns this channel off. */
  void TurnOff ();
    
  /* Sets the number of ticks on the inhale and exhale. */
  void TicksInhaleExhaleSet (int NewTicksInhale, int NewTicksExhale);
    
  /* Increments theflow rate sensor pulse counter. */
  void TickFlow ();
    
  /* Prints the state of object to the debug stream. */
  void Print (int Index);
    
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
