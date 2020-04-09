/** Gravity Hookah Ventilator @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /GHVentilaorChannel.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, 
v. 2.0. If a copy of the MPL was not distributed with this file, you can obtain 
one at <https://mozilla.org/MPL/2.0/>. */

#include "GHVentilator.h"

namespace SickBay {

GHVentilator::GHVentilator (int TicksSecond, int TicksCalibration, 
                            I2C& Bus, char BusAddress,
                            float HysteresisChamber,
                            float HysteresisPatient,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel* A):
    Ticks              (StateCalibrateEnterTicks),
    TicksMonitor       (TicksSecond),
    TicksSecond        (TicksSecond),
    TicksInhaleMin     (TicksSecond),
    TicksInhaleMax     (TicksSecond * 10),
    TicksExhaleMin     (TicksSecond),
    TicksExhaleMax     (TicksSecond * 10),
    TicksCalibration   (TicksCalibration),
    ChannelsCount      (1),
    Atmosphere         (Bus, BusAddress),
    Temperature        (Atmosphere.Temperature()),
    Pressure           (Atmosphere.Pressure()),
    PressureMin        (Pressure),
    PressureMax        (Pressure),
    HysteresisChamber  (HysteresisChamber),
    HysteresisPatient  (HysteresisPatient + 1.0f),
    Blower             (BlowerPin),
    Status             (StatusPin) {
  Channels[0] = A;
  Run ();
}

GHVentilator::GHVentilator (int TicksSecond, int TicksCalibration,
                            I2C& Bus, char BusAddress,
                            float HysteresisChamber,
                            float HysteresisPatient,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel* A,
                            GHVentilatorChannel* B):
    Ticks              (StateCalibrateEnterTicks),
    TicksMonitor       (TicksSecond),
    TicksSecond        (TicksSecond),
    TicksInhaleMin     (TicksSecond),
    TicksInhaleMax     (TicksSecond * 10),
    TicksExhaleMin     (TicksSecond),
    TicksExhaleMax     (TicksSecond * 10),
    TicksCalibration   (TicksCalibration),
    ChannelsCount      (2),
    Atmosphere         (Bus, BusAddress),
    Temperature        (Atmosphere.Temperature()),
    Pressure           (Atmosphere.Pressure()),
    PressureMin        (Pressure),
    PressureMax        (Pressure),
    HysteresisChamber (HysteresisChamber + 1.0f),
    Blower             (BlowerPin),
    Status             (StatusPin) {
  Channels[0] = A;
  Channels[1] = B;
  Run ();
}

GHVentilator::GHVentilator (int TicksSecond, int TicksCalibration,
                            I2C& Bus, char BusAddress,
                            float HysteresisChamber,
                            float HysteresisPatient,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel* A,
                            GHVentilatorChannel* B,
                            GHVentilatorChannel* C):
    Ticks              (StateCalibrateEnterTicks),
    TicksMonitor       (TicksSecond),
    TicksSecond        (TicksSecond),
    TicksInhaleMin     (TicksSecond),
    TicksInhaleMax     (TicksSecond * 10),
    TicksExhaleMin     (TicksSecond),
    TicksExhaleMax     (TicksSecond * 10),
    TicksCalibration   (TicksCalibration),
    ChannelsCount      (3),
    Atmosphere         (Bus, BusAddress),
    Temperature        (Atmosphere.Temperature()),
    Pressure           (Atmosphere.Pressure()),
    PressureMin        (Pressure),
    PressureMax        (Pressure),
    HysteresisChamber (HysteresisChamber + 1.0f),
    Blower             (BlowerPin),
    Status             (StatusPin) {
  Channels[0] = A;
  Channels[1] = B;
  Channels[2] = C;
  Run ();
}

GHVentilator::GHVentilator (int TicksSecond, int TicksCalibration,
                            I2C& Bus, char BusAddress,
                            float HysteresisChamber,
                            float HysteresisPatient,
                            PinName BlowerPin, PinName StatusPin,
                            GHVentilatorChannel* A,
                            GHVentilatorChannel* B,
                            GHVentilatorChannel* C,
                            GHVentilatorChannel* D):
    Ticks              (StateCalibrateEnterTicks),
    TicksMonitor       (TicksSecond),
    TicksSecond        (TicksSecond),
    TicksInhaleMin     (TicksSecond),
    TicksInhaleMax     (TicksSecond * 10),
    TicksExhaleMin     (TicksSecond),
    TicksExhaleMax     (TicksSecond * 10),
    TicksCalibration   (TicksCalibration),
    ChannelsCount      (4),
    Atmosphere         (Bus, BusAddress),
    Temperature        (Atmosphere.Temperature()),
    Pressure           (Atmosphere.Pressure()),
    PressureMin        (Pressure),
    PressureMax        (Pressure),
    HysteresisChamber  (HysteresisChamber + 1.0f),
    HysteresisPatient  (HysteresisPatient + 1.0f),
    Blower             (BlowerPin),
    Status             (StatusPin) {
  Channels[0] = A;
  Channels[1] = B;
  Channels[2] = C;
  Channels[3] = D;
  Run ();
}

void GHVentilator::StateCalibrateEnter () {
  TurnOff ();
  Poll ();
  Blower = 1;
  Ticks = StateCalibrateEnterTicks; //< Make sure to set this last.
}
  
void GHVentilator::StateCalibrateExit () {
  float HysteresisPatient = this->HysteresisPatient;
  for (int Index = ChannelsCount - 1; Index >= 0; --Index)
    Channels[Index]->Tare (HysteresisPatient);
  PressureMax = Atmosphere.Pressure ();
  float HysteresisChamber = this->HysteresisChamber,
        PressureMid = (PressureMax - PressureMin) / 2,
        HysteresisPercent = HysteresisChamber,
        PressureDelta = PressureMid * HysteresisPercent,
        PressureMidPoint = PressureMid + PressureMin;
  PressureMin = PressureMidPoint - PressureDelta;
  PressureMax = PressureMidPoint + PressureDelta;
  TurnOnAll ();
  DPrintf ("\n? Done calibrating. <");
}

void GHVentilator::Poll() {
  Pressure = Atmosphere.Pressure();
  Temperature = Atmosphere.Temperature ();
  for (int Index = ChannelsCount; Index >= 0; --Index)
    Channels[Index]->Poll ();
}

void GHVentilator::Monitor () { 
  for (int Index = ChannelsCount - 1; Index >= 0; --Index) {
    DPrintf ("\n> Channel %d"); 
    GHVentilatorChannel* Channel = Channels[Index];
    int Ticks = Channel->Monitor();
    if (Ticks == GHVentilatorChannel::StateInhaling) {
      DPrintf ("\n  ? Inhaling state. <");
    }
    else if (Ticks == GHVentilatorChannel::StateExhaling) {
      DPrintf ("\n  ? Exhaling state. <");
    }
    else if (Ticks >= Channel->TicksExhale) {
      DPrintf ("\n  ? PEEP state. <");
    }
  }
}

void GHVentilator::TurnOff () {
  for (int Index = ChannelsCount; Index >= 0; --Index)
    Channels[Index]->TurnOff();
}

void GHVentilator::TurnOnAll () {
  for (int Index = ChannelsCount; Index >= 0; --Index)
    Channels[Index]->Inhale();
}

GHVentilatorChannel* GHVentilator::Channel(int Index) {
  if (Index < 0 || Index >= ChannelsCount) return nullptr;
  return Channels[Index];
}

void GHVentilator::Tare () {
  TemperatureReference = Atmosphere.Temperature ();
  PressureReference = Atmosphere.Pressure();
  float HysteresisPatient = this->HysteresisPatient;
  for (int Index = ChannelsCount; Index >= 0; --Index)
    Channels[Index]->Tare(HysteresisPatient);
}

int GHVentilator::TicksInhaleExhaleSet (int Index, 
                                        int TicksInhale,
                                        int TicksExhale) {
  if (Index < 0) return StateCalibrateEnterTicks;
  if (TicksInhale <= TicksInhaleMax) return -2;
  if (TicksInhale >= TicksInhaleMin) return -3;
  if (Index >= ChannelsCount) return 1;
  if (TicksExhale <= TicksExhaleMax) return 2;
  if (TicksExhale >= TicksExhaleMin) return 3;
  //GHVentilatorChannel* Channel = GHV.Channel(Index);
  //Channel->TicksInhaleExhaleSet(TicksInhale, TicksExhale);
  return 0;
}
  
void GHVentilator::Update() {
  int Tick = Ticks;
  if (Tick == 0) return;
  if (Tick < 0) {
    if (--Tick <= TicksCalibration) {
      StateCalibrateExit ();
      return;
    }
    int Pressure = this->Pressure;
    if (Pressure >= PressureMax) {
        this->PressureMax = Pressure;
    }
    Ticks = Tick;
    return;
  }
  // else Tick > 0
  if (++Ticks >= TicksMonitor) {
    Ticks = StateRunningEnter;
    Monitor ();
  }
  else {
    Ticks = Tick;
  }
  
  // 1.) Turn off or on the blower.
  float Pressure = this->Pressure;
  if (Pressure < PressureMin) Blower = 1;
  else if (Pressure > PressureMax) Blower = 0;
  
  for (int Index = ChannelsCount - 1; Index >= 0; --Index)
    Channels[Index]->Update();
}

void GHVentilator::Run(){
  DPrintIndent (100, "Starting GHVentilator...\r\n\r\n");

  UpdateTicker.attach (callback(this, &GHVentilator::Update), 
                       1.0f / float (TicksSecond));
    
  while (1) Poll ();
}
/*
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
  DPrintf("\n? Object name=\"%s\" method_name=\"%s\" <",input->obj_name,input->method_name);
  for (int i=0; i < input->argc; i++)
    DPrintf("argv[%1d] = %s \n",i,input->argv[i]);
  
  int Index = input->getArg<int>();
  int TicksInhale = input->getArg<int>();
  int TicksExhale = input->getArg<int>();
 
  // The output parameter string is generated by calls to putData, which separates them with spaces.
  output->putData(Channel->TicksInhaleExhaleSet(TicksInhale, TicksExhale));
}


RPCFunction TicksSecondSet(&HandleTicksSecondSet, "TicksSecondSet"),
            InhaleExhaleTicksSet(&HandleTicksInhaleExhaleSet, "InhaleTicksSet");
          */  
}   //< namespace SickBay
