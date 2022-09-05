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

#ifndef SIMPLEX_LOGGER_HPP
#define SIMPLEX_LOGGER_HPP

#include "StreamWriter.hpp"
#include "string.hpp"
#include "Singleton.hpp"

#define __class__ "simplex::Logger"

#include "FormattingDecorations.hpp"

namespace simplex
{
    #define __LoggerLocationInformation__ string{" In file: '"} + __FILE__ + "' on line: '" + __LINE__ + "'"

    enum class LoggerLevel : char
    { 
        On = 6, 
        Debug = 5, 
        Info = 4, 
        Warning = 3, 
        Error = 2, 
        FatalError =  1, 
        Off = 0
    };

    class Logger : public Singleton
    {
        StreamWriter* debugStream;
        StreamWriter* infoStream;
        StreamWriter* warningStream;
        StreamWriter* errorStream;
        StreamWriter* fatalErrorStream;
        bool uniquePointers;
        bool takeOnOwnership;

        static bool loggerRunning;
        static Logger* instance;

        Logger(inout ownership StreamWriter* stream, in bool takeOnOwnership);
        Logger(inout ownership StreamWriter* debugStream, inout ownership StreamWriter* infoStream, inout ownership StreamWriter* warningStream, 
            inout ownership StreamWriter* errorStream, inout ownership StreamWriter* fatalErrorStream, in bool takeOnOwnership);

        public:
        static LoggerLevel DisplayLevel;
        static LoggerLevel KillSwitch;

        virtual ~Logger();

        // Specify each stream for each logging type. Creating with pointers means logger will take over ownership
        static void CreateLogger(inout ownership StreamWriter* debugStream, inout ownership StreamWriter* infoStream, 
            inout ownership StreamWriter* warningStream, inout ownership StreamWriter* errorStream, inout ownership StreamWriter* fatalErrorStream, 
            in LoggerLevel displayLevel = LoggerLevel::On);
        // Specify each stream for each logging type. Creating with references means you manage steam memory.
        static void CreateLogger(inout StreamWriter& debugStream, inout StreamWriter& infoStream, 
            inout StreamWriter& warningStream, inout StreamWriter& errorStream, inout StreamWriter& fatalErrorStream, 
            in LoggerLevel displayLevel = LoggerLevel::On);
        // Specify one stream for all the logging to take place on. Creating with pointer means it will take over ownership.
        static void CreateLogger(inout ownership StreamWriter* stream, in LoggerLevel displayLevel = LoggerLevel::On);
        // Specify one stream for all the logging to take place on. Creating with reerences means you manage stream memory.
        static void CreateLogger(inout StreamWriter& stream, in LoggerLevel displayLevel = LoggerLevel::On);
        static void LogDebug(in const string& message);
        static void LogInfo(in const string& message);
        static void LogWarning(in const string& message);
        static void LogError(in const string& message);
        static void LogFatalError(in const string& message);
        static void UnpauseLogger();
        static void PauseLogger();

        private:
        static string GetDateTime();
    };
}

#include "EndFormattingDecorations.hpp"
#undef __class__
#endif //SIMPLEX_LOGGER_HPP