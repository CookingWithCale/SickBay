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
from Stringf import *
import re
  
# A SickBay tree node with a unique Node ID (NID).
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

  def __init__(self, SickBay, Command, Type, TID):
    self.NID = SickBay.NIDNext ()  #< The globally unique Node ID.
    self.TID = TID                 #< The class unique Type ID.
    self.Parent = SickBay.Top      #< This node's parent.
    self.Meta = {                  #< The Meta members
      "Type": "",                  #< The node Type in UpperCaseCamel.
      "Name": "",                  #< The Node name in any format.
      "Description": "",           #< The description of this Device.
      "Help": ""                   #< The help string.
    }
    self.Children = {}             #< The child SBNodes.
    # Callable Crabs functions.
    self.Functions = {
      "<":  "Pop",
      "*":  "Bang",
      ".":  "PushCountReset",
      "!":  "ListDetails",
      "\"": "PrintStats",
      "?":  "List",
      "#":  "ListMeta",
      "$":  "ListChildren",
      "help":  "PrintHelp",
    }
    
    # Pushes this node on the SickBay stack.
    def Push(self, SickBay, Command = ""):
      return SickBay.Push(self, Command)
    
    # Pops this node off of the SickBay stack.
    def Pop(self, SickBay, Command = ""):
      return SickBay.Pop(Command)
    
    self.COut("> " + self.Key())
    Result = self.Command(SickBay, Command)
    if Result != None:
      self.Meta["Error"] = Result
    SickBay.Push(self)
    self.COut("> Created Node <\n")
  
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
    return Parent.Path(PathString) + self.Key() + "."
    
  def FunctionsAdd(self, Key):
    self.Functions[Key] = None

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
  def Add(self, SickBay, Key, Value):
    self.COut("> Adding Key " + Key + " <\n")
    self.Children[Key] = Value
    SickBay.Pop()
    self.COut("> Added Key " + Key + " <\n")
    
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
  
  # Searchs the SickBay for the Query.
  def Search(self, SickBay, Query):
    Results = []
    for Node in self.Children:
      if (Node.NID == str(Node.NID) or
          Query in self.Meta or
          self.Meta["Name"].startswith(Query) or
          self.Meta["Key"].find(Query) == 0):
        Results.append(Node)
    return Results
  
  def TypeSet(self, Type):
    self.Type = Type
  
  def HandleSet(self, Key):
    self.Key = Key
  
  def DescriptionSet(self, Description):
    self.Description = Description
  
  def Description(self):
    return self.Meta["Description"]
  
  def DescriptionSet(self, Description):
    self.Meta["Description"] = Description
    
  # Prints the String indented the current Path depth.
  def Print(self, String):
    return Stringf.Indent(self.PathDepth() + 1, String)
    
  # Prints the String indented the current Path depth.
  def COut(self, String):
    return COut.Indent(self.PathDepth() + 1, String)
  
  # Prints out the most important information.
  def PrintStats(self, String = "", SelfKey = None):
    self.COut("> Printing Stats <\n")
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
    #self.COut("> Searching for Key for NID:" + str(self.NID) + " <\n")
    for Key, Value in self.Parent.Children.iteritems():
      if Value == self:
        return Key
    return "MissingKey"
  
  # Sets
  def MetaSet(self, Key, Value):
    self.Parent.Meta[Key] = Value
  
  # Returns a string with all of the Keys in the Meta and Children indented to a custom indent.
  def ListMetaIndented(self, Indent = 0):
    Result = ""
    Index = len(self.Children)
    for Key, Value in self.Meta.items():
      Index += 1
      String = str(Index) + ". " + Key + ":" + Value.__class__.__name__
      Result += Stringf.Indent(Indent, String)
    return Result
  
  # Returns a string with all of the Keys in the Meta and Children indented to the PathDepth().
  def ListMeta(self):
    return ListMetaIndented(self.PathDepth())

  # Returns a string with all of the Keys in the Meta and Children indented to a custom indent.
  def ListChildrenIndented(self, Indent = 0):
    Index = 0
    Result = ""
    for Key, Value in self.Children.items():
      Index += 1
      String = str(Index) + ". " + Key + ":" + Value.__class__.__name__ + ":" + str(Value.NID)
      Result += Stringf.Indent(Indent, String)
    return Result
  
  # Returns a string with all of the Keys in the Meta and Children indented to the PathDepth().
  def ListChildren(self, Indent = 0):
    return self.ListChildrenIndented(self.PathDepth())
  
  # Returns a string with all of the Keys in the Meta and Children to the PathDepth().
  def ListIndent(self, Indent = 0):
    String = Stringf.Indent(Indent, "> " + self.Key())
    String += self.ListChildrenIndented(Indent + 1)
    String += Stringf.Indent(Indent + 1, "> Meta")
    String += self.ListMetaIndented (Indent + 2)
    String +=  Stringf.Indent(Indent + 1, "<")
    String += Stringf.Indent(Indent, "<")
    return String
  
  # Returns a string with all of the Keys in the Meta and Children indented to the PathDepth().
  def List(self):
    return self.ListIndent(self.PathDepth())
  
  # Parses the string as either int, float, str, or None.
  def CommandArg(self, Args):
    try: 
      return int(Args)
    except ValueError:
      pass
    try: 
      return float(Args) # float(re.search('\d+\.*\d*', r).group(0))
    except ValueError:
      pass
    CommandArgs = Args.split("\"", 2)
    if (len(CommandArgs) == 3):
      return CommandArgs[1]
    return None
  
  # The function that is called when a Duck typed member is created.
  def CommandDuck(self, SickBay, Key, Command):
    self.COut("#Duck " + Command)
    self.Children[Key] = SBNode("Node", 0, SickBay, Command)
  
  def CommandKeyNext(self, SickBay, Args):
    Tokens = Args.split(".", 1)
    if Tokens[0] in self.Children: return Tokens
    return None

  # The number of Meta plus the number of children.
  def MemberCount(self):
    return len(self.Meta) + len(self.Children)

  # Runs the common commands and returns None if no commands were executed.
  def CommandSuper(self, SickBay, Command):
    if Command == None or Command == "": return None
    self.COut("#Super " + Command)
    
    self.COut("> Skipping whitespace. <")
    Char = Command[0]
    Cursor = 1
    while Char <= " ":
      # IMUL is a superset of Script2, and Char ASCII C0 Codes 0-8 push NID0 
      # through NID8 onto the stack and ASCII C0 Codes 11-31 push on child 0-20.
      if Char == 0:
        return None
      if Char == 1:
        return "<> Error Byte compresson not available the Python version of Script2 and IMUL. <"
      if Char < '\t':
        return SickBay.PushNID(int(Char - 2), Command[Cursor:])
      if Char > '\n':
        if Char != " ":
          return SickBay.Push(self.ChildNumber(int(Char - '\n')), Command[Cursor:])
      Char = Command[Cursor]
      Cursor += 1
    if Char == '-' or Char >= '0' and Char <= '9':
      CursorStart = Cursor
      Cursor += 1
      Char = Command[Cursor]
      while Char >= '0' and Char <= '9':
        Cursor += 1
        Char = Command[Cursor]
      Index = int(Command[CursorStart:Cursor])
      if Index < 0:
        return SickBay.PushNID(Index * -1, Command[Cursor:])
      return SickBay.Push(self.ChildNumber(Index), Command[Cursor:])
    
    if Cursor != 1: Command = Command[Cursor:] # Skip any whitespace.

    Arg = 0
    ParsingsArguments = 0
    while ParsingsArguments == 0:
      Arg += 1
      self.COut("> Parsing Argument " + str(Arg) + " <\n")
      self.COut("> Scanning until we get to a '.', ' ', '\t', or '\n', "\
                "or '='. <\n")
      CursorStart = Cursor
      ScanningLoop = 0
      ScanningMultiLineCommand = False
      while ScanningLoop == 0:
        # No non-printable characters in keys.
        if Char == 0: return None
        if Char < " " and Char != '\n' and Char != '\t': \
          return "<> Error Keys may not have non-printable characters in it. <"
        if Char == '.':
          Key = Command[CursorStart:Cursor]
          ScanningLoop = SBNode.ScanningChildKey
        elif Char == '\\':
          ScanningMultiLineCommand = True
        elif Char == '\n':
          if ScanningMultiLineCommand:
            ScanningMultiLineCommand = False
          else:
            return Command[Cursor:]
        elif Char == ' ' or Char == '\t':
          self.COut("> Scanning whitespace.")
          Cursor += 1
          Char = Command[Cursor]
          while Char == ' ' or Char == '\t':
            Cursor += 1
            Char = Command[Cursor]
        Cursor += 1
        Char = Command[Cursor]
      

      # Push items on the stack, creating them if they don't exist
      Scanning = 0
      Cursor = 0
      Char = Command[Cursor]
      while Scanning == 0:
        Cursor += 1
        if Char == ".":
          self.COut("> Found a period. <")
          Key = Command[0:Arg]
          if Key in self.Children:
            return SickBay.Push(self.Children[Key], Command[Arg:])
          return self.CommandDuck(SickBay, Command[0:Arg], Command[Arg:])
        if Char == " ":
          self.COut("> Found a space. <")
          Key = Command[0:Arg]
          Arg += 1
          Char = Command[Arg]
          while Char == " ":
            Arg += 1
            Char = Command[Arg]
          
          Scanning = 1
        elif Char == "=":
          self.COut("> Found a =. <")
          Scanning = 1
        else:
          Char = Command[Arg]

      self.COut("> Tokens " + str(Tokens))
      Key = Tokens[0].rstrip()
      Command = Tokens[1]
      self.COut("> Parsed Key \"" + Key + "\" Command=\"" + Command + "\" <\n")
      
      if Key in self.Children:
        self.COut("> Parsed an existing child Key. <\n")
        return SickBay.Push(self, Command)

      if Key in self.Meta:
        self.COut("> Parsed an existing metadata Key. <\n")
        Tokens = Command.split(" ", 1)
        self.Meta[Key] = self.CommandArg(Tokens[0])

      
      Tokens = Key.split(".", 1)
      if len(Tokens) == 1:
        self.COut("> The Key doesn't exist, it's a Duck! <\n")
        return self.CommandDuck(SickBay, Key, Command)

      self.COut("> The Key is hierarchial because it has at least one '.' in it. <\n")
      if len(Tokens) == 1:
        Pushing = False
      else:
        Tokens = Command.split(".", 1)
        Key = Tokens[0]
        if Key in self.Children:
          SickBay.Push(self.Children[Key], Command)
        elif Key in self.Meta:
            return "<> Error The Key:\"" + Key + "\" is a Metadata value and is not hierarchial. <\n"
    return self.Top.Command(SickBay, Command)
  
  # Triggers all of the children to Bang.
  def Bang(self, SickBay, Result):
    for Child in self.Children:
      Child.Bang(Bang)
    return Bang
  
  # Issues a Console command to this node.
  # ><.Intake.Metadata Foo="" Name="Harry" Description=""
  def Command(self, SickBay, Command):
    Result = self.CommandSuper(SickBay, Command)
    if Result == None: return Result
    if Result[0] == '<': return Result
    
    self.COut("#Self " + Command)
    if Result != None:
      return Result
    # At this point we can't push anymore Nodes on to the Crabs Stack.
    Tokens = Command.split(" ", 1)
    if len(Tokens) == 1:
      return None
    Command = Tokens[1]
    Key = Tokens[0]
    TokensLength = len(Tokens)
    if TokensLength == 1:
      return "<> Error Key, Index, or NID does not exist. <\n"
    Tokens = Key.split(".", 1)
    if len(Tokens) > 1:
      return self.CommandArgs(SickBay, Tokens[1])
    if Key == "set":
      Tokens = Tokens[1].split(" ", 1)
      Key = Tokens[0]
      if (len(Tokens) == 1):
        return "<> Error You have to have to type \"add Key Value\". <\n"
      self.Metadata(Key, self.CommandArg(Command))
      return ""
    if Key in self.Meta: # It's metadata
      return str(self.Meta[Key])
    return ""
  
  # Function to call when starting a command.
  def CommandStart(self, SickBay, Command):
    self.Command(SickBay, Command)
    if self.ModeStackRestore:
      for X in range(self.StackPushCount):
        self.Pop(SickBay)
      self.StackPushCount = 0
