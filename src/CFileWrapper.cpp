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

#include "CFileWrapper.hpp"

#define __class__ "simplex::CFileWrapper"

namespace simplex
{
    CFileWrapper::CFileWrapper() : fileIsOpen{false} {}

    CFileWrapper::CFileWrapper(const string &filePath, const FileMode& mode, bool isBinary) : fileIsOpen{false}
    {
        openFile(filePath, mode, isBinary);
    }

    CFileWrapper::~CFileWrapper()
    {
        if(fileIsOpen)
            fclose(file);
    }

    void CFileWrapper::openFile(const string &filePath, const FileMode& mode, bool isBinary)
    {
        this->filePath = filePath;

        string fopenMode = "";
        if(mode == FileMode::ReadMode)
        {
            fileIsReadMode = true;
            fopenMode += "r";
        }
        else 
        {
            fileIsReadMode = false;
            fopenMode += "w";
        }

        if(isBinary)
            fopenMode += "b";
        fileIsBinary = isBinary;

        if(file = fopen(filePath.toCString(), fopenMode.toCString()))
            fileIsOpen = true;
        else
            throw Exception{"Unable to open file: "+filePath, __ExceptionParams__};
    }

    string CFileWrapper::readString(int lengthOfString) const
    {
        if(fgets(buffer, lengthOfString, file))
            return string(buffer);
        else
            return "";
    }

    string CFileWrapper::readLine() const
    {
        if(fgets(buffer, 1023, file))
            return string(buffer);
        else
            return "";
    }

    void CFileWrapper::writeString(const string& String)
    {
        const char* temp = String.toCString();
        fwrite(temp, sizeof(char), String.length(), file);
    }

    void CFileWrapper::writeLine(const string& line)
    {
        writeString(line+"\n");
    }

    void CFileWrapper::seek(int characters) const
    {
        fseek(file, characters, SEEK_CUR);
    }

    void CFileWrapper::rewind() const
    {
        ::rewind(file);
    }
}

#undef __class__
