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

#ifndef SIMPLEX_CFILEWRAPPER_HPP
#define SIMPLEX_CFILEWRAPPER_HPP

#include "object.hpp"
#include "string.hpp"
#include "Exception.hpp"
#include <stdio.h>

#define __class__ "simplex::CFileWrapper"

namespace simplex
{
    enum class FileMode { ReadMode, WriteMode };
    
    class CFileWrapper
    {
        FILE* file;
        bool fileIsOpen;
        bool fileIsBinary;
        bool fileIsReadMode;
        string filePath;
        mutable char buffer[1023]; //It's a buffer even if instance is const this can change `mutable`

    public:

        CFileWrapper();
        CFileWrapper(const string& filePath, const FileMode& mode, bool isBinary);
        virtual ~CFileWrapper();
        CFileWrapper(const CFileWrapper&) = default;

        void openFile(const string& filePath, const FileMode& mode, bool isBinary);

        template<typename returnType>
        returnType read(size_t sizeOfRead) const
        {
            throw NotImplementedException{__ExceptionParams__};
        }
        string readString(int lengthOfString) const;
        string readLine() const;

        template<typename type>
        void write(type addressOfValue, size_t sizeOfWriteInBytes)
        {
            fwrite(addressOfValue, sizeof(char), sizeOfWriteInBytes, file);
        }
        
        void writeString(const string& String);
        void writeLine(const string& line);

        void seek(int characters) const;
        void rewind() const;
    };
}

#undef __class__

#endif // SIMPLEX_CFILEWRAPPER_HPP
