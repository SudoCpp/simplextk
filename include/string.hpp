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

#ifndef SIMPLEX_STRING_HPP
#define SIMPLEX_STRING_HPP

#include <string>
#include "object.hpp"

namespace simplex
{
	template<typename ArrayMemberType> class Array;
    
    class string : public object
	{
		::std::string data;

	public:
		//Constructors
        string();
        string(const char* str);
        string(const ::std::string& str);
        string(const ::std::string* str);
        string(const char* character, uint32_t repetition);
        string(const char& character, uint32_t repetition);
        string(const string& str);
        string(const string* str);
        virtual ~string() = default;

        static string FromNumber(int8_t number);
        static string FromNumber(int16_t number);
        static string FromNumber(int32_t number);
        static string FromNumber(int64_t number);
        static string FromNumber(uint8_t number);
        static string FromNumber(uint16_t number);
        static string FromNumber(uint32_t number);
        static string FromNumber(uint64_t number);
        static string FromNumber(float number, const int32_t precision);
        static string FromNumber(double number, const int32_t precision);
        static string FromNumber(long double number, const int32_t precision);

        template<typename NumberType>
        NumberType toNumber() const;

        //Modified Strings
        string toLower() const noexcept;
        string toUpper() const noexcept;

        //Operators
        friend string operator+(const string& leftHandSide, const string& rightHandSide);
        friend bool operator==(const string& leftHandSide, const string& rightHandSide);
        friend bool operator!=(const string& leftHandSide, const string& rightHandSide);
        string& operator+=(const string& rightHandSide);
        string& operator=(const string& rightHandSide);

        //Outputs
        ::std::string toStdString() const noexcept;
        const char* toCString() const noexcept;
        int32_t length() const noexcept;
        int32_t indexOf(const string& subString) const noexcept;
        int32_t indexOf(const string& subString, int32_t offset) const noexcept;
        int32_t lastIndexOf(const string& subString) const noexcept;
        int32_t indexOf(const char character) const noexcept;
        int32_t indexOf(const char character, int32_t offset) const noexcept;
        int32_t lastIndexOf(const char character) const noexcept;
        bool contains(const string& subString) const noexcept;
        int32_t containsCount(const string& subString) const noexcept;
        string replace(const string& find, const string& replace) noexcept;
        Array<string> split(const char characterToSplit) const noexcept;
        string subString(uint32_t start) const;
        string subString(uint32_t start, uint32_t lengthOfSub) const;
        string trim() const noexcept;
        string trimBeginning() const noexcept;
        string trimEnd() const noexcept;

        virtual size_t getHash() const noexcept;
    };
}

template<> struct std::hash<simplex::string>
{
    size_t operator()(const simplex::string& str) const noexcept
    {
        return str.getHash();
    }
};

#endif //SIMPLEX_STRING_HPP
