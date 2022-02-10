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

#include "FileSystem.hpp"
#include "Exception.hpp"

#include <sys/types.h>
#include <sys/stat.h>

#define __class__ "simplex::FileSystem"

namespace simplex::FileSystem
{
    #if defined(__WIN32__) || defined(__WIN32) || defined(WIN32)
        string PathSeparator = "\\";
    #else
        string PathSeparator = "/";
    #endif

    bool Exists(const string &path)
    {
        struct stat info;

        if (stat(path.toCString(), &info) != 0)
            return false;
        else if (info.st_mode & S_IFDIR)
            return true;
        else
            return false;
    }

    string GetExtension(const string &fullPath)
    {
        int32_t position = fullPath.lastIndexOf(".");
        if (position == -1)
            throw Exception{"Invalid Path: " + fullPath, __ExceptionParams__};
        return fullPath.subString(position);
    }

    string GetFileName(string fullPath)
    {
        fullPath = fullPath.replace("\\", "/");
        int32_t position = fullPath.lastIndexOf("/");
        if (position == -1)
            throw Exception{"Invalid Path: " + fullPath, __ExceptionParams__};
        return fullPath.subString(position + 1);
    }

    string GetFileNameWithoutExtension(string fullPath)
    {
        fullPath = GetFileName(fullPath);
        if (fullPath.indexOf(".") != -1)
            return fullPath.subString(0, fullPath.indexOf("."));
        else
            return fullPath;
    }
}

#undef __class__