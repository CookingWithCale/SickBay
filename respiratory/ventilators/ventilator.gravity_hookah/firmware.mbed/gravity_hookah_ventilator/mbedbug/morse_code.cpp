/* mbedBug @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /morse_code.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#include "morse_code.h"
namespace mbedbug {
const char* SMorseCode (char code) {
    static const char* space = " "; //<

    static const char* cypher[] = {
        ".-.-.",        //< ASCII: NUL, Morse code: End of message.
        0,              //< ASCII: SOH.
        "-.-.-",        //< ASCII: STX, Morse code: Start copying.
        "-.-..-..",     //< ASCII: ETX, Morse code: Going off the air ("clear").
        "...-.-",       //< ASCII: EOT, Morse code: End of transmission.
        "-.--.",        //< ASCII: ENQ, Morse code: Invite a specific station to transmit.
        "...-.",        //< ASCII: ACK, Morse code: Understood.
        "...---...",    //< ASCII: BEL, Morse code: SOS distress signal.
        "........",     //< ASCII: BS,  Morse code: Prosign error.
        space,          //< ASCII: HT,  Morse code: non-standard space.
        ".-.-",         //< ASCII: LF,  Morse code: New Line
        "-...-",        //< ASCII: VT,  Morse code: New paragraph.
        ".-.-.",        //< ASCII: FF,  Morse code: New Page
        0,              //< ASCII: CR
        "-..---",       //< ASCII: SO,  Morse code: Change to Wabun Mores code.
        ".--...",       //< ASCII: SI,  Morse code: Non-standard return to Western Mores code
        0,              //< ASCII: DLE
        0,              //< ASCII: DC1
        0,              //< ASCII: DC2
        0,              //< ASCII: DC3
        0,              //< ASCII: DC4
        0,              //< ASCII: NAK
        ".-...",        //< ASCII: SYN, Morse code: AS, Wait.
        0,              //< ASCII: ETB
        0,              //< ASCII: CAN
        "-...-.-",      //< ASCII: EM,  Morse code: Break/BRB.
        0,              //< ASCII: SUB
        0,              //< ASCII: ESC
        0,              //< ASCII: FS
        0,              //< ASCII: GS
        0,              //< ASCII: RS
        0,              //< ASCII: US
        space,          //< ASCII: ' '
        ".-..-.",       //< ASCII: '!'
        ".-..-.",       //< ASCII: '\"'
        0,              //< ASCII: '#'
        "..._.-..",     //< ASCII: '$'
        "....._..",     //< ASCII: '%'
        "._...",        //< ASCII: '&'
        ".----.",       //< ASCII: '\''
        "-.--.-",       //< ASCII: '('
        ".-..-.",       //< ASCII: ')', Nonstandard, inverse of '('
        0,              //< ASCII: '*'
        0,              //< ASCII: '+'
        "--..--",       //< ASCII: ','
        "-....-",       //< ASCII: '-'
        ".-.-.-",       //< ASCII: '.'
        "-..-.",        //< ASCII: '/'
        "-----",        //< ASCII: '0'
        ".---",         //< ASCII: '1'
        "..---",        //< ASCII: '2'
        "...--",        //< ASCII: '3'
        "....-",        //< ASCII: '4'
        ".....",        //< ASCII: '5'
        "-...",         //< ASCII: '6'
        "--...",        //< ASCII: '7'
        "---..",        //< ASCII: '8'
        "----.",        //< ASCII: '9'
        "---...",       //< ASCII: ':'
        0,              //< ASCII: ','
        0,              //< ASCII: '<'
        "-...-",        //< ASCII: '='
        0,              //< ASCII: '>'
        "..--..",       //< ASCII: '?'
        ".--.-.",       //< ASCII: '@'
        ".-",           //< ASCII: 'A'
        "-...",         //< ASCII: 'B'
        "-.-.",         //< ASCII: 'C'
        "-..",          //< ASCII: 'D'
        ".",            //< ASCII: 'E'
        "..-.",         //< ASCII: 'F'
        "--.",          //< ASCII: 'G'
        "....",         //< ASCII: 'H'
        "..",           //< ASCII: 'I'
        ".---",         //< ASCII: 'J'
        "-.-",          //< ASCII: 'K'
        ".-..",         //< ASCII: 'L'
        "--",           //< ASCII: 'M'
        "-.",           //< ASCII: 'N'
        "---",          //< ASCII: 'O'
        ".--.",         //< ASCII: 'P'
        "--.-",         //< ASCII: 'Q'
        ".-.",          //< ASCII: 'R'
        "...",          //< ASCII: 'S'
        "-",            //< ASCII: 'T'
        "..-",          //< ASCII: 'U'
        "...-",         //< ASCII: 'V'
        ".--",          //< ASCII: 'W'
        "-..-",         //< ASCII: 'X'
        "-.--",         //< ASCII: 'Y'
        "--.."          //< ASCII: 'Z'
    };

    ///if (code < 0) return 0;  //< Uncomment if your compiler uses signed char.
    if (code >= 'a' && code <= 'z') code -= 'a' - 'A';   //< Covert from lowercase to upper case if need be.
    if (code > 'Z')
    {
        switch (code)
        {
          case -4: return ".-.-";   //< 132
          case -5: return ".--.-";  //< 133
          case -6: return ".--.-";  //< 134
          case -16: return "..-.."; //< 144
          case -37: return "--.--"; //< 165
          case -25: return "---.";  //< 153
          case -26: return "..--";  //< 154
          default:  return 0;
        }
    }
    return cypher[code];
}

}   //< namespace mbedbug
