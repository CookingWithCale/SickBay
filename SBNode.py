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
from Stringf import Stringf
  
# A SickBay tree node with a unique Node ID (NID).
# Example
# ```Script2
# ><.Intake CaptainKabuki Name="Cale McCollough" DoB="4/1/2020"
# ><.DoB.Set "3/31/2020" <
# ><.Foo 1.234
# ><.Print
# ><.PrintStats
# ><.PrintDetails
# ```
class SBNode:

  def __init__(self, SickBay, Type = "", TID = 0, Command = ""):
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
    self.Functions = {}            #< Callable Crabs functions.
    SickBay.Push(self, Command)

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
  
  # Adds a Key-Value pair to the Children or Meta
  def Add(self, Key, Value):
    if Value == None:
      return
    if isinstance(Value, SBNode):
      self.Children[Key] = Value
    else:
      self.Meta[Key] = Value
  
  # Adds a Key-Value pair to the Children or Meta
  def AddPop(self, SickBay, Key, Value):
    self.Add(Key, Value)
    SickBay.Pop()
    
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
  
  def PrintStats(self, String = "", SelfKey = None):
    print ("\nPrinting Stats")
    if SelfKey != None:
      String += SelfKey + " "
    for Key, Value in self.Children.iteritems() :
      Value.PrintStats(String, Key)
    return String
  
  def PrintDetails(self, String = "", Indent = 0, SelfKey = None):
    String += Stringf.Indent(Indent, "> ") + ".Details"
    if SelfKey != None:
      String += SelfKey
    for Key, Value in self.Children.iteritems() :
      Value.PrintDetails(String, Indent + 1, Key)
    return String
  
  # Prints a human-readable help string.
  def PrintHelp(self, String = "", Indent = 0, SelfKey = None):
    String += Stringf.Indent(Indent, "> ") + SelfKey + ".Help" + \
              Stringf.Indent(Indent + 1, "") + self.Meta["Help"]
    for Child in self.Children:
      Child.PrintHelp(String, SelfKey, Indent + 1)
  
  # Prints the List() to the COut
  def Print(self, Indent = 0):
    Stringf.COut(self.List())
  
  # Gets this node's Key.
  def Key(self):
    if self == self.Parent:
      return "><"
    for Key, Value in self.Children.iteritems():
      if (Value == self):
        return Key
    return ""
  
  # Gets the Path.
  def Path(self, Result = ""):
    if (self.Parent == self):
      Key = "SickBay"
    else:
      Key = self.Key()
    return Result + Key + "."
  
  # Gets the length of the path from the root.
  def PathLength(self, Length = 0):
    if(self == self.Partent):
      return Length
    return self.PathLength(Length + 1)
  
  # Sets
  def MetaSet(self, Key, Value):
    self.Parent.Meta[Key] = Value

  def Path(self, Path = ""):
    Parent = self.Parent
    if self != Parent:
      return Parent.Path(Path)
    return Path + self.Key() + "."
  
  # Returns a string with all of the Keys in the Meta and Children.
  def ListMeta(self, Indent = 0):
    Result = ""
    Index = len(self.Children)
    for Key, Value in self.Meta.iteritems():
      Index += 1
      String = str(Index) + ". " + Key + ":" + Value.__class__.__name__
      Result += Stringf.Indent(Indent, String)
    return Result
  
  # Returns a string with all of the Keys in the Meta and Children.
  def ListChildren(self, Indent = 0):
    Index = 0
    Result = ""
    for Key, Value in self.Children.iteritems():
      Index += 1
      String = str(Index) + ". " + Key + ":" + Value.__class__.__name__
      Result += Stringf.Indent(Indent, String)
    return Result
  
  # Returns a string with all of the Keys in the Meta and Children.
  def List(self, Indent = 0):
    String = Stringf.Indent(Indent, "> " + self.Key())
    String += self.ListChildren(Indent + 1)
    String += Stringf.Indent(Indent + 1, "> Meta")
    String += self.ListMeta (Indent + 2)
    String +=  Stringf.Indent(Indent + 1, "<")
    String += Stringf.Indent(Indent, "<")
    return String

  # Parses the string as either int, float, str, or None.
  def CommandParseValue(self, Args):
    try: 
      return int(Args)
    except ValueError:
      pass
    try: 
      return float(Args) # float(re.search('\d+\.*\d*', r).group(0))
    except ValueError:
      pass
    Commands = Args.split("\"", 2)
    if (len(Commands) == 3):
      return Commands[1]
    return None
  
  # Initializes the Meta using a sequence of XML-style duck-typed setters.
  # Example: Name="John Doe" Foo="Bar" FooBar=4.20
  def Commands(self, Args):
    Loop = True
    while Loop:
      Args = Args.split("=", 1)
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
      Args = Args.split(" ", 1)
      String = Args[0]
      Item = CommandParseValue(Args)
      Args = Args[1]
      if (len(Args[1]) == 0):
        Loop = False
  
  def CommandKeyNext(self, SickBay, Args):
    Tokens = Args.split(".", 1)
    if Tokens[0] in self.Children: return Tokens
    return None

  # The number of Meta plus the number of children.
  def MemberCount(self):
    return len(self.Meta) + len(self.Children)

  # Runs the common commands and returns None if no commands were executed.
  def CommandSuper(self, SickBay, Command):
    if Command == None: return ""
    if Command == "":
      return SickBay.Pop()
    if Command[0] == ".":
      self.CommandPushCount = 0
      Command = Command[1:]
    if Command == "!":
      return self.PrintStats()
    if Command == "|":
      return self.PrintDetails()
    if Command == "list":
      return self.List()
    if Command == "list meta":
      return self.List()
    if Command == "?":
      return self.PrintHelp()
    try: 
      Index = int(Command)
      if Index < 0:
        return SickBay.Push(SickBay.FindNID(Index * -1))
      ChildCount = self.ChildCount()
      if Index < ChildCount:
        Key = self.Children.keys()[Index]
        return SickBay.Push(self.Children[Key])
      # else the index was of a self.Member
      return "ERROR: You can't push metadata onto the Crabs stack. Use the "\
             "index 0 for the SickBay, and 1 through N for the Children."
    except ValueError:
      pass
    # Else there are some Keys and Values and the Keys might be hierarchial

    # Push items on the stack, creating them if they don't exist
    Tokens = Command.split(" ", 1)
    Key = Tokens[0]
    if Key in self.Children:
      return self.Push(SickBay, Tokens[1])
    # Else it's hierarchial
    Pushing = True
    while Pushing:
      if len(Tokens) == 1:
        Pushing = False
      else:
        Tokens = Command.split(".", 1)
        Key = Tokens[0]
        if Key in self.Children:
          SickBay.Push(self.Children[Key])
        elif Key in self.Meta:
            return "> Error The Key:\"" + Key + " is a Metadata value and is not hierarchial. <"
    return self.Top.Command(SickBay, Command)
  
  # Issues a Console command to this node.
  # ><.Intake.Add Foo="" Name="Harry" Description=""
  def Command(self, SickBay, Args):
    Result = self.CommandSuper(SickBay, Args)
    if Result != None:
      return Result
    # At this point we can't push anymore Nodes on to the Crabs Stack.
    Tokens = Args.split(" ", 1)
    Args = Tokens[1]
    Key = Tokens[0]
    TokensLength = len(Tokens)
    if TokensLength == 1:
      return "ERROR: Key, Index, or NID does not exist."
    Tokens = Key.split(".", 1)
    if len(Tokens) > 1:
      return self.Commands(SickBay, Tokens[1])
    if Key == "set":
      Tokens = Tokens[1].split(" ", 1)
      Key = Tokens[0]
      if (len(Tokens) == 1):
        return "ERROR: You have to have to type \"add Key Value\"."
      self.Add(Key, self.CommandParseValue(Args))
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
