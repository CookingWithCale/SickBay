# !/usr/bin/python
# -*- coding: utf-8 -*-
# Crabs @version 0.x
# @link    https://github.com/KabukiStarship/Crabs.git
# @file    /SBNode.py
# @author  Cale McCollough <https://cale-mccollough.github.io>
# @license Copyright 2020 (C) Kabuki Starship <kabukistarship.com>; all rights 
# reserved (R). This Source Code Form is subject to the terms of the Mozilla 
# Public License, v. 2.0. If a copy of the MPL was not distributed with this 
# file, you can obtain one at <https://mozilla.org/MPL/2.0/>.

from shlex import split
import re
from Stringf import *
  
# A Crabs tree node with a unique Node ID (NID).
# Example
# ```Script2
# ><.Intake CaptainKabuki Name="Cale McCollough" DoB="4/1/2020"
# ><.DoB.Set "3/31/2020" <
# ><.Foo 1.234
# ><.Print
# ><.PrintStats
# ><.ListDetails
# ```
class SBNode:
  # Consants
  ScanningChildKey = 1             #< Scanning a Child key.
  ScanningMetaKey = 2              #< Scanning a metadata key.

  def __init__(self, Crabs, TypeID = 0, Type = ""):
    self.Parent = Crabs.Top    #< This node's parent.
    self.NID = Crabs.NIDNext() #< The globally unique Node ID.
    self.TID = TypeID          #< The class unique Type ID.
    self.Meta = {              #< The Meta members
      "Type": Type,            #< The Type of the SBNode.
      "Name": "",              #< The Node name in any format.
      "Description": "",       #< The description of this Device.
      "Help": ""               #< The help string.
    }
    self.Children = {}      #< The child SBNodes.
    # Callable Crabs functions.
    self.Functions = {
      ">":    SBNode.Push,
      "<":    SBNode.Pop,
      ">><<": SBNode.PopAll,
      "*":    SBNode.Bang,
      "$":    SBNode.DepthCounterReset,
      "`":    SBNode.PrintStats,
      "?":    SBNode.List,
      "^":    SBNode.PushParent,
      ".":    SBNode.ListChildren,
      "#":    SBNode.ListMeta,
      "!":    SBNode.ListDetails,
      "help": SBNode.PrintHelp,
    } 
    Crabs.Push(self)

  # Function resest the DepthCounter.
  def DepthCounterReset(self, Crabs, Command, Cursor):
    return Crabs.DepthCounterReset
    
  # Pushes this node on the Crabs stack.
  def Push(self, Crabs, Command, Cursor):
    return Crabs.Push(self, Command, Cursor)
    
  # Pushes this node on the Crabs stack.
  def PushParent(self, Crabs, Command, Cursor):
    return Crabs.Push(self.Parent, Command, Cursor)
  
  # Pops this node off of the Crabs stack.
  def Pop(self, Crabs, Command, Cursor):
    return Crabs.Pop(Command, Cursor)
  
  # Pops this node off of the Crabs stack.
  def PopAll(self, Crabs, Command, Cursor):
    return Crabs.PopAll(Command, Cursor)
  
  # Resets the push count.
  def PushCountReset(self):
      self.CommandPushCount = 0

  # Gets the length of the path from the root.
  def PathDepth(self, Length = 0):
    Parent = self.Parent
    if Parent == self:
      return Length
    return Parent.PathDepth(Length) + 1

  def Path(self, PathString = "><."):
    Parent = self.Parent
    if self == Parent:
      return PathString
    return Parent.Path(PathString) + self.Key() + '.'
    
  def FunctionsAdd(self, Key, Mapping):
    self.Functions[Key] = Mapping

  def FunctionsRemove(self, Key):
    del(self.Functions[Key])
  
  # Gets the name Metadata.
  def Name(self):
    return self.Meta["Name"]
  
  # Sets the Name metadata to the new Name if it's not nil.
  def NameSet(self, Name):
    if Name is None: return None
    self.Meta["Name"] = Name
    return Name
  
  # Loads a Node from the URI.
  # @todo Write me!
  def Load(self, URI):
    if self.Meta["URI"] == None:
      return
  
  # Loads a Node from the URI.
  # @todo Write me!
  def Save(self, URI):
    pass

  # Gets the Member with the given Key
  def Get (self, Key):
    if (Key not in self.Meta): return None
    return self.Meta[Key]
  
  # The member count.
  def MemberCount(self): return len(self.Meta)
  
  # The children Nodes that you can push onto the stack.
  def ChildCount(self): return len(self.Children)
  
  # Gets a child by the index of it's Key.
  def ChildNumber(self, Index): 
      return self.Children.values()[Index]
  
  # Adds a Key-Value pair to the Children or Meta
  def Metadata(self, Key, Value):
      self.Meta[Key] = Value
  
  # Adds a Key-Value pair to the Children or Meta
  def Add(self, Crabs, Key, Value, Command = None):
    self.COut("? Adding Key " + Key + " <\n")
    self.Children[Key] = Value

    Crabs.Pop()
    self.COut("? Added Key " + Key + " <\n")
    
  # Removes the given Key from the Meta
  def Remove(self, Key):
    if (Key in self.Children):
      del self.Children[Key]
    if (Key in self.Meta):
      del self.Meta[Key]
  
  # Removes the given node index
  def RemoveIndex(self, Index):
    if Index >= 0 and Index < len(self.Children):
      del self.Children[Index]
  
  def SearchNID(self, NID):
    Results = []
    for Node in self.Children:
      Node.NID == NID
    return Results
  
  # Searches for child and member contents that starts with the query.
  def Search(self, Key, Query):
    Results = []
    if self.NID.startswith(Query):
      Results += self
      for Node in self.Children:
        if Node.Meta[Key].startswith(Query):
          Results += Node
      return Results
    if Query == "Key":
      Results += self
    for Member in self.Meta:
      if Member.Meta[Key].startswith(Query):
        Results += Member
    for Node in self.Children:
      if Node.Meta[Key].startswith(Query):
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
  
  # Searchs the Crabs for the Query.
  def Search(self, Crabs, Query):
    Results = []
    for Node in self.Children:
      if (Node.NID == str(Node.NID) or
          Query in self.Meta or
          self.Meta["Name"].startswith(Query) or
          self.Meta["Key"].find(Query) == 0):
        Results.append(Node)
    return Results
  
  def HandleSet(self, Key):
    self.Key = Key
  
  def DescriptionSet(self, Description):
    self.Description = Description
  
  def Description(self):
    return self.Meta["Description"]
  
  def DescriptionSet(self, Description):
    self.Meta["Description"] = Description
    
  # Prints the String indented the current Path depth.
  def Print(self, String = ""):
    return Stringf.Indent(self.PathDepth() + 1, String)
    
  # Prints the String indented the current Path depth.
  def PrintError(self, String):
    return Stringf.Indent(">< Error " + String + " <")
    
  # Prints the String indented the current Path depth.
  def COut(self, String= ""):
    return COut.Indent(self.PathDepth() + 1, String)
    
  # Prints the String indented the current Path depth.
  def CCOutHint(self, String):
    return self.COut("? " + String + " <")
  
  # Prints the path to the 
  def COutPath(self):
    return COut.PrintLn(self.Path ())
  
  # Prints out the most important information.
  def PrintStats(self, String = "", SelfKey = None):
    self.COut("? Printing Stats <\n")
    if SelfKey != None:
      String += SelfKey + " "
    for Key, Value in self.Children.items() :
      Value.PrintStats(String, Key)
    return String
  
  # Prints a human-readable help string.
  def PrintHelp(self, String = "", Indent = 0, SelfKey = None):
    String += Stringf.Indent(Indent, "> ") + SelfKey + ".Help" + \
              Stringf.Indent(Indent + 1, "") + self.Meta["Help"]
    for Child in self.Children:
      Child.PrintHelp(String, SelfKey, Indent + 1)

  # Gets this node's Key.
  def Key(self):
    if self == self.Parent:
      return "><"
    #self.COut("? Searching for Key for NID:" + str(self.NID) + " <\n")
    for Key, Value in self.Parent.Children.iteritems():
      if Value == self:
        return Key
    return "MissingKey"
  
  # Returns a string with all of the Keys in the Meta and Children indented to the PathDepth().
  def ListMeta(self, SickBay, Command, Cursor):
    Result = ""
    Index = len(self.Children)
    for Key, Value in self.Meta.items():
      Index += 1
      String = str(Index) + ". " + Key + ":" + Value.__class__.__name__
      Result += Stringf.Indent(self.PathDepth() + 1, String)
    return Result
  
  # Returns a string with all of the Keys in the Meta and Children indented to the PathDepth().
  def ListChildren(self, SickBay, Command, Cursor):
    Index = 0
    Result = ""
    for Key, Value in self.Children.items():
      Index += 1
      String = str(Index) + ". " + Key + ":" + Value.__class__.__name__ + ":" + str(Value.NID)
      Result += Stringf.Indent(self.PathDepth() + 1, String)
    return Result
  
  # Returns a string with all of the Keys in the Meta and Children indented to the PathDepth().
  def List(self, SickBay, Command, Cursor):
    Depth = self.PathDepth ()
    String = Stringf.Indent(Depth, "> " + self.Key())
    String += self.ListChildren(SickBay, Command, Cursor)
    String += Stringf.Indent(Depth + 1, "> Meta")
    String += self.ListMeta (SickBay, Command, Cursor)
    String += Stringf.Indent(Depth + 1, "<")
    String += Stringf.Indent(Depth, "<")
    return String
  
  # Returns a string with all of the Keys in the Meta and Children indented to the PathDepth().
  def ListDetails(self, SickBay, Command, Cursor):
     self.List(SickBay, Command, Cursor)
  
  # The function that is called when a Duck typed member is created.
  def PushDuck(self, Crabs, Key, Command, Cursor):
    self.COut("#Duck " + Command)
    NID = Crabs.NIDNext()
    Node = SBNode(Crabs)
    self.Children[Key] = Node
    return Crabs.Push(Node.Command(Crabs, Command, Cursor))

  def CommandKeyNext(self, Crabs, Args):
    Tokens = Args.split(".", 1)
    if Tokens[0] in self.Children: return Tokens
    return None

  # The number of Meta plus the number of children.
  def MemberCount(self):
    return len(self.Meta) + len(self.Children)
  
  # Runs the common commands and returns None if no commands were executed.
  def CommandSuper(self, Crabs, Command, Cursor):
    if Command == None or Cursor >= len(Command): return None
    if Command == "": return None
    self.COut("#Super " + Command)
    Char = Command[Cursor]
    while Char <= ' ':
      self.COut("? Skipping leading whitespace and pushing non-printable "\
                "nodes. <")
      # IMUL is a superset of Script2, and Char ASCII C0 Codes 0-8 push NID0 
      # through NID8 onto the stack and ASCII C0 Codes 11-31 push on child 0-20.
      if Char == 0: return None
      if Char == 1: return ">< Error Byte compresson not implemented. <"
      if Char < '\t':
        return Crabs.PushChildNumber(Char, Command, Cursor)
      if Char > '\n':
        if Char != ' ':
          return Crabs.Push(self.ChildNumber(int(Char - '\n')),
                              Command, Cursor)
      Cursor += 1
      if Cursor >= len(Command): return None
      Char = Command[Cursor]
      
    Cursor = Stringf.PeekNumber(Command, Cursor)
    if Cursor > 0:
      Index = int(Command[CursorStart: Cursor])
      self.COut("? Pushing " + str(Index))
      return Crabs.Push(self.ChildNumber(Index), Command, Cursor)
    elif Cursor < 0:
        return Crabs.PushNID(Index * -1, Command, -Cursor)
    self.COut("? Scanning a Key. <")
    Arg = 0
    ParsingsArguments = 0
    while ParsingsArguments == 0:
      Arg += 1
      self.COut("? Parsing Argument " + str(Arg) + " <")
      CursorStart = Cursor
      TokenEnd = Stringf.TokenNext(Command, Cursor)
      if TokenEnd == Cursor: return None
      Key = Command[Cursor: TokenEnd]
      self.COut("? Found Key " + Key + " <")
      Cursor = TokenEnd
      if Cursor >= len(Command): 
        if Key in self.Functions:
          Function = self.Functions[Key]
          self.COut("? Found Function " + Key + " <")
          Result = Function(self, Crabs, Command, Cursor)
          if Result:
            self.COut("? Found result: <\n")
            self.COut(Result)
        return self.PushDuck(Crabs, Key, Command, Cursor)
      Char = Command[Cursor]
      if Char == '=':
        self.COut("? Found meta key. <")
        Value = None
        Delta = Stringf.PeekNumber(String, Cursor)
        if Delta > 0:
          TokenEnd = Cursor + Delta
          Value = int(Command[Cursor: TokenEnd])
        elif Delta < 0:
          TokenEnd = Cursor - Delta
          Value = float(Command[Cursor: TokenEnd])
        else:
          Delta = Stringf.PeekString(String, Cursor)
          if Delta > 0:
            TokenEnd = Cursor + Delta
            Value = Command[Cursor: TokenEnd]
          elif Delta < 0:
            TokenEnd = Cursor - Delta
            Value = Command[Cursor:TokenEnd - 1]
          else:
            return None
        self.Meta[Key] = Value
      self.COut("? Key was not meta value. <")
    return None
  
  # Triggers all of the children to Bang!
  def Bang(self, Crabs, Result):
    for Child in self.Children:
      Child.Bang(Result)
    return Result
  
  # Issues a Console command to this node.
  # ><.Intake.Metadata Foo="" Name="Harry" Description=""
  def Command(self, Crabs, Command, Cursor):
    Result = self.CommandSuper(Crabs, Command, Cursor)
    if Result == None: return Result
    if Result[0] == '<': return Result
    
    self.COut("#Self " + Command, Cursor)
    if Result != None:
      return Result
    return None
  
  # Runs a command from a file.
  def CommandRun(self, Crabs, Cursor, Filename):
    File = open(Filename, "r")
    return self.Command(Crabs, 0, File.read(1))
  
  # Function to call when starting a command.
  def CommandStart(self, Crabs, Command, Cursor):
    self.Command(Crabs, Command, Cursor)
    if self.ModeStackRestore:
      for X in range(self.StackPushCount):
        self.Pop(Crabs)
      self.StackPushCount = 0
