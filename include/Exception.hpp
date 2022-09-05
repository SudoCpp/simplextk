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

/* Required Source Files:
* Exception.cpp
*/

#ifndef SIMPLEX_EXCEPTION_HPP
#define SIMPLEX_EXCEPTION_HPP

#include <exception>
#include "string.hpp"

#include "FormattingDecorations.hpp"

#define __ExceptionParams__ __FILE__, __LINE__, __class__, __func__

namespace simplex
{
    class Exception : public object, public ::std::exception
	{
    protected:
        mutable string whatMessage;

	public:
		string exceptionType;
        string message;
        const string fileName;
        const int32_t lineNumber;
        const string className;
        const string methodName;
    protected:
        const string text;

    public:
        Exception(in const string text, in const char* fileName, in const int32_t lineNumber, in const char* className, in const char* methodName);
        virtual ~Exception() = default;
        virtual const char* what() const throw ();
        string toString() const noexcept;
	};

	class IndexOutOfBoundsException : public Exception
	{
		public:
            IndexOutOfBoundsException(in const string text, in const char* fileName, in const int32_t lineNumber, in const char* className, in const char* methodName);
            virtual ~IndexOutOfBoundsException() = default;
	};

	class NotImplementedException : public Exception
	{
		public:
            NotImplementedException(in const char* fileName, in const int32_t lineNumber, in const char* className, in const char* methodName);
            virtual ~NotImplementedException() = default;
	};

	class NullException : public Exception
	{
		public:
            NullException(in const string text, in const char* fileName, in const int32_t lineNumber, in const char* className, in const char* methodName);
            virtual ~NullException() = default;
	};
}

#include "EndFormattingDecorations.hpp"

#endif // SIMPLEX_EXCEPTION_HPP
