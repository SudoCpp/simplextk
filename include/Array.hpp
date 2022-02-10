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

#ifndef SIMPLEX_ARRAY_HPP
#define SIMPLEX_ARRAY_HPP

#include <algorithm>
#include "Exception.hpp"
#include <vector>
#include <string>

namespace simplex
{
	template <typename ArrayMemberType> class Array
	{
		public:
            using Type = ArrayMemberType;
			Array();
			Array(::std::initializer_list<ArrayMemberType> iList);
			Array(int32_t arraySize, char* characterArray[]);
			Array(int32_t arraySize, ArrayMemberType nativeArray[]);
			Array(::std::vector<ArrayMemberType> vectorObject);

			//Operators
            ArrayMemberType operator[](int32_t index) const;
            ArrayMemberType& operator[](int32_t index);

			//Methods
			Array<ArrayMemberType>& add(ArrayMemberType& value) noexcept;
			Array<ArrayMemberType>& add(ArrayMemberType&& value) noexcept;
			Array<ArrayMemberType>& add(ArrayMemberType* value) noexcept;
			Array<ArrayMemberType>& add(ArrayMemberType value, int32_t index);
			Array<ArrayMemberType>& add(::std::initializer_list<ArrayMemberType> iList) noexcept;
			Array<ArrayMemberType>& add(Array<ArrayMemberType> arrayValues) noexcept;
			Array<ArrayMemberType>& add(::std::vector<ArrayMemberType> arrayValues) noexcept;
			
			static Array<ArrayMemberType> FromVector(::std::vector<ArrayMemberType> vectorObject) noexcept;
			std::vector<ArrayMemberType> toVector() const noexcept;
			
			ArrayMemberType& at(int32_t index);
            ArrayMemberType at(int32_t index) const;

			Array<ArrayMemberType>& clear() noexcept;
			
			Array<ArrayMemberType> getPartialArray(int32_t start) const;
			Array<ArrayMemberType> getPartialArray(int32_t start, int32_t count) const;
			
			bool contains(const ArrayMemberType& value) const;
			int32_t containsCount(const ArrayMemberType& value) const;
			int32_t indexOf(const ArrayMemberType& value) const;
			int32_t lastIndexOf(const ArrayMemberType& value) const;
			ArrayMemberType pop();
			Array<ArrayMemberType>& push(ArrayMemberType& value);
			
			Array<ArrayMemberType>& remove(const ArrayMemberType& value);
			Array<ArrayMemberType>& removeAll() noexcept;
			Array<ArrayMemberType>& removeAt(int32_t index);
			
			Array<ArrayMemberType>& reserveSpace(size_t spaceToReserve);
			
			Array<ArrayMemberType>& reverse();
			Array<ArrayMemberType>& reverseSort();
			struct sorter
			{
				inline bool operator() (ArrayMemberType type1, ArrayMemberType type2)
				{
                    if (::std::is_same<string, ArrayMemberType>::value || ::std::is_same<::std::string, ArrayMemberType>::value || ::std::is_integral<ArrayMemberType>::value || ::std::is_same<float, ArrayMemberType>::value || ::std::is_same<double, ArrayMemberType>::value || ::std::is_same<long double, ArrayMemberType>::value)
                        return type1 < type2;
                    else
                        return true;
                }
			};
			Array<ArrayMemberType>& sort();
			
            auto begin() const noexcept
			{
				return array_.begin();
			}
            auto end() const noexcept
			{
				return array_.end();
			}
			
			size_t size() const;

		protected:
			::std::vector<ArrayMemberType> array_;
	};
}

#define __class__ "simplex::Array"

namespace simplex
{
    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array() {}

    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array(::std::initializer_list<ArrayMemberType> iList)
    {
        for (ArrayMemberType item : iList)
            add(item);
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array(int32_t arraySize, char* characterArray[])
    {
        for (int32_t i = 0; i < arraySize; i++)
            array_.emplace_back(::std::string(characterArray[i]));
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>::Array(::std::vector<ArrayMemberType> vectorObject) : array_{vectorObject}
    {}

    //Operators
    template <typename ArrayMemberType>
    ArrayMemberType Array<ArrayMemberType>::operator[](int32_t index) const
    {
        return at(index);
    }
    template <typename ArrayMemberType>
    ArrayMemberType& Array<ArrayMemberType>::operator[](int32_t index)
    {
        return at(index);
    }

    //Methods
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(ArrayMemberType& value) noexcept
    {
        array_.emplace_back(std::move(value));
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(ArrayMemberType&& value) noexcept
    {
        array_.emplace_back(value);
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(ArrayMemberType* value) noexcept
    {
        array_.emplace_back(value);
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(ArrayMemberType value, int32_t index)
    {
        if (index < size() + 1)
        {
            array_.insert(array_.begin() + index, value);
        }
        else
            throw IndexOutOfBoundsException{"Index "+ string::FromNumber(index) +" does not exist.", __ExceptionParams__};

        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(::std::initializer_list<ArrayMemberType> iList) noexcept
    {
        for (ArrayMemberType item : iList)
            add(item);
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(Array<ArrayMemberType> arrayValues) noexcept
    {
        array_.insert(array_.end(), arrayValues.begin(), arrayValues.end());
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::add(::std::vector<ArrayMemberType> arrayValues) noexcept
    {
        array_.insert(array_.end(), arrayValues.begin(), arrayValues.end());
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType> Array<ArrayMemberType>::FromVector(::std::vector<ArrayMemberType> vectorObject) noexcept
    {
        Array<ArrayMemberType> array{vectorObject};
        return array;
    }
    template <typename ArrayMemberType>
    ::std::vector<ArrayMemberType> Array<ArrayMemberType>::toVector() const noexcept
    {
        return array_;
    }

    template <typename ArrayMemberType>
    ArrayMemberType& Array<ArrayMemberType>::at(int32_t index)
    {
        try
        {
            return array_.at(index);
        }
        catch (...)
        {
            throw IndexOutOfBoundsException("Index "+ string::FromNumber(index) +" does not exist.", __ExceptionParams__);
        }
    }
    template <typename ArrayMemberType>
    ArrayMemberType Array<ArrayMemberType>::at(int32_t index) const
    {
        try
        {
            const ArrayMemberType temp = array_.at(index);
            return temp;
        }
        catch (...)
        {
            throw IndexOutOfBoundsException("Index "+ string::FromNumber(index) +" does not exist.", __ExceptionParams__);
        }
    }

    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::clear() noexcept
    {
        array_.clear();
        return *this;
    }

    template <typename ArrayMemberType>
    Array<ArrayMemberType> Array<ArrayMemberType>::getPartialArray(int32_t start) const
    {
        int32_t arraySize = array_.size();
        if (start < 0)
            start = arraySize + start;

        if (start > arraySize)
            throw IndexOutOfBoundsException("Starting beyond size of Array.", __ExceptionParams__);

        return Array<ArrayMemberType>(::std::vector<ArrayMemberType>(array_.begin() + start, array_.end()));
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType> Array<ArrayMemberType>::getPartialArray(int32_t start, int32_t count) const
    {
        int32_t arraySize = array_.size();
        if (start < 0)
            start = arraySize + start;
        if (count < 0)
            count = arraySize - start + count;

        if (start > arraySize)
            throw IndexOutOfBoundsException("Starting beyond size of Array.", __ExceptionParams__);
        else if (start + count > arraySize)
            throw IndexOutOfBoundsException("Starting beyond size of Array.", __ExceptionParams__);

        if (start + count == arraySize)
            return Array<ArrayMemberType>(::std::vector<ArrayMemberType>(array_.begin() + start, array_.end()));
        else
            return Array<ArrayMemberType>(::std::vector<ArrayMemberType>(array_.begin() + start, array_.begin() + start + count));
    }
    
    template <typename ArrayMemberType>
    bool Array<ArrayMemberType>::contains(const ArrayMemberType& value) const
    {
        return (::std::find(array_.begin(), array_.end(), value) != array_.end()) ? true : false;
    }
    template <typename ArrayMemberType>
    int32_t Array<ArrayMemberType>::containsCount(const ArrayMemberType& value) const
    {
        return ::std::count(array_.begin(), array_.end(), value);
    }
    template <typename ArrayMemberType>
    int32_t Array<ArrayMemberType>::indexOf(const ArrayMemberType& value) const
    {
        return ::std::distance(array_.begin(), ::std::find(array_.begin(), array_.end(), value));
    }
    template <typename ArrayMemberType>
    int32_t Array<ArrayMemberType>::lastIndexOf(const ArrayMemberType& value) const
    {
        int32_t indexFromEnd = std::distance(array_.rbegin(), ::std::find(array_.rbegin(), array_.rend(), value));
        return array_.size() - indexFromEnd - 1;
    }
    template <typename ArrayMemberType>
    ArrayMemberType Array<ArrayMemberType>::pop()
    {
        ArrayMemberType temp = array_.at(array_.size() - 1);
        array_.pop_back();
        return temp;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::push(ArrayMemberType& value)
    {
        add(value);
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::remove(const ArrayMemberType& value)
    {
        int32_t arraySize = size();
        for (int32_t loop = 0; loop < arraySize; loop++)
            if (array_[loop] == value)
            {
                removeAt(loop);
                break;
            }

        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::removeAll() noexcept
    {
        array_.clear();
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::removeAt(int32_t index)
    {
        array_.erase(array_.begin() + index);
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::reserveSpace(size_t spaceToReserve)
    {
        array_.reserve(spaceToReserve);
        return *this;
    }
    
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::reverse()
    {
        ::std::reverse(array_.begin(), array_.end());
        return *this;
    }
    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::reverseSort()
    {
        sort();
        reverse();
        return *this;
    }

    template <typename ArrayMemberType>
    Array<ArrayMemberType>& Array<ArrayMemberType>::sort()
    {
        ::std::sort(array_.begin(), array_.end(), sorter());
        return *this;
    }
    
    template <typename ArrayMemberType>
    size_t Array<ArrayMemberType>::size() const
    {
        return array_.size();
    }
}

#undef __class__

#endif // SIMPLEX_ARRAY_HPP