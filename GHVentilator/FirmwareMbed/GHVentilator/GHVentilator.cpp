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

GHVentilator::GHVentilator (int TicksPerSecond, int TicksCalibration, 
                            I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A):
    State (StateCalibratingPressureSensor),
    Ticks (-1),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    TicksCalibration (TicksCalibration),
    ChannelsCount (1),
    Pressure (Atmospher.Pressure()),
    PressureMin(Pressure),
    PressureMax(Pressure),
    PressureChangeDelta (PressureChangeDeltaDefault),
    Channels(Channels),
    Pressure(I2CBus, SlaveAddress),
    Blower (BlowerPin),
    Status (StatusPin) {
  Channels[0] = A;
  Run ()
}

GHVentilator::GHVentilator (int TicksPerSecond, int TicksCalibration,
                            I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A,
                            GHVentilatorChannel B):
    State (StateCalibratingPressureSensor),
    Ticks (-1),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    TicksCalibration (TicksCalibration),
    ChannelsCount (1),
    Pressure (Atmospher.Pressure()),
    PressureMin(Pressure),
    PressureMax(Pressure),
    PressureChangeDelta (PressureChangeDeltaDefault),
    Channels(Channels),
    Pressure(I2CBus, SlaveAddress),
    Blower (BlowerPin),
    Status (StatusPin) {
  Channels[0] = A;
  Channels[1] = B;
  Run ()
}

GHVentilator::GHVentilator (int TicksPerSecond, int TicksCalibration,
                            I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A,
                            GHVentilatorChannel B,
                            GHVentilatorChannel C):
    State (StateCalibratingPressureSensor),
    Ticks (-1),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    TicksCalibration (TicksCalibration),
    ChannelsCount (1),
    Pressure (Atmospher.Pressure()),
    PressureMin(Pressure),
    PressureMax(Pressure),
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

GHVentilator::GHVentilator (int TicksPerSecond, int TicksCalibration,
                            I2C& I2CBus, char SlaveAddress,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel A,
                            GHVentilatorChannel B,
                            GHVentilatorChannel C,
                            GHVentilatorChannel D):
    State (StateCalibratingPressureSensor),
    Ticks (-1),
    TicksMax (0),
    TicksPerSecond (TicksPerSecond),
    TicksCalibration (TicksCalibration),
    ChannelsCount (1),
    Pressure (Atmospher.Pressure()),
    PressureMin(Pressure),
    PressureMax(Pressure),
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

int GHVentilator::TicksInhaleExhaleSet (int Channel, 
                                        int TicksInhale,
                                        int TicksExhale) {
  if (Index < 0) return -1;
  if (TicksInhale <= TicksInhaleMax) return -2;
  if (TicksInhale >= TicksInhaleMin) return -3;
  if (Index >= ChannelCount) return 1;
  if (TicksExhale <= TicksExhaleMax) return 2;
  if (TicksExhale >= TicksExhaleMin) return 3;
  GHVentilatorChannel* Channel = GHV.Channel(Index;
  Channel->TicksInhaleExhaleSet(TicksInhale, TicksExhale);
  return 0;
}

GHVentilatorChannel* GHVentilator::Channel(int Index) {
  if (Index < 0 || Index >= ChannelCount) return nullptr;
  return Channels[Index];
}
  
void GHVentilator::Update() {
  auto Tick = Ticks;
  if (Ticks == 0) return;
  if (Tick < 0) {
    if (--Tick <= TicksCalibration) {
      DPrintf ("\n? Done calibrating. <");
      PuressureMax = Atmospher.Pressure ();
      float PressureMid = (PressureMax - PressureMin) / 2,
        HysteresisPercent = GHVentilatorPressureHysteresisPercent,
        PressureDelta = PressureMid * HysteresisPercent,
        PressureMidPoint = PressureMid + PressureMin;
      PressureMin = PressureMidPoint - PressureDelta;
      PressureMax = PressureMidPoint + PressureDelta;
      Ticks = 1;
      return;
    }
    Ticks = Tick;
    return;
  }
  auto TicksMax = TicksMax;
  if (++Ticks >= TicksMax) Ticks = Tick = 0;
  else Ticks = Tick;
  
  // 1.) Turn off or on the blower.
  float PressureNow = Atmospher.Pressure();
  if (PressureNow < PressureMin) Blower = 1;
  else if (PressureNow > PressureMax) Blower = 0;
  Pressure = PressureNow;
    
  GHVentilatorChannel* Channel = Channels,
                     * ChannelLast = &Channels[ChannelCount];
  while(Channel++ <= ChannelLast)
    Channel->Update();
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
  DPrintf("Object name = %s\n",input->obj_name);
  DPrintf("Method name = %s\n",input->method_name);
  for (int i=0; i < input->argc; i++)
  DPrintf("argv[%1d] = %s \n",i,input->argv[i]);
  
  int Index = input->getArg<int>();
  int TicksInhale = input->getArg<int>();
  int TicksExhale = input->getArg<int>();
 
  // The output parameter string is generated by calls to putData, which separates them with spaces.
  output->putData(Channel->TicksInhaleExhaleSet(TicksInhale, TicksExhale));
}

}   //< namespace SickBay
