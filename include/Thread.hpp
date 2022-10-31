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

#include "FormattingDecorations.hpp"

namespace simplex
{
    class ThreadBase : public object
    {
        public:
        ThreadBase();
        virtual ~ThreadBase();
    };

    template<typename ... Args>
    class Thread : public ThreadBase
    {
        std::function<void(Args...)> func;

        public:
        bool isFinished;

        private:
        std::thread* thread;

        public:
        Thread(std::function<void(Args...)> func, Args... args) : func{func}, isFinished{false}, thread{new std::thread{std::bind(&Thread::threadRunner, this, args...)}}
        { }

        virtual ~Thread()
        {
            if(thread->joinable())
                thread->detach();
            delete thread;
        }

        void threadRunner(Args... args)
        {
            isFinished = false;
            func(args...);
            isFinished = true;
        }

        void waitForFinish()
        {
            thread->join();
        }
    };
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_THREAD_HPP