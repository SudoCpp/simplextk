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

#ifndef SIMPLEX_THREADMANAGER_HPP
#define SIMPLEX_THREADMANAGER_HPP

#include "Array.hpp"
#include "Singleton.hpp"
#include <mutex>

#include "FormattingDecorations.hpp"

namespace simplex
{
    class ThreadManagerSettings
    {
        public:
        bool multiThreadedProgram;
        //Excluding the main thread that the program is running on
        //0 means unlimited, 
        uint32_t maximumNumberConcurrentThreads;

        //Mark this as true if you want one instance of a class to only be running at one time.
        //Example:
        // class Car;
        // Car car1{};
        // Car car2{};
        // Thread<Car> car1Thread1(&Car::method1, car1);
        // Thread<Car> car1Thread2(&Car::method2, car1); //Will not run until after car1Thread1 finishes.
        // Thread<Car> car2Thread1(&Car::method1, car2); //Different instance of Car will run immediately.
        bool oneThreadPerClassInstance;
        // If oneThreadPerClassInstance is true, this will great global functions (non-member functions) as if they
        // are in one instance. 
        bool globalFunctionsInOneInstance;

        ThreadManagerSettings() 
            : multiThreadedProgram{true}, maximumNumberConcurrentThreads{0}, 
            oneThreadPerClassInstance{false}, globalFunctionsInOneInstance{false}
        {}
    };

    class ThreadBase;
    class ThreadManager : public Singleton
    {
        Array<ThreadBase*> threads;
        Array<ThreadBase*> queuedThreads;
        Array<ThreadBase*> activeThreads;
        ThreadManagerSettings settings;
        std::mutex threadMutex;
        ThreadManager();
        static ThreadManager* managerInstance;
        bool noNewThreads;
        bool gettingCaughtUp;

        public:
        virtual ~ThreadManager();
        static void SetSettings(const ThreadManagerSettings& settings);
        static void WaitForAllThreadsToFinish(bool preventQueuedThreadsFromStarting = false);

        private:
        void evaluateThreadStatus();
        void startThread(ThreadBase* thread);

        internal:
        static void RegisterInstance(ThreadBase* instance);
        static void UnregisterInstance(ThreadBase* instance);
        static void ThreadFinished(ThreadBase* instance);
    };
}

#include "EndFormattingDecorations.hpp"

#endif // SIMPLEX_THREADMANAGER_HPP