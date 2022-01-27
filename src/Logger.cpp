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

#include "Logger.hpp"
#include "DateTime.hpp"
#include "Exception.hpp"

#define __class__ "simplex::Logger"

namespace simplex
{
    //Create spots in memory for static variables
    Logger* Logger::instance = nullptr;
    LoggerLevel Logger::DisplayLevel;

    //Implementation
    Logger::Logger(StreamWriter* stream, bool takeOnOwnership)
    : debugStream{stream}, infoStream{stream}, warningStream{stream},
    errorStream{stream}, fatalErrorStream{stream}, uniquePointers{false},
    takeOnOwnership{takeOnOwnership}
    {
        loggerRunning = true;
    }

    Logger::Logger(StreamWriter* debugStream, StreamWriter* infoStream, StreamWriter* warningStream, 
    StreamWriter* errorStream, StreamWriter* fatalErrorStream, bool takeOnOwnership)
    : debugStream{debugStream}, infoStream{infoStream}, warningStream{warningStream},
    errorStream{errorStream}, fatalErrorStream{fatalErrorStream}, uniquePointers{true},
    takeOnOwnership{takeOnOwnership}
    {
        loggerRunning = true;
    }

    Logger::~Logger()
    {
        if(takeOnOwnership)
        {
            delete debugStream;
            if(uniquePointers)
            {
                delete infoStream;
                delete warningStream;
                delete errorStream;
                delete fatalErrorStream;
            }
        }
    }

    void Logger::CreateLogger(StreamWriter* debugStream, StreamWriter* infoStream, 
    StreamWriter* warningStream, StreamWriter* errorStream, StreamWriter* fatalErrorStream, 
    LoggerLevel displayLevel)
    {
        if(instance != nullptr)
            delete instance;
        instance = new Logger{debugStream, infoStream, warningStream, errorStream, fatalErrorStream, true};
        DisplayLevel = displayLevel;
    }

    void Logger::CreateLogger(StreamWriter& debugStream, StreamWriter& infoStream, 
    StreamWriter& warningStream, StreamWriter& errorStream, StreamWriter& fatalErrorStream, 
    LoggerLevel displayLevel)
    {
        if(instance != nullptr)
            delete instance;
        instance = new Logger{&debugStream, &infoStream, &warningStream, &errorStream, &fatalErrorStream, false};
        DisplayLevel = displayLevel;
    }

    void Logger::CreateLogger(StreamWriter* stream, LoggerLevel displayLevel)
    {
        if(instance != nullptr)
            delete instance;
        instance = new Logger{stream, true};
        DisplayLevel = displayLevel;
    }

    void Logger::CreateLogger(StreamWriter& stream, LoggerLevel displayLevel)
    {
        if(instance != nullptr)
            delete instance;
        instance = new Logger{&stream, false};
        DisplayLevel = displayLevel;
    }

    string Logger::GetDateTime()
    {
        return string::FromNumber(DateTime::LocalMonth()) + "/" + 
        string::FromNumber(DateTime::LocalDay()) + " " + 
        string::FromNumber(DateTime::Local12Hour()) + ":" + 
        string::FromNumber(DateTime::LocalMinute()) + ":" + 
        string::FromNumber(DateTime::LocalSecond()) + " " + 
        ((DateTime::LocalAmPm() == 0) ? "AM" : "PM");
    }

    void Logger::LogDebug(const string& message)
    {
        if(instance == nullptr)
            throw NullException{"Please run Logger::CreateLogger before Logger::LogDebug", __ExceptionParams__};

        if(DisplayLevel >= LoggerLevel::Debug)
            instance->debugStream->writeLine("DEBUG - " + GetDateTime() + " - " + message);
    }

    void Logger::LogInfo(const string& message)
    {
        if(instance == nullptr)
            throw NullException{"Please run Logger::CreateLogger before Logger::LogInfo", __ExceptionParams__};

        if(DisplayLevel >= LoggerLevel::Info)
            instance->infoStream->writeLine("INFO - " + GetDateTime() + " - " + message);
    }

    void Logger::LogWarning(const string& message)
    {
        if(instance == nullptr)
            throw NullException{"Please run Logger::CreateLogger before Logger::LogWarning", __ExceptionParams__};

        if(DisplayLevel >= LoggerLevel::Warning)
            instance->warningStream->writeLine("WARNING - " + GetDateTime() + " - " + message);
    }

    void Logger::LogError(const string& message)
    {
        if(instance == nullptr)
            throw NullException{"Please run Logger::CreateLogger before Logger::LogError", __ExceptionParams__};

        if(DisplayLevel >= LoggerLevel::Error)
            instance->errorStream->writeLine("ERROR - " + GetDateTime() + " - " + message);
    }

    void Logger::LogFatalError(const string& message)
    {
        if(instance == nullptr)
            throw NullException{"Please run Logger::CreateLogger before Logger::LogFatalError", __ExceptionParams__};

        if(DisplayLevel >= LoggerLevel::FatalError)
            instance->fatalErrorStream->writeLine("FATAL ERROR - " + GetDateTime() + " - " + message);
    }

    void Logger::StartLogger()
    {
        if(!loggerRunning)
        {
            if(instance == nullptr)
                throw NullException{"Please run Logger::CreateLogger atleast once before trying to restart it.", __ExceptionParams__};
            loggerRunning = true;
        }
    }
    
    void Logger::StopLogger()
    {
        if(loggerRunning)
        {
            loggerRunning = false;
        }
    }
}

#undef __class__