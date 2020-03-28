/* mbedBug @version 0.x
@link    https://github.com/KabukiStarship/mbedbug.git
@file    /error_list.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright 2016-20 (C) Kabuki Starship <kabukistarship.com>; all rights 
reserved (R). This Source Code Form is subject to the terms of the Mozilla 
Public License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <mbedbug_config.h>
namespace mbedBug {

/* An array of error strings.
@code
ErrorList<5> errors;

@endcode
*/
template<unsigned int cErrorCountMax>
class ErrorList {
  public:

    /* Default simple constructor. */
    ErrorList ()
    :   error_count (0) {
        /// Nothing to do here! :-)
    }

    /* Clears the error list. */
    void Clears () { error_count = 0; }

    /* Gets the number of errors. */
    unsigned int GetNumErrors () { return error_count; }

    /* Reports an error with the given message. */
    void Report (const char* Error) {
        if (error_count >= cErrorCountMax) return;
        errors[error_count++] = Error;
        return this;
    }

    /* Reports an error with the given message. */
    ErrorList& operator += (const char* Error) {
        Report (Error);
        return this;
    }

    virtual void Print () {
        for (int i = 0; i < error_count; ++i)
            printf ("\r\n%s", errors[i]);
    }

    /* Returns the list of errors. */
    const char* GetErrors () { return errors; }

  private:

    unsigned int error_count;

    const char* errors[cErrorCountMax];
};

}   //< namespace mbedBug {
