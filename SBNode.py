# !/usr/bin/python
# -*- coding: utf-8 -*-
# SickBay @version 0.x
# @link    https://github.com/KabukiStarship/SickBay.git
# @file    /SBNode.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from shlex import split
import time
from SBPrint import SBPrint
  
# A SickBay tree node with a unique Node ID (NID).
class SBNode:

  def __init__(self, SickBay, Handle = "", Type = "", Name = "", Description = "", Help=""):
    self.NID = SickBay.NIDNext ()  #< The Node ID.
    self.Parent = SickBay.Top.NID  #< This node's parent NID.
    self.Handle = Handle           #< The Node name in any format.
    self.Members = {               #< The Metadata members
      "Type": Type,                #< The node Type in UpperCaseCamel.
      "Name": Name,                #< The Node name in any format.
      "Description": Description,  #< The description of this Device.
      "Help": Help                 #< The help string.
    }
    self.Nodes = []                #< The child SBNodes.
  
  # Loads a Node from the URI.
  # @todo Write me!
  def Load(self, URI):
    if self.Members["URI"] == None:
      return
  
  # Loads a Node from the URI.
  # @todo Write me!
  def Save(self, URI):
    pass

  # Gets the Member with the given Key
  def Get (self, Key):
    if (Key not in self.Members): return None
    return self.Members[Key]
  
  def NodesCount(self): return len(self.Nodes)

  def Add(self, Node):
    self.Nodes.append(Node)
    
  # Removes the given Key from the Members
  def Remove(self, Key):
    if (Key not in self.Members): return
    del self.Members[Key]
  
  # Removes the given node index
  def RemoveIndex(self, Index):
    if Index >= 0 and Index < len(self.Nodes):
      del self.Nodes[Index]
  
  def SearchNID(self, NID):
    Results = []
    for Node in self.Nodes:
      Node.NID == NID
    return Results
  
  # Searches for SBNode contents that starts with the query.
  def Search(self, Tag, Query):
    Results = []
    if self.NID.startswith(Query):
      Results += self
      for Node in self.Nodes:
        if Node.Members[Tag].startswith(Query):
          Results += Node
      return Results
    if Query == "Handle":
      Results += self
    for Member in self.Members:
      if Member.Members[Tag].startswith(Query):
        Results += Member
    for Node in self.Nodes:
      if Node.Members[Tag].startswith(Query):
        Results += Node
    return Results
  
  # Searches this node for a tag that contains the query.
  def Find(self, Tag, Query):
     pass

  def Search(self, Query):
    Results = []
    for Node in self.Nodes:
      if (Node.NID == str(Node.NID) or
          self.Members["Name"].startswith(Query) or
          self.Members["Handle"].find(Query) == 0):
        Results.append(Node)
    return Results
  
  def TypeSet(self, Type):
    self.Type = Type
  
  def HandleSet(self, Handle):
    self.Handle = Handle
  
  def DescriptionSet(self, Description):
    self.Description = Description
  
  def Description(self):
    return self.Members["Description"]
  
  def DescriptionSet(self, Description):
    self.Members["Description"] = Description
  
  def Print(self, Indent = 0):
    SBPrint.Indent(Indent, "NID: " + self.NID + "Type: " + self.Type() + 
                   "Handle: " + self.Handle() + "Name: " + self.Name() +
                   "Description: " + self.Description())

  def PrintHelp(self):
    print(self.Members["Help"])
  
  def PrintAll(self, Indent = 0):
    self.Print(Indent)
    SBPrint.Indent(Indent, "Children: NodesCount" + self.NodesCount () + " { ")
    for Node in self.Nodes:
      print(Node.Handle + ", ")
    print (" }")
    SBPrint.Indent(Indent, "Description" + self.Members["Description"])
  
  def Command(self, SickBay, Command):
    if Command == "":
      self.PrintStats()
      return ""
    if Command == "?":
      self.PrintHelp()
      return ""
    if Command.isdigit():
      Index = int(Command)
      SickBay.Push (self)
      return ""
    Results = SBNode(SickBay, self.NID)
    if Command[0].isdigit():
      # This means we're going to feed a node a string but not push it on the
      # SickBay.Stack
      Index = 1
      while Command[Index].isdigit(): Index += 1
      if Command[Index] != " ":
        return ("\nERROR: you must put a space after the NID. Try this:" +
               "\n> 0 handle\n< Results: SickBay")
      Index = int(Command[0:Index])
      if Index == 0:
        SickBay.Push(SickBay)
      if Index >= 0 and Index < len(self.Nodes):
        Results.Push(self.Nodes[Index])
        SickBay.Push(Results)
        return ""
    if (Command == "*"):
      for Node in self.Nodes:
        Results.append(Node)
      return Results
    elif Command.startswith("? "):
      Query = Command[10:]
      for Node in self.Nodes:
        if str(self.Node.NID).find(Query):
          Results.append(Node)
      return Results
    for Node in self.Nodes:
      if self.Node.Handle == Command:
        Results.append(Node)
        return Results
    return Results
