/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /GHVentilaorChannel.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#include "GHVentilator.h"

#ifndef PressureChangeDeltaMinDefault
#define PressureChangeDeltaMinDefault  0.000000001
#endif
#ifndef PressureChangeDeltaDefault
#define PressureChangeDeltaDefault     0.000001
#endif
#define PressureChangeDeltaMaxDefault  0.001

static volatile int SecondCount = 0;

namespace SickBay {

GHVentilator::GHVentilator (int TicksPerSecond, I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A):
    State (StateCalibratingPressureSensor),
    Ticks (0),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    ChannelsCount (1),
    PressureMin(PressureMin),
    PressureMax(PressureMax),
    Pressure (Pressure),
    PressureChangeDelta (PressureChangeDeltaDefault),
    Channels(Channels),
    Pressure(I2CBus, SlaveAddress),
    Blower (BlowerPin),
    Status (StatusPin) {
  Channels[0] = A;
  Run ()
}

GHVentilator::GHVentilator (int TicksPerSecond, I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A,
                            GHVentilatorChannel B):
    State (StateCalibratingPressureSensor),
    Ticks (0),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    ChannelsCount (1),
    PressureMin(PressureMin),
    PressureMax(PressureMax),
    Pressure (Pressure),
    PressureChangeDelta (PressureChangeDeltaDefault),
    Channels(Channels),
    Pressure(I2CBus, SlaveAddress),
    Blower (BlowerPin),
    Status (StatusPin) {
  Channels[0] = A;
  Channels[1] = B;
  Run ()
}

GHVentilator::GHVentilator (int TicksPerSecond, I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A,
                            GHVentilatorChannel B,
                            GHVentilatorChannel C):
    State (StateCalibratingPressureSensor),
    Ticks (0),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    ChannelsCount (1),
    PressureMin(PressureMin),
    PressureMax(PressureMax),
    Pressure (Pressure),
    PressureChangeDelta (PressureChangeDeltaDefault),
    Channels(Channels),
    Pressure(I2CBus, SlaveAddress),
    Blower (BlowerPin),
    Status (StatusPin) {
  Channels[0] = A;
  Channels[1] = B;
  Channels[2] = C;
  Run ()
}

GHVentilator::GHVentilator (int TicksPerSecond, I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A,
                            GHVentilatorChannel B,
                            GHVentilatorChannel C,
                            GHVentilatorChannel D):
    State (StateCalibratingPressureSensor),
    Ticks (0),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    ChannelsCount (1),
    PressureMin(PressureMin),
    PressureMax(PressureMax),
    Pressure (Pressure),
    PressureChangeDelta (PressureChangeDeltaDefault),
    Channels(Channels),
    Pressure(I2CBus, SlaveAddress),
    Blower (BlowerPin),
    Status (StatusPin) {
  Channels[0] = A;
  Channels[1] = B;
  Channels[2] = C;
  Channels[3] = D;
  Run ()
}
  
void GHVentilator::Update() {
    // 1.) Turn off or on the blower.
    float Reading = Pressure.PressureGet();
    if (Reading < PressureMin) Blower = 1;
    else if (Reading > PressureMax) Blower = 0;
    Pressure = Reading;
    
    for (int i = 0; i < ChannelsCount; ++i) {
        Channels[i].Update();
}

SHVentilator::Run(){
  PrintIndent (100, "Starting GHVentilator...\r\n\r\n");

  UpdateTicker.attach (callback(this, &GHVentilator::Update), 
                       1.0f / float (TicksPerSecond));
    
  #if GHVDebug
  DebugTicker.attach (&DemoTickerISR, 1.0f/200.0f);
  #endif
    
  while (1);  //< This is an IRQ driven application.
}

void SHVentilator::Update () {
  auto Tick = Ticks;
  auto TicksMax = TicksMax;
  if (++Ticks >= TicksMax) Ticks = Tick = 0;
  else Ticks = Tick;
  
  GHVentilatorChannel* Channel = Channels,
                     * ChannelLast = &Channels[ChannelCount];
  while(Channel++ <= ChannelLast)
    Channel->Update();
}

}   //< namespace SickBay
