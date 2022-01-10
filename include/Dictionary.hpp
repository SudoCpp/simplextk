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

#ifndef SIMPLEX_DICTIONARY_HPP
#define SIMPLEX_DICTIONARY_HPP

#include <unordered_map>
#include "Array.hpp"
#include "Exception.hpp"

namespace simplex
{
    template<typename KeyType, typename ValueType>
    class Dictionary
    {
        protected:
        ::std::unordered_map<KeyType, ValueType> dictionary_;

        public:
        //Constructors
        Dictionary();
        Dictionary(::std::initializer_list<::std::pair<KeyType const, ValueType>> bracedPairs);

        //Operators
        ValueType operator [](const KeyType& key) const;
        ValueType& operator [](const KeyType& key);

        //Methods
        Dictionary<KeyType, ValueType>& add(KeyType key, ValueType value);
        Dictionary<KeyType, ValueType>&  add(::std::initializer_list<::std::pair<KeyType, ValueType>> bracedPairs);
        ValueType& at(const KeyType& key);
        ValueType at(const KeyType& key) const;
        // ValueType at(int index) const;
        // ValueType& at(int index);

        bool containsKey(const KeyType& key) const;
        Dictionary<KeyType, ValueType>& removeByKey(const KeyType& key);
        Dictionary<KeyType, ValueType>& clear();

        //Variables
        Array<KeyType> keys() const;
        Array<ValueType> values() const;

        //Standard c++ aliases
        Dictionary<KeyType, ValueType>& insert(KeyType key, ValueType value);
        int size() const;

        auto begin() const
        {
            return dictionary_.begin();
        }
        auto end() const
        {
            return dictionary_.end();
        }
    };
}

#include <utility>
#include "Exception.hpp"

#define __class__ "simplex::Dictionary"

namespace simplex
{	
    class KeyNotFoundException : public Exception
	{
		public:
            KeyNotFoundException(const string text, const char* fileName, const int lineNumber, const char* className, const char* methodName)
            : Exception{text, fileName, lineNumber, className, methodName}
            { 
                exceptionType = "KeyNotFoundException";
            }
	};
    
    template <typename KeyType, typename ValueType>
    Dictionary<KeyType, ValueType>::Dictionary() {}
    template <typename KeyType, typename ValueType>
    Dictionary<KeyType, ValueType>::Dictionary(::std::initializer_list<::std::pair<KeyType const, ValueType>> bracedPairs)
    {
        for (auto keyvalue : bracedPairs)
        {
            add(keyvalue.first, keyvalue.second);
        }
    }

    //Operators
    template <typename KeyType, typename ValueType>
    ValueType Dictionary<KeyType, ValueType>::operator [](const KeyType& key) const
    {
        return at(key);
    }
    template <typename KeyType, typename ValueType>
    ValueType& Dictionary<KeyType, ValueType>::operator [](const KeyType& key)
    {
        return at(key);
    }

    //Methods
    template <typename KeyType, typename ValueType>
    Dictionary<KeyType, ValueType>& Dictionary<KeyType, ValueType>::add(KeyType key, ValueType value)
    {
        dictionary_.insert(std::make_pair(key, value));
        return *this;
    }
    template <typename KeyType, typename ValueType>
    Dictionary<KeyType, ValueType>& Dictionary<KeyType, ValueType>::add(::std::initializer_list<::std::pair<KeyType, ValueType>> bracedPairs)
    {
        for (auto keyvalue : bracedPairs)
            add(keyvalue.first, keyvalue.second);
        return *this;
    }
    template <typename KeyType, typename ValueType>
    ValueType& Dictionary<KeyType, ValueType>::at(const KeyType& key)
    {
        try
        {
            if(containsKey(key))
                return dictionary_.at(key);
            else
                throw Exception{"Key not found.", __ExceptionParams__};
        }
        catch (...)
        {
            throw Exception{"Key not found.", __ExceptionParams__};
        }
    }
    template <typename KeyType, typename ValueType>
    ValueType Dictionary<KeyType, ValueType>::at(const KeyType& key) const
    {
        try
        {
            if(containsKey(key))
                return dictionary_.at(key);
            else
                throw Exception{"Key not found.", __ExceptionParams__};
        }
        catch (...)
        {
            throw Exception{"Key not found.", __ExceptionParams__};
        }
    }
    // template <typename KeyType, typename ValueType>
    // ValueType Dictionary<KeyType, ValueType>::at(int index) const
    // {
    //     try
    //     {
    //         auto keys = this->keys();
    //         return dictionary_.at(keys[index]);
    //     }
    //     catch (...)
    //     {
    //         throw KeyNotFoundException{"Unable to use this index in Dictionary", __ExceptionParams__};
    //     }
    // }
    // template <typename KeyType, typename ValueType>
    // ValueType& Dictionary<KeyType, ValueType>::at(int index)
    // {
    //     try
    //     {
    //         auto keys = this->keys();
    //         return dictionary_.at(keys[index]);
    //     }
    //     catch (...)
    //     {
    //         throw KeyNotFoundException{"Unable to use this index in Dictionary", __ExceptionParams__};
    //     }
    // }
    template <typename KeyType, typename ValueType>
    bool Dictionary<KeyType, ValueType>::containsKey(const KeyType& key) const
    {
        return (dictionary_.count(key) > 0);
    }
    template <typename KeyType, typename ValueType>
    Dictionary<KeyType, ValueType>& Dictionary<KeyType, ValueType>::removeByKey(const KeyType& key)
    {
        dictionary_.erase(key);
        return *this;
    }
    template <typename KeyType, typename ValueType>
    Dictionary<KeyType, ValueType>& Dictionary<KeyType, ValueType>::clear()
    {
        dictionary_.clear();
        return *this;
    }

    //Variables
    template <typename KeyType, typename ValueType>
    Array<KeyType> Dictionary<KeyType, ValueType>::keys() const
    {
        Array<KeyType> keys;
        keys.reserveSpace(dictionary_.size());

        for (auto key : dictionary_)
            keys.add(key.first);

        return keys;
    }
    template <typename KeyType, typename ValueType>
    Array<ValueType> Dictionary<KeyType, ValueType>::values() const
    {
        Array<ValueType> values;
        values.reserveSpace(dictionary_.size());

        for (auto value : dictionary_)
            values.add(value.second);

        return values;
    }

    //Standard c++ aliases
    template <typename KeyType, typename ValueType>
    Dictionary<KeyType, ValueType>& Dictionary<KeyType, ValueType>::insert(KeyType key, ValueType value)
    {
        Add(key, value);
        return *this;
    }
    template <typename KeyType, typename ValueType>
    int Dictionary<KeyType, ValueType>::size() const
    {
        return dictionary_.size();
    }
}

#undef __class__

#endif //SIMPLEX_DICTIONARY_HPP