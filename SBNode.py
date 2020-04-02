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
import sys
  
# A SickBay tree node with a unique Node ID (NID).
class SBNode:
  HelpDefault = ("This is a Generic node that contains a collection of Keys " +
                 "that you push Nodes onto the SickBay Stack, which is best " +
                 "described as putting playing cards on a stack face down " +
                 "with one card face up on top, and your manipulate the " +
                 "face up card. You push items on the stack either by their " +
                 "index 0, 1, ...N, or, by their Key by typing it in and " +
                 "pressing enter, or by the unique Node ID (NID) which you " +
                 "enter as a negative number." +
                 "Example Command 1> Foo" +
                 "Example Command 2> Foo add" +
                 "\n")

  def __init__(self, SickBay, Type = "", TypeCount = 0, Arguments=""):
    self.NID = SickBay.NIDNext ()  #< The Node ID.
    self.TypeCount = TypeCount     #< The unique index of the Type created.
    self.Parent = SickBay.Top      #< This node's parent.
    self.Members = {               #< The Metadata members
      "Type": "",                  #< The node Type in UpperCaseCamel.
      "Name": "",                  #< The Node name in any format.
      "Description": "",           #< The description of this Device.
      "Help": ""                   #< The help string.
    }
    self.Children = {}             #< The child SBNodes.
    #self.Push(SickBay)

  def Push(self, SickBay):
    SickBay.Stack.append(SickBay.Top)
    SickBay.Top = self

  def Pop(self, SickBay):
    SickBay.Top = SickBay.Stack.pop()
  
  def PushKey(self, SickBay, Key):
    if (Key in self.Children):
      self.Children[Key].Push(SickBay)
  
  def Name(self):
    return self.Members["Name"]
  
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
  
  def Command(self, Arguments):
    Loop = True
    while Loop:
      Args = Arguments.split("=", 1)
      if (len(Args) == 1):
        return ""
      Key = Args[0].strip()
      if " " in Key:
        return "ERROR: Spaces aren't allowed in Keys."
      if "." in Key:
        return "ERROR: Nested children are not implemented yet."
      Strings = Args[1].spilt("\"", 2)
      if len(Strings) == 3:
        self.Add(Key, Strings[1])
        return ""
      String = Args[1].lstrip()
      Args = Arguments.split(" ", 1)
      String = Args[0]
      try: 
        self.Add(Key, int(String))
        return ""
      except ValueError:
        pass
      try: 
        self.Add(Key, float(String))
        return ""
      except ValueError:
        return ""
      Arguments = Args[1]
      if (len(Args[1]) == 0):
        Loop = False
  
  def MemberCount(self): return len(self.Members)
  
  def ChildCount(self): return len(self.Children)
  
  def Add(self, Key, Value):
    if Value == None:
      return
    if isinstance(Value, SBNode):
      self.Children[Key] = Value
    else:
      self.Members[Key] = Value

  def AddChild(self, Key, Value):
    self.Children[Key] = Value
    
  # Removes the given Key from the Members
  def Remove(self, Key):
    if (Key in self.Children):
      del self.Children[Key]
    if (Key in self.Members):
      del self.Members[Key]
  
  # Removes the given node index
  def RemoveIndex(self, Index):
    if Index >= 0 and Index < len(self.Children):
      del self.Children[Index]
  
  def SearchNID(self, NID):
    Results = []
    for Node in self.Children:
      Node.NID == NID
    return Results
  
  # Searches for SBNode contents that starts with the query.
  def Search(self, Key, Query):
    Results = []
    if self.NID.startswith(Query):
      Results += self
      for Node in self.Children:
        if Node.Members[Key].startswith(Query):
          Results += Node
      return Results
    if Query == "Key":
      Results += self
    for Member in self.Members:
      if Member.Members[Key].startswith(Query):
        Results += Member
    for Node in self.Children:
      if Node.Members[Key].startswith(Query):
        Results += Node
    return Results
  
  # Searchs for the NID in this object and it's children.
  def FindNID(self, NID):
    if self.NID == NID:
      return self
    for Child in self.Children:
      Child.FindNID(NID)
    return None
  
  # Searches this node for with a Key.
  def Find(self, Key):
    if Key in self.Children:
      return self.Children[Key]
    return None    

  def Search(self, SickBay, Query):
    Results = []
    for Node in self.Children:
      if (Node.NID == str(Node.NID) or
          Query in self.Members or
          self.Members["Name"].startswith(Query) or
          self.Members["Key"].find(Query) == 0):
        Results.append(Node)
    return Results
  
  def TypeSet(self, Type):
    self.Type = Type
  
  def HandleSet(self, Key):
    self.Key = Key
  
  def DescriptionSet(self, Description):
    self.Description = Description
  
  def Description(self):
    return self.Members["Description"]
  
  def DescriptionSet(self, Description):
    self.Members["Description"] = Description
  
  def PrintStats(self, String = "", SelfKey = None):
    print ("\nPrinting Stats")
    if SelfKey != None:
      String += SelfKey + " "
    for Key, Value in self.Children.iteritems() :
      Value.PrintStats(String, Key)
    return String
  
  def PrintDetails(self, String = "", Indent = 0, SelfKey = None):
    String += SBPrint.Indent("> ", Indent) + ".Details"
    if SelfKey != None:
      String += SelfKey
    for Key, Value in self.Children.iteritems() :
      Value.PrintDetails(String, Indent + 1, Key)
    return String
  
  # Prints a human-readable help string.
  def PrintHelp(self, String = "", Indent = 0, SelfKey = None):
    String += SBPrint.Indent("> ", Indent) + SelfKey + ".Help" + \
              SBPrint.Indent("", Indent + 1) + self.Members["Help"]
    for Child in self.Children:
      Child.PrintHelp(String, SelfKey, Indent + 1)
  
  # Prints the List() to the COut
  def Print(self, Indent = 0):
    SBPrint.COut(self.List())

  def Key(self):
    if self == self.Parent:
      return "><"
    for Key, Value in self.Children.iteritems():
      if (Value == self):
        return Key
    return ""

  def Path(self, Path = ""):
    Parent = self.Parent
    if self != Parent:
      return Parent.Path(Path)
    return Path + self.Key() + "."
  
  # Returns a string with all of the Keys in the Members and Children.
  def List(self):
    Index = 0
    Result = "{ Members: { "
    for Key, Value in self.Members.iteritems():
      Result += Key + ":" + Value.__class__.__name__ + ", "
    Result += "} Children: { "
    for Key, Value in self.Children.iteritems():
      Result += Key + ":" + Value.__class__.__name__ + ", "
    Result += "} }"
    return Result
  
  # Issues a Console command to this node.
  # Intake.Add Token="" Name="Harry" Description=""
  # 
  def Command(self, SickBay, Command):
    if Command == "":
      print("\nAttempting to PrintStats")
      return self.PrintStats()
    if Command == "..":
      self.Pop(SickBay)
    Tokens = Command.split(".", 1)
    Target = Tokens[0]
    TokensLength = len(Tokens)

    if Command == "list":
      return "\n> " + self.List()
    
    if Target == "?" or Target == "help":
      if TokensLength == 1:
        self.PrintHelp()
        return ""
      if TokensLength > 1:
        return ("ERROR: Must enter a ? or help followed by either a child " +
                "Node ID (NID) or Key, a negative to select an index " +
                "number, the word All.\nExample 1:? Foo\nExample 2:? all")
      ObjectToken = Tokens[1]
      if ObjectToken == "all" or ObjectToken == "*":
        self.PrintHelp()
        for Child in self.Children:
          Child.PrintHelp()
        return ""
      if ObjectToken in self.Children:
        SickBay.Push(self.Children[ObjectToken])
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
      if Index >= 0 and Index < len(self.Children):
        Results.Push(self.Children[Index])
        SickBay.Push(Results)
        return ""
    if (Command == "*"):
      for Node in self.Children:
        Results.append(Node)
      return Results
    elif Command.startswith("? "):
      Query = Command[10:]
      for Node in self.Children:
        if str(self.Node.NID).find(Query):
          Results.append(Node)
      return Results
    return Results
