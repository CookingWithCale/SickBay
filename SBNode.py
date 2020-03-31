#!/usr/bin/python
# -*- coding: utf-8 -*-
"""SickBay @version 0.x
@link    https://github.com/KabukiStarship/SickBay.git
@file    /SBNode.py
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. """

from shlex import split
import time
import SBPrint

SBNodeIDCount = 0  #< The static node count.
def SBNodeNIDNext():
  Result = SBNodeIDCount
  SBNodeIDCount += 1
  return Result
  
# A SickBay tree node with a unique Node ID (NID).
class SBNode:
  
  def __init__(self):
    self.Nodes = []                #< The child SBNodes.
    self.NID = SBNode.SBNodeNIDNext()    #< The Node ID.
    self.Type = Type               #< The node Type in UpperCaseCamel.
    self.Handle = Handle           #< The Node name in any format.
    self.Name = Name               #< The Node name in any format.
    self.Description = Description #< The description of this Device.
    self.Help = Help               #< The help string.
  
  #def __init__(self, Type = "", Handle = "", Name = "", Description = "", Help=""):
  #  self.Nodes = []                #< The child SBNodes.
  #  self.NID = SBNode.SBNodeNIDNext()    #< The Node ID.
  #  self.Type = Type               #< The node Type in UpperCaseCamel.
  #  self.Handle = Handle           #< The Node name in any format.
  #  self.Name = Name               #< The Node name in any format.
  #  self.Description = Description #< The description of this Device.
  # self.Help = Help               #< The help string.
  
  def Count(self): return len(self.Nodes)

  def NodesAdd(self, Node):
    self.Nodes.append(Node)
  
  def NodesRemove(self, Index):
    if Index >= 0 and Index < len(self.Nodes):
      del self.Nodes[Index]
  
  def NodesSearch(self, Query):
    Results = []
    for Node in self.Nodes:
      if (Node.NID == str(Node.NID) or
          self.Name.startswith(Query) or
          self.Handle.find(Query) == 0):
        Results.append(Node)
    return Results
  
  def TypeSet(self, Type):
    self.Type = Type
  
  def HandleSet(self, Handle):
    self.Handle = Handle
  
  def DescriptionSet(self, Description):
    self.Description = Description
  
  def Print(self, Indent = 0):
    SBPrint.Indent(Indent, "NID: " + self.NID + "Type: " + self.Type  + 
                       "Handle: " + self.Handle + "Name: " + self.Name)
  
  def PrintAll(self, Indent = 0):
    self.Print(Indent)
    SBPrint.Indent(Indent, "Children: Count", self.NodesCount (), " { ")
    for Node in self.Nodes:
      print(Node.Handle + ", ")
    print (" }")
    SBPrint.Indent(Indent, "Description" + self.Description)
  
  def Command(self, Command):
    # Commands that list the child notes by group, NID, Type, Handle, or Name.
    Command = Command.lower()
    Results = []
    if Command[0].isnumeric():
      IndexLength = 1
      Index = 1
      while Command[Index].isnum(): Index += 1
      Index = int(Command[0:Index - 1])
      if Index >= 0 and Index < len(self.Nodes):
        Results.append(self.Nodes[Index])
        return Results
    if (Command == "list"):
      for Node in self.Nodes:
        Results.append(Node)
      return Results
    elif Command.startswith("search nid "):
      Query = Command[10:]
      for Node in self.Nodes:
        if str(Node.NID).find(Query):
          Results.append(Node)
      return Results
    elif Command.startswith("search type "):
      Query = Command[11:]
      for Node in self.Nodes:
        if(Node.Type.find(Query)):
          Results.append(Node)
      return Results
    elif Command.startswith("search handle "):
      Query = Command[13:]
      for Node in self.Nodes:
        if(Node.Handle.find(Query)):
          Results.append(Node)
      return Results
    elif Command.startswith("search name "):
      for Node in self.Nodes:
        if(Node.Name.find(Query)):
          Results.append(Node)
      return Results
    elif Command.startswith("search description "):
      for Node in self.Nodes:
        if(Node.Description.find(Query)):
          Results.append(Node)
      return Results
    for Node in self.Nodes:
      if (Node.Handle) == Query:
        Results.append(Node)
        return Results
    return Results
