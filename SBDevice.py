"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/sickbay.git
@file    /SBDevice.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

import SBNode

# A SickBay device with a Device ID (DID).
class SBDevice(SBNode):

  def __init__(self):
    super().__init__()
    self.DID = 0                  #< The Device ID.
    self.Name = "SickBay"         #< The Device name in UpperCaseCamel.
    self.Description = "SickBay"  #< The description of this Device.
  
  def __init__(self, DID, Name, Description):
    self.DID = DID                #< The Device ID.
    self.Name = Name              #< The Device name in UpperCaseCamel.
    self.Description = "SBDevice" #< The description of this Device.
    
  def DescriptionSet(self, Description):
    self.Description = Description

  def DescriptionPrint (self):
    print (self.Description)
