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

#include "FileWriter.hpp"
#include "Exception.hpp"
#include "string.hpp"
#include "stdio.h"

#define __class__ "simplex::FileWriter"

namespace simplex
{
    FileWriter::FileWriter(const string& filePath) : filePath{filePath}
    {
        string fopenMode = "wb";

        if(!(file = fopen(filePath.toCString(), fopenMode.toCString())))
            throw Exception{"Unable to open file: "+filePath, __ExceptionParams__};
    }

    FileWriter::~FileWriter()
    {
        fclose(file);
    }

    void FileWriter::writeLine(const string& toWrite)
    {
        write(toWrite+"\n");
    }

    void FileWriter::write(const string& toWrite)
    {
        data+=toWrite;
        const char* temp = toWrite.toCString();
        fwrite(temp, sizeof(char), toWrite.length(), file);
    }

    void FileWriter::writeType(void* value, size_t typeSize)
    {
        NotImplementedException(__ExceptionParams__);
    }
}

#undef __class__