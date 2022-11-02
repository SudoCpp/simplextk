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

#include "ThreadManager.hpp"
#include "Thread.hpp"
#include "Exception.hpp"

#define __class__ "simplex::ThreadManager"

namespace simplex
{
    ThreadManager* ThreadManager::managerInstance = nullptr;

    ThreadManager::ThreadManager() 
        : threads{true}, queuedThreads{false}, activeThreads{false}, noNewThreads{false}, gettingCaughtUp{false}
    { }

    void ThreadManager::RegisterInstance(ThreadBase* instance)
    {
        if(managerInstance == nullptr)
            managerInstance = new ThreadManager();
        if(!managerInstance->threads.contains(instance))
            managerInstance->threads.add(instance);
        managerInstance->queuedThreads.add(instance);
        managerInstance->evaluateThreadStatus();
    }

    void ThreadManager::UnregisterInstance(ThreadBase* instance)
    {
        if(managerInstance == nullptr)
            managerInstance = new ThreadManager();
        managerInstance->threads.remove(instance, false);
        managerInstance->evaluateThreadStatus();
    }

    void ThreadManager::SetSettings(const ThreadManagerSettings& settings)
    {
        if(managerInstance == nullptr)
            managerInstance = new ThreadManager();
        managerInstance->settings.maximumNumberConcurrentThreads = settings.maximumNumberConcurrentThreads;
        managerInstance->settings.multiThreadedProgram = settings.multiThreadedProgram;
        managerInstance->settings.oneThreadPerClassInstance = settings.oneThreadPerClassInstance;
        managerInstance->evaluateThreadStatus();
    }

    ThreadManager::~ThreadManager()
    { 
        if(activeThreads.size() > 0)
            throw Exception("Program is terminating and there are still Threads running. You will have undefined behavior.", __ExceptionParams__);
    }

    void ThreadManager::evaluateThreadStatus()
    {
        const std::lock_guard<std::mutex> lock{threadMutex};
        if(!noNewThreads)
        {
            if(managerInstance == nullptr)
                managerInstance = new ThreadManager();
            if(activeThreads.size() < managerInstance->settings.maximumNumberConcurrentThreads || managerInstance->settings.maximumNumberConcurrentThreads == 0)
            {   Array<void*> activeAddresses{false};
                for(ThreadBase* thread : activeThreads)
                    activeAddresses.add(thread->instanceAddress);
                for (ThreadBase* thread : queuedThreads)
                {
                    if(!managerInstance->settings.oneThreadPerClassInstance)
                    {
                        startThread(thread);
                        break;
                    }//oneThreadPerClassInstance true below here
                    else if(!managerInstance->settings.globalFunctionsInOneInstance && thread->instanceAddress == nullptr)
                    {
                        startThread(thread);
                        break;
                    }
                    else if(!activeAddresses.contains(thread->instanceAddress))
                    {
                        startThread(thread);
                        break;
                    }
                }
            }
        }
    }

    void ThreadManager::startThread(ThreadBase* thread)
    {
        queuedThreads.remove(thread, false);
        activeThreads.add(thread);
        if(managerInstance->settings.multiThreadedProgram && !gettingCaughtUp)
            thread->startThread();
        else
            thread->startSingle();

        if(queuedThreads.size() == 0 && gettingCaughtUp)
            gettingCaughtUp = false;
    }

    void ThreadManager::ThreadFinished(ThreadBase* instance)
    {
        if(managerInstance == nullptr)
            managerInstance = new ThreadManager();
        managerInstance->activeThreads.remove(instance, false);
        managerInstance->evaluateThreadStatus();
    }

    void ThreadManager::WaitForAllThreadsToFinish(bool preventQueuedThreadsFromStarting)
    {
        if(managerInstance == nullptr)
            managerInstance = new ThreadManager();
        managerInstance->gettingCaughtUp = true;
        managerInstance->noNewThreads = preventQueuedThreadsFromStarting;
        for(ThreadBase* thread : managerInstance->activeThreads)
            thread->waitForFinish();
    }
}

#undef __class__