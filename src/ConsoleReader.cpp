/*
    BSD 3-Clause License
    
    Copyright (c) 2022, SudoCpp
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

#include "ConsoleReader.hpp"
#include "Exception.hpp"
#include "string.hpp"
#include <string>
#include <iostream>
#include <iomanip>

#define __class__ "simplex::ConsoleReader"

namespace simplex
{
    bool ConsoleReader::readString(string& str, uint32_t numberOfCharacters)
    {
        buffer << std::cin.rdbuf();
        ::std::string temp;
        buffer >> std::setw(numberOfCharacters) >> temp;
        str = string(temp);
        return true;
    }

    bool ConsoleReader::readType(void* value, size_t typeSize)
    {
        string line{};
        if(!readLine(line))
            return false;
        if (typeSize != line.length())
            return false;
        else
        {
            memcpy(value, line.toCString(), typeSize);
            return true;
        }
    }

    bool ConsoleReader::readLine(string &str)
    {
        buffer << std::cin.rdbuf();
        ::std::string temp;
        if(!::std::getline (buffer, temp))
            return false;
        str = string(temp);
        return true;
    }

    void ConsoleReader::rewind(uint32_t numberOfCharacters)
    {
        int32_t currentPosition = buffer.tellg();
        int32_t newPosition = (currentPosition - numberOfCharacters < 0)? 0 : currentPosition - numberOfCharacters;
        buffer.seekg(newPosition);
    }

    void ConsoleReader::rewind()
    {
        buffer.seekg(0);
    }
}

#undef __class__