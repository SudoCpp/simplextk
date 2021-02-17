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

/* Required Source Files:
* Exception.cpp
*/

#ifndef SIMPLEX_EXCEPTION_HPP
#define SIMPLEX_EXCEPTION_HPP

#include <exception>
#include "string.hpp"

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
        const int lineNumber;
        const string className;
        const string methodName;
    protected:
        const string text;

    public:
        Exception(const string text, const char* fileName, const int lineNumber, const char* className, const char* methodName);
        virtual ~Exception() = default;
        virtual const char* what() const throw ();
        string toString() const noexcept;
	};

	class IndexOutOfBoundsException : public Exception
	{
		public:
            IndexOutOfBoundsException(const string text, const char* fileName, const int lineNumber, const char* className, const char* methodName);
	};

	class NotImplementedException : public Exception
	{
		public:
            NotImplementedException(const char* fileName, const int lineNumber, const char* className, const char* methodName);
	};

	class NullException : public Exception
	{
		public:
            NullException(const string text, const char* fileName, const int lineNumber, const char* className, const char* methodName);
	};
}

#endif // SIMPLEX_EXCEPTION_HPP
