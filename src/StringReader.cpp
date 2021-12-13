/*
    BSD 3-Clause License
    
    Copyright (c) 2021, SudoCpp
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "StringReader.hpp"
#include "Exception.hpp"
#include "string.hpp"

#define __class__ "simplex::StringReader"

namespace simplex
{
    StringReader::StringReader(const string& data) : data{data}, position{0} {}

    bool StringReader::read(unsigned int numberOfCharacters, string& readTo) const
    {
        if(data.length() >= position + numberOfCharacters)
        {
            readTo = data.subString(position, position + numberOfCharacters);
            position += numberOfCharacters;
            return true;
        }
        return false;
    }

    string StringReader::readLine() const
    {
        string newStr = "";
        string character = "";
        while(read(1, character) && character != "\n")
            newStr += character;
        if(character == "\n")
        {
            read(1, character);
            if(character == "\r")
                newStr += character;
            else
                rewind(1);
        }

        return newStr;
    }

    void StringReader::rewind(unsigned int numberOfCharacters) const
    {
        if(position >= numberOfCharacters)
            position -= numberOfCharacters;
    }

    void StringReader::rewind() const
    {
        position = 0;
    }
}

#undef __class__