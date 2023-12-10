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

#ifndef SIMPLEX_SIGNAL_HPP
#define SIMPLEX_SIGNAL_HPP

#include "object.hpp"
#include <functional>
#include "Dictionary.hpp"
#include <type_traits>
#include "string.hpp"
#include "Array.hpp"
#include "SupportsSignals.hpp"

namespace simplex
{
    using namespace std::placeholders;

    template<typename ReturnType, typename ... Args>
    class Signal : public object
    {
        mutable Dictionary<uint32_t, std::function<ReturnType(Args...)>> slots;
        mutable Dictionary<uint32_t, SupportsSignals*> slotParents;
        mutable uint32_t currentKey;
        public:
        Signal();

        virtual ~Signal() = default;
        
        void emit(Args... args);
        void emit(Args... args) const;
        uint32_t connect(std::function<ReturnType(Args...)> slot);
        Signal<ReturnType, Args...>& disconnect(uint32_t handle);
        
        //If this signal is emitted then call this method from this instance.
        template<typename SlotClassType>
        uint32_t connect(ReturnType(SlotClassType::*slot)(Args...), SlotClassType* slotInstance);
        
        template<typename SlotClassType>
        uint32_t connect(ReturnType(SlotClassType::*slot)(Args...) const, const SlotClassType* slotInstance);
        
        //If this signal is emitted then emit it again with the following signal
        uint32_t connect(Signal<ReturnType, Args...>* signal);
    };

    template<typename ReturnType, typename ... Args>
    Signal<ReturnType, Args...>::Signal() : currentKey{0}
    {}

    template<typename ReturnType, typename ... Args>
    void Signal<ReturnType, Args...>::emit(Args... args)
    {
        Array<uint32_t> slotParentKeys = slotParents.keys();
        for(uint32_t key : slotParentKeys)
            if(slotParents[key] == nullptr)
            {
                std::function<void(Args...)> bound = std::bind(slots[key], args...);
                bound(args...);
            }
            else if(slotInstanceStillExists(slotParents[key]))
            {
                std::function<void(Args...)> bound = std::bind(slots[key], args...);
                bound(args...);
            }
            else
            { //This instance has died and slots need to be removed.
                slots.removeByKey(key);
                slotParents.removeByKey(key);
            }
    }

    template<typename ReturnType, typename ... Args>
    void Signal<ReturnType, Args...>::emit(Args... args) const
    {
        Array<uint32_t> slotParentKeys = slotParents.keys();
        for(uint32_t key : slotParentKeys)
            if(slotParents[key] == nullptr)
            {
                std::function<void(Args...)> bound = std::bind(slots[key], args...);
                bound(args...);
            }
            else if(slotInstanceStillExists(slotParents[key]))
            {
                std::function<void(Args...)> bound = std::bind(slots[key], args...);
                bound(args...);
            }
            else
            { //This instance has died and slots need to be removed.
                slots.removeByKey(key);
                slotParents.removeByKey(key);
            }
    }

    template<typename ReturnType, typename ... Args>
    uint32_t Signal<ReturnType, Args...>::connect(std::function<ReturnType(Args...)> slot)
    {
        slotParents.add(currentKey, nullptr);
        slots.add(currentKey, slot);
        currentKey++;
        return (currentKey-1);
    }

    template<typename ReturnType, typename ... Args>
    template<typename SlotClassType>
    uint32_t Signal<ReturnType, Args...>::connect(ReturnType(SlotClassType::*slot)(Args...) const, const SlotClassType* slotInstance)
    {
        static_assert(std::is_base_of<SupportsSignals, SlotClassType>::value, "Slot class must be derived from SupportsSignals");
        SupportsSignals* castedInstance = (SupportsSignals*)slotInstance;
        addSlot(castedInstance);
        castedInstance->addSignal(this); //Log this instance so when slot instance destructs it can alert signal parent
        slotParents.add(currentKey, castedInstance);
        slots.add(currentKey, [=](Args... args) 
        { 
            (slotInstance->*slot)(args...); 
        });
        currentKey++;
        return (currentKey-1);
    }

    template<typename ReturnType, typename ... Args>
    template<typename SlotClassType>
    uint32_t Signal<ReturnType, Args...>::connect(ReturnType(SlotClassType::*slot)(Args...), SlotClassType* slotInstance)
    {
        static_assert(std::is_base_of<SupportsSignals, SlotClassType>::value, "Slot class must be derived from SupportsSignals");
        SupportsSignals* castedInstance = (SupportsSignals*)slotInstance;
        addSlot(castedInstance);
        castedInstance->addSignal(this); //Log this instance so when slot instance destructs it can alert signal parent
        slotParents.add(currentKey, castedInstance);
        slots.add(currentKey, [=](Args... args) 
        { 
            (slotInstance->*slot)(args...); 
        });
        currentKey++;
        return (currentKey-1);
    }

    template<typename ReturnType, typename ... Args>
    uint32_t Signal<ReturnType, Args...>::connect(Signal<ReturnType, Args...>* signal)
    {
        return connect(&Signal<ReturnType, Args...>::emit, signal);
    }

    template<typename ReturnType, typename ... Args>
    Signal<ReturnType, Args...>& Signal<ReturnType, Args...>::disconnect(uint32_t handle)
    {
        slots.removeByKey(handle);
        slotParents.removeByKey(handle);
        return *this;
    }
}

#endif