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

#include "string.hpp"
#include "Exception.hpp"
#include <locale>
#include "Array.hpp"
#include <sstream>

#define __class__ "simplex::string"

namespace simplex
{
    string::string() : data{""} {}

    string::string(const char* str) : data{std::string{str}} {}
    string::string(const ::std::string& str): data{std::string{str}} {}
    string::string(const ::std::string* str): data{std::string{*str}} {}
    string::string(const char* character, unsigned int repetition) : data{""}
    {
        for (int loop = 0; loop < repetition; loop++)
            data += character;
    }
    string::string(const char& character, unsigned int repetition) : data{""}
    {
        for (int loop = 0; loop < repetition; loop++)
            data += character;
    }
    string::string(const string& str) : data{std::string{str.data}} {}
    string::string(const string* str) : data{std::string{str->data}} {}

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

    string string::FromNumber(int8_t number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(int16_t number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(int32_t number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(int64_t number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(uint8_t number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(uint16_t number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(uint32_t number)
    {
        return string{std::to_string(number)};
    }

    string string::FromNumber(uint64_t number)
    {
        return string{std::to_string(number)};
    }
    
    string string::FromNumber(float number, const int precision)
    {
        std::ostringstream temp;
        temp.precision(precision);
        temp << std::fixed << number;
        return string{temp.str()};
    }

    string string::FromNumber(double number, const int precision)
    {
        std::ostringstream temp;
        temp.precision(precision);
        temp << std::fixed << number;
        return string{temp.str()};
    }

    string string::FromNumber(long double number, const int precision)
    {
        std::ostringstream temp;
        temp.precision(precision);
        temp << std::fixed << number;
        return string{temp.str()};
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

    string string::replace(const string& find, const string& replace) noexcept
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

    Array<string> string::split(const char characterToSplit) const noexcept
    {
        Array<string> temp{};
        int previousLocation = 0;
        int location = 0;
        do
        {
            previousLocation = location;
            location = indexOf(characterToSplit, location);
            if(location != -1)
                temp.add(subString((unsigned int)previousLocation, (unsigned int)location));
            else
                temp.add(subString(previousLocation));
        } while (location != -1);

        return temp;
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
        
        throw IndexOutOfBoundsException{"String length is less than substring length requested.", __ExceptionParams__};
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

    size_t string::getHash() const noexcept
    {
        return std::hash<std::string>()(data);
    }

    template<>
    float string::toNumber<float>() const
    {
        try
        {
            return std::stof(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    double string::toNumber<double>() const
    {
        try
        {
            return std::stod(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    long double string::toNumber<long double>() const
    {
        try
        {
            return std::stold(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    uint8_t string::toNumber<uint8_t>() const
    {
        try
        {
            return (uint8_t)std::stoul(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    uint16_t string::toNumber<uint16_t>() const
    {
        try
        {
            return (uint16_t)std::stoul(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    uint32_t string::toNumber<uint32_t>() const
    {
        try
        {
            return (uint32_t)std::stoul(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    uint64_t string::toNumber<uint64_t>() const
    {
        try
        {
            return (uint64_t)std::stoull(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    int8_t string::toNumber<int8_t>() const
    {
        try
        {
            return (int8_t)std::stoi(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    int16_t string::toNumber<int16_t>() const
    {
        try
        {
            return (int16_t)std::stoi(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    int32_t string::toNumber<int32_t>() const
    {
        try
        {
            return (int32_t)std::stol(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }

    template<>
    int64_t string::toNumber<int64_t>() const
    {
        try
        {
            return (int64_t)std::stoll(data);
        }
        catch(std::exception ex)
        {
            throw Exception(ex.what(), __ExceptionParams__);
        }
    }
}

#undef __class__
