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

#ifndef SIMPLEX_SMARTREF_HPP
#define SIMPLEX_SMARTREF_HPP

#include "object.hpp"
#include "Array.hpp"

namespace simplex
{
    template<typename classType>
    class SmartRef : public object
    {
        classType* pointer;
        bool managed;
        
        public:
        SmartRef();
        SmartRef(classType* pointer);
        virtual ~SmartRef();

        classType& getRef();
        classType* stopManaging();
        classType& startManaging(classType* pointer);
    };

    class SmartRefManager : public object
    {
        Array<SmartRef<object>> refs;
        public:
        template<typename type>
        type* add(SmartRef<type>& smartRef)
        {
            type* temp = smartRef.stopManaging();
            refs.add(SmartRef<object>{temp});
            return temp;
        }
    };
}

#include "Exception.hpp"
#include <typeinfo>

#define __class__ "simplex::SmartRef"

namespace simplex
{
    template<typename classType>
    SmartRef<classType>::SmartRef() : managed(false) {}
    template<typename classType>
    SmartRef<classType>::SmartRef(classType* pointer) : pointer(pointer), managed(true) {}

    template<typename classType>
    SmartRef<classType>::~SmartRef()
    {
        if(managed)
            delete pointer;
    }

    template<typename classType>
    classType& SmartRef<classType>::getRef()
    {
        return *pointer;
    }

    template<typename classType>
    classType* SmartRef<classType>::stopManaging()
    {
        managed = false;
        return pointer;
    }

    template<typename classType>
    classType& SmartRef<classType>::startManaging(classType* pointer)
    {
        if(!managed)
        {
            this->pointer = pointer;
            managed = true;
            return *pointer;
        }
        else
        {
            throw Exception{"A pointer is already being managed please stop managing this pointer before attempting to manage a new one.", __ExceptionParams__};
        }
    }
}

#undef __class__

#endif //SIMPLEX_SMARTREF_HPP