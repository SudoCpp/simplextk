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

#include <filesystem>

#define __class__ "simplex::FileSystem"

namespace simplex::FileSystem
{
    #if defined(__WIN32__) || defined(__WIN32) || defined(WIN32)
        string PathSeparator = "\\";
    #else
        string PathSeparator = "/";
    #endif

    class FileMemoryManager
    {
        public:
            FILE* filePtr;
            FileMemoryManager(FILE* filePtr) 
            : filePtr{filePtr} 
            {}
            ~FileMemoryManager()
            { 
                fclose(filePtr);
            }
    };

    bool Exists(const string &path)
    {
        return std::filesystem::exists(path.toStdString());
    }

    void CopyFile(const string& filePath, const string& newFilePath)
    {
        std::filesystem::copy_file(filePath.toStdString(), newFilePath.toStdString());
    }

    void CreateDirectory(const string& fullPath)
    {
        std::filesystem::create_directory(fullPath.toStdString());
    }

    void DeleteDirectory(const string& filePath)
    {
        std::filesystem::remove(filePath.toStdString());
    }

    void DeleteFile(const string& filePath)
    {
        std::filesystem::remove(filePath.toStdString());
    }

    Array<string> GetDirectories(const string& fullPath)
    {
        Array<string> directories{};
        for (const auto & entry : std::filesystem::directory_iterator(fullPath.toStdString()))
            if(std::filesystem::is_directory(entry.path()))
                directories.add(entry.path().c_str());
        return directories;
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

    string GetFilePath(string fullPath)
    {
        fullPath = fullPath.replace("\\", "/");
        int32_t position = fullPath.lastIndexOf("/");
        if (position == -1)
            throw Exception{"Invalid Path: " + fullPath, __ExceptionParams__};
        return fullPath.subString(0, position + 1);
    }

    string GetFilePathUpOneLevel(string fullPath)
    {
        fullPath = GetFilePath(fullPath);
        fullPath = fullPath.subString(0, fullPath.length() - 1);
        int32_t position = fullPath.lastIndexOf("/");
        if (position == -1)
            throw Exception{"Invalid Path: " + fullPath, __ExceptionParams__};
        return fullPath.subString(0, position + 1);
    }

    Array<string> GetFiles(const string& fullPath)
    {
        Array<string> files{};
        for (const auto & entry : std::filesystem::directory_iterator(fullPath.toStdString()))
            if(!std::filesystem::is_directory(entry.path()))
                files.add(entry.path().c_str());
        return files;
    }

    bool IsDirectory(string fullPath)
    {
        return std::filesystem::is_directory(fullPath.toStdString());
    }

    void MoveFile(const string& oldFilePath, const string& newFilePath)
    {
        std::filesystem::rename(oldFilePath.toStdString(), newFilePath.toStdString());
    }

    void RenameFile(const string& oldFilePath, const string& newFilePath)
    {
        std::filesystem::rename(oldFilePath.toStdString(), newFilePath.toStdString());
    }
}

#undef __class__