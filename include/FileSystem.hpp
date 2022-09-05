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

#ifndef SIMPLEX_FILESYSTEM_HPP
#define SIMPLEX_FILESYSTEM_HPP

#include "string.hpp"
#include "Array.hpp"

#include "FormattingDecorations.hpp"

namespace simplex
{
    namespace FileSystem
    {
        extern string PathSeparator;
        void CopyFile(in const string& filePath, in const string& newFilePath);
        void CreateDirectory(in const string& fullPath);
        void DeleteDirectory(in const string& filePath);
        void DeleteFile(in const string& filePath);
        bool Exists(in const string &path);
        Array<string> GetDirectories(in const string& fullPath);
        string GetExtension(in const string& fullPath);
        string GetFileName(in string fullPath);
        string GetFileNameWithoutExtension(in string fullPath);
        string GetFilePath(in string fullPath);
        string GetFilePathUpOneLevel(in string fullPath);
        Array<string> GetFiles(in const string& fullPath);
        bool IsDirectory(in string fullPath);
        void MoveFile(in const string& oldFilePath, in const string& newFilePath);
        void RenameFile(in const string& oldFilePath, in const string& newFilePath);
    }
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_FILESYSTEM_HPP