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
#include <mbedBug.h>
using namespace mbedBug;
#include "GHVentilatorConfig.h"
#include "BMP280.h"

#ifndef GHVentilatorChannelsCount
#define GHVentilatorChannelsCount 1
#endif

#define GHVentilatorPressureHysteresis 0.000001f
#define GHVentilatorPressureTemperature 0.000001f

volatile int CurrentChannel = -1;
volatile bool TooMuchAir = false;

namespace SickBay {

/* A Gravity Hookah Ventilator channel for one patient. */
class GHVentilatorChannel {
    public:
    
    int Ticks,               //< Ticks since the beginning of the inhale.
        TicksInhale,         //< The ticks in the inhale duty half-period.
        TicksExhale;         //< The period of the breathing.
    volatile int TicksFlowLast, //< The previous saved count.
        TicksFlow;           //< Flow sensor pulse count.
    int TicksFlowInhale,     //< Number of flow sensor ticks on the last exhale.
        ServoClosed,         //< The min servo duty cycle of no air flow.
        ServoOpen;           //< The max servo duty cycle of an open tube.
    float ReferencePressure, //< The pressure in the mask at one atmosphere.
          ReferenceTemperature; //< The refernce temperature,
    BMP280 Atmosphere;       //< The air Atmosphere going to the patient.
    InterruptIn Sensor;      //< The flow sensor pin.
    DigitalOut Valve,        //< The Solenoid valve.
      Status;                //< The Status LED and optional alarm.
    PwmOut Servo;            //< The Servo for reducing the pressrue.
    AnalogIn PulseOximeter;  //< The PulseOximeterentiometer pin.

    /* Constructs a smart waterer. */
    GHVentilatorChannel (PinName SensorPin,
                         PinName PulseOximeterPin,
                         PinName SolenoidPin,
                         PinName StatusPin,
                         PinName ServoPin,
                         I2C& I2CBus, char I2CAddress);
    
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
    void Tare ();
    
    /* Updates the channel with the DeviceTick. */
    void Update();
    
    private:
    
    /* Calculates the pulse target value from the PulseOximeter value. */
    inline int CalcPulseTarget ();
};
}   //< namespace SickBay
#endif //< GHVentilatorChannelDecl
