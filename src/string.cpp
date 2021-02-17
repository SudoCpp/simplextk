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

#include "string.hpp"
#include <locale>

namespace simplex
{
    string::string() : data{""} {}

    string::string(const char* str) : data{str} {}

    string::string(::std::string str) : data{str} {}

    string::string(const char& character, unsigned int repetition)
    {
        data = "";
        for (int loop = 0; loop < repetition; loop++)
            data += character;
    }

    string operator+(const string& leftHandSide, const string& rightHandSide)
    {
        return string(leftHandSide.data + rightHandSide.data);
    }

    bool operator==(const string& leftHandSide, const string& rightHandSide)
    {
        return leftHandSide.toStdString() == rightHandSide.toStdString();
    }

    bool operator!=(const string& leftHandSide, const string& rightHandSide)
    {
        return leftHandSide.toStdString() != rightHandSide.toStdString();
    }

    string& string::operator+=(const string& rightHandSide)
    {
        this->data += rightHandSide.data;
        return *this;
    }

    string& string::operator=(const string& rightHandSide)
    {
        this->data = rightHandSide.data;
        return *this;
    }

    string string::FromNumber(int number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(char number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(float number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(long number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(long long number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(unsigned long number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(unsigned long long number)
    {
        return string{std::to_string(number)};
    }
    
    string string::FromNumber(double number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(long double number)
    {
        return string{std::to_string(number)};
    }

    string string::toLower() const noexcept
    {
        ::std::string temp = data;
        for (auto& ch : temp)
            ch = ::std::tolower(ch);
        return string{temp};
    }

    string string::toUpper() const noexcept
    {
        ::std::string temp = data;
        for (auto& ch : temp)
            ch = ::std::toupper(ch);
        return string{temp};
    }

    ::std::string string::toStdString() const noexcept
    {
        return ::std::string(data);
    }

    const char* string::toCString() const noexcept
    {
        return data.c_str();
    }

    int string::length() const noexcept
    {
        return data.length();
    }

    int string::indexOf(const string& subString) const noexcept
    {
        size_t location = data.find(subString.data);
        if (location != std::string::npos)
            return (int)location;
        else
            return -1;
    }

    int string::indexOf(const string& subString, int offset) const noexcept
    {
        size_t location = data.find(subString.data, offset);
        if (location != std::string::npos)
            return (int)location;
        else
            return -1;
    }

    int string::lastIndexOf(const string& subString) const noexcept
    {
        int location = (int)data.find_last_of(subString.data);
        location -= subString.length() - 1;
        if (location != std::string::npos)
            return location;
        else
            return -1;
    }

    int string::indexOf(const char character) const noexcept
    {
        size_t location = data.find(character);
        if (location != std::string::npos)
            return (int)location;
        else
            return -1;
    }

    int string::indexOf(const char character, int offset) const noexcept
    {
        size_t location = data.find(character, offset);
        if (location != std::string::npos)
            return (int)location;
        else
            return -1;
    }

    int string::lastIndexOf(const char character) const noexcept
    {
        size_t location = data.find_last_of(character);
        if (location != std::string::npos)
            return (int)location;
        else
            return -1;
    }
    
    bool string::contains(const string& subString) const noexcept
    {
        if (data.find(subString.toStdString()) != ::std::string::npos)
            return true;
        else
            return false;
    }

    int string::containsCount(const string& subString) const noexcept
    {
        int count = 0;
        int nPos = data.find(subString.toStdString(), 0);
        while (nPos != -1)
        {
            count++;
            nPos = data.find(subString.toStdString(), nPos + 1);
        }
        return count;
    }

    string string::replace(const string& find, const string& replace)
    {
        //Try to use std::string logic so that if the c++ library improves, it will improve here also
        std::string duplicate{data};
        std::string stdFind = find.toStdString();
        std::string stdReplace = replace.toStdString();
        size_t position = 0;
        while ((position = duplicate.find(stdFind, position)) != std::string::npos) 
        {
            duplicate.replace(position, find.length(), stdReplace);
            position += replace.length();
        }

        return string{duplicate};
    }

    string string::subString(unsigned int start) const
    {
        if (start < 0)
            start = length() + start;

        if (start <= (unsigned int)length())
            return string{data.substr(start)};
        return string{};
    }

    string string::subString(unsigned int start, unsigned int lengthOfSub) const
    {
        if (start < 0)
            start = length() + start;

        if (lengthOfSub < 0)
        {
            if (-lengthOfSub <= length() - start)
                return string{data.substr(start, length() - start + lengthOfSub)};
        }
        else if (start + lengthOfSub <= length())
            return string{data.substr(start, lengthOfSub)};
        
        return string{};
    }

    string string::trim() const noexcept
    {
        return trimBeginning().trimEnd();
    }
    string string::trimBeginning() const noexcept
    {
        std::string copy{data};
        copy.erase(0, copy.find_first_not_of(" \t\n\r\f\v"));
        return string{copy};
    }
    string string::trimEnd() const noexcept
    {
        std::string copy{data};
        copy.erase(copy.find_last_not_of(" \t\n\r\f\v")+1);
        return string{copy};
    }
}
