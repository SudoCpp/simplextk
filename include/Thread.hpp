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

#ifndef SIMPLEX_THREAD_HPP
#define SIMPLEX_THREAD_HPP

#include <thread>
#include "object.hpp"
#include "ThreadManager.hpp"
#include "Signal.hpp"

#include "FormattingDecorations.hpp"

namespace simplex
{
    class ThreadBase : public object
    {
        friend class ThreadManager;

        void* instanceAddress;
        bool hasBeenStarted;
        std::function<void()> func;
        std::thread* thread;

        public :
        bool isFinished;

        public:
        ThreadBase(in void* instance, in std::function<void()> func);
        virtual ~ThreadBase();

        Signal<> started;
        Signal<> finished;

        void start();
        void waitForFinish();

        private:
        void startThread();
        void startSingle();

        private:
        void internalRunner();
    };

    template<typename ... Args>
    class Thread : public ThreadBase
    {
        public:
        template<typename ThreadClassType>
        Thread(in void(ThreadClassType::*method)(Args...), inout ThreadClassType& classInstance, in Args... args);
        Thread(in std::function<void(Args...)> func, in Args... args);
        virtual ~Thread() {}
    };

    template<typename ... Args>
    template<typename ThreadClassType>
    Thread<Args...>::Thread(void(ThreadClassType::*method)(Args...), ThreadClassType& classInstance, Args... args) 
        : ThreadBase{&classInstance, std::bind(method, &classInstance, args...)}
    { }

    template<typename ... Args>
    Thread<Args...>::Thread(std::function<void(Args...)> func, Args... args) 
        : ThreadBase{nullptr, std::bind(func, args...)}
    { }
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_THREAD_HPP