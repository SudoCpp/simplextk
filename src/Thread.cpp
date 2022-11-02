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

#include "Thread.hpp"
#include "Exception.hpp"

#define __class__ "simplex::ThreadBase"

namespace simplex
{
    ThreadBase::ThreadBase(void* instance, std::function<void()> func) 
        : instanceAddress{instance}, hasBeenStarted{false}, 
        isFinished{false}, func{func},
        thread{nullptr}
    { }

    ThreadBase::~ThreadBase()
    {
        if(thread != nullptr)
        {
            if(thread->joinable())
                thread->detach();
        }
        ThreadManager::UnregisterInstance(this);
        if(thread != nullptr)
        {
            delete thread;
        }
    }

    void ThreadBase::start()
    {
        if(!hasBeenStarted)
        {
            hasBeenStarted = true;
            ThreadManager::RegisterInstance(this);
        }
        else if(isFinished)
        {
            isFinished = false;
            ThreadManager::RegisterInstance(this);
        }
        else
            throw Exception("A Thread that is currently running is trying to run again. Please wait for the Thread to finish before rerunning.", __ExceptionParams__);
    }

    void ThreadBase::waitForFinish()
    {
        if(thread != nullptr)
            if(thread->joinable())
                thread->join();
    }

    void ThreadBase::startThread()
    {
        thread = new std::thread(&ThreadBase::internalRunner, this);
    }

    void ThreadBase::startSingle()
    {
        internalRunner();
    }

    void ThreadBase::internalRunner()
    {
        started.emit();
        isFinished = false;
        func();
        isFinished = true;
        ThreadManager::ThreadFinished(this);
        finished.emit();
    }
}

#undef __class__