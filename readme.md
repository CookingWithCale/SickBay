# SickBay

Open-source emergency medical equipment, SickBay app, and Gravity Hookah Ventilator design files and firmware for the [Pandemic Cookbook](https://pandemiccookbook.org).

## SickBay App

The SickBay app is a Python app for controlling and monitoring SickBay hardware. The SickBay app talks to mbed hardware via [mbed RPC](https://os.mbed.com/cookbook/Interfacing-Using-RPC). The app models the human body so that Medical caretakers can enter in real-world measurements such as patient height, weight, age, sex, and the app calculates the optimal settings for the SickBay hardware.

The SickBay app needs to be able to control and interface with open-source Ventilators and to monitor heart rate and blood O2 absortion rate (SpO2) using a 7-pin pulse oximeter, and to be able to monitor and control off-the-shelf blood pressure monitors.

The SickBay hardware firmware is designed to not do any intense calculations because microcontrollers are VERY VERY slow at division, so all calculations need to be done on a PC. The SickBay app must be able to hot swap hardware and the Hardware should not need to be reset if the connection to the PC is lost. The SickBay is to monitor and control the hardware, but the hardware must run independently from the PC.

## Modules

### Respiratory

#### Ventilators

* [Gravity Hookah Ventilator](./respiratory/ventilators/ventilator.gravity_hookah) - A low-cost rapid manufacturable ventilator from Home Depot and Electronic hobby store parts.

### Vital Sign Monitors

* [Blood Pressure Monitor](./vital_sign_monitors/blood_pressure_monitor) - A modification for off-the-self blood pressure monitors to interface with the SickBay app.
* [Pulse Oximeter](./vital_sign_monitors/pulse_oximeter) - A modification for an NS-100A fingertip pulse oximeter to measure pulse and blood oxygen absorption rate (SoO2).

## How to Contribute

The best way to learn how to contribute to SickBay is to read the Quickstart Guide of the Pandemic Cookbook at <https://pandemiccookbook.org/getting_started/quickstart_guide>.

## License

Copyright © 2020 [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
