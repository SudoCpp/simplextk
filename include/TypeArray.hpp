/*
    BSD 3-Clause License
    
    Copyright (c) 2021, SudoCpp
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

//This saves on the typing :D
#define getType(typeArray, index) decltype(simplex::typeArrayGet<(index)>(typeArray))::type

namespace simplex
{
    //This is the base template so that we can specialize below
    template<int index, typename... Types>
    class TypeElement;

    //As the Types are unpacked eventually there will be no types left, this prevent compile error
    template<int index>
    class TypeElement<index>
    {};

    //This starts to unpack the types.
    template<int index, typename FirstType, typename... Types>
    class TypeElement<index, FirstType, Types...> :
    public TypeElement<index+1, Types...> //This will unpack and uniquely name with a number
    {
        public:
        using type = FirstType; // Simliar to #define but allows a type we can access
    };

    template<int index, typename FirstType, typename... Types>
    auto typeArrayGet(TypeElement<index, FirstType, Types...> typeArray)
    {
        //Create an instance of this class so we can decltype it
        return TypeElement<index, FirstType, Types...>();
    }

    template<typename... Types>
    using TypeArray = TypeElement<0, Types...>;
}