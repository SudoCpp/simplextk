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

#include "SupportsSignals.hpp"
#include <algorithm>

namespace simplex
{
    SupportsSignals::SupportsSignals()
    {}

    SupportsSignals::~SupportsSignals()
    {
        //Called by slot, tells signal that slot is now invalid.
        for(SupportsSignals* signalObj : linkedSignalObjects)
            signalObj->removeSlot(this);

        // // //Called by signal, tells slot it doesn't need to notify signal when slot is destructing
        for(SupportsSignals* slotObj : linkedSlotObjects)
            slotObj->removeSignal(this);
    }

    bool SupportsSignals::vecContains(const std::vector<SupportsSignals*>& vec, SupportsSignals* value)
    {
        return (::std::find(vec.begin(), vec.end(), value) != vec.end()) ? true : false;
    }

    void SupportsSignals::vecRemove(std::vector<SupportsSignals*>& vec, SupportsSignals* value)
    {
        int32_t size = vec.size();
        for (int32_t loop = 0; loop < size; loop++)
            if (vec[loop] == value)
            {
                vec.erase(vec.begin() + loop);
                break;
            }
    }
    
    void SupportsSignals::addSignal(SupportsSignals* signalObj)
    {
        if(!vecContains(linkedSignalObjects, signalObj))
            linkedSignalObjects.push_back(signalObj);
    }

    void SupportsSignals::removeSignal(SupportsSignals* signalObj)
    {
        if(vecContains(linkedSignalObjects, signalObj))
            vecRemove(linkedSignalObjects, signalObj);
    }

    void SupportsSignals::removeSlot(SupportsSignals* slotObj)
    {
        if(vecContains(linkedSlotObjects, slotObj))
            vecRemove(linkedSlotObjects, slotObj);
    }

    void SupportsSignals::addSlot(SupportsSignals* slotObj)
    {
        if(!vecContains(linkedSlotObjects, slotObj))
            linkedSlotObjects.push_back(slotObj);
    }

    bool SupportsSignals::slotInstanceStillExists(SupportsSignals* slotObj)
    {
        return vecContains(linkedSlotObjects, slotObj);
    }

    SupportsSignals::operator SupportsSignals*() { return (SupportsSignals*)this; }
}