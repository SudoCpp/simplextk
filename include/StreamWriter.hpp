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

#ifndef SIMPLEX_STREAMWRITER_HPP
#define SIMPLEX_STREAMWRITER_HPP

#include "object.hpp"
#include "string.hpp"
#include <string.h>
#include "Array.hpp"

#include "FormattingDecorations.hpp"

namespace simplex
{
    class StreamWriter : public object
	{
        protected:
            string data;
        
		public:
			virtual void writeLine(in const string& toWrite)
            {
                write(toWrite + "\n");
            }
			virtual void write(in const string& toWrite) = 0;
			// Not a template to force method to children.
            // void* will accept any type of pointer.
            virtual void writeType(in void* value, in size_t typeSize) = 0;
            virtual void writeAllLines(in const Array<string>& lines)
            {
                for(string line : lines)
                    writeLine(line);
            }
            virtual ~StreamWriter() = default;
            virtual void writeBuffer() = 0;
	};
}

#include "EndFormattingDecorations.hpp"

#endif // SIMPLEX_STREAMWRITER_HPP