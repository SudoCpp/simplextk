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

    template<typename ... Args>
    class Signal : public object
    {
        mutable Dictionary<unsigned int, std::function<void(Args...)>> slots;
        mutable Dictionary<unsigned int, SupportsSignals*> slotParents;
        mutable unsigned int currentKey;
        public:
        Signal();

        virtual ~Signal() = default;
        
        Signal<Args...>& emit(Args... args);
        unsigned int connect(std::function<void(Args...)> slot);
        Signal<Args...>& disconnect(unsigned int handle);
        template<typename SlotClassType>
        unsigned int connect(void(SlotClassType::*slot)(Args...), SlotClassType* slotInstance);
    };

    template<typename ... Args>
    Signal<Args...>::Signal() : currentKey{0}
    {}

    template<typename ... Args>
    Signal<Args...>& Signal<Args...>::emit(Args... args)
    {
        Array<unsigned int> slotParentKeys = slotParents.keys();
        for(unsigned int key : slotParentKeys)
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
        return *this;
    }

    template<typename ... Args>
    unsigned int Signal<Args...>::connect(std::function<void(Args...)> slot)
    {
        slotParents.add(currentKey, nullptr);
        slots.add(currentKey, slot);
        currentKey++;
        return (currentKey-1);
    }

    template<typename ... Args>
    template<typename SlotClassType>
    unsigned int Signal<Args...>::connect(void(SlotClassType::*slot)(Args...), SlotClassType* slotInstance)
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

    template<typename ... Args>
    Signal<Args...>& Signal<Args...>::disconnect(unsigned int handle)
    {
        slots.removeByKey(handle);
        slotParents.removeByKey(handle);
        return *this;
    }
}

#endif