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

#ifndef SIMPLEX_DATACELL_HPP
#define SIMPLEX_DATACELL_HPP

#include "object.hpp"
#include "string.hpp"
#include "Array.hpp"

#include "FormattingDecorations.hpp"

namespace simplex
{
    enum class DataCellType
    {
        Pointer,
        Uint8_t,
        Uint16_t,
        Uint32_t,
        Uint64_t,
        Int8_t,
        Int16_t,
        Int32_t,
        Int64_t,
        Double,
        LongDouble,
        Float,
        String,
        NotSet
    };

    #define __class__ "simplex::DataCell"
    class DataTable;
    class DataCell : public object
    {
        union
        {
            void* data;
            uint64_t largeUnsigned;
            int64_t largeSigned;
            long double largeDouble;
            double Double;
            float Float;
        };
        union
        {
            size_t sizeInBytes;
            uint8_t decimalPrecision;
        };
        string String;
        
        _internal:
        DataCellType type;

        public:
        DataCell();
        DataCell(in ownership void* value, in size_t sizeOfValueInBytes);
        DataCell(in uint8_t value);
        DataCell(in uint16_t value);
        DataCell(in uint32_t value);
        DataCell(in uint64_t value);
        DataCell(in int8_t value);
        DataCell(in int16_t value);
        DataCell(in int32_t value);
        DataCell(in int64_t value);
        DataCell(in float value);
        DataCell(in double value);
        DataCell(in long double value);
        DataCell(in string value);
        virtual void* getValue();
        virtual ~DataCell();

        void setValue(in ownership void* value, in size_t sizeOfValueInBytes);
        void setValue(in uint8_t value);
        void setValue(in uint16_t value);
        void setValue(in uint32_t value);
        void setValue(in uint64_t value);
        void setValue(in int8_t value);
        void setValue(in int16_t value);
        void setValue(in int32_t value);
        void setValue(in int64_t value);
        void setValue(in float value, in uint8_t decimalPrecision);
        void setValue(in double value, in uint8_t decimalPrecision);
        void setValue(in long double value, in uint8_t decimalPrecision);
        void setValue(in string value);
    
        template<typename returnType>
        void* getValue(typename std::enable_if<std::is_same<void*, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Pointer)
                return data;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        uint8_t getValue(typename std::enable_if<std::is_same<uint8_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Uint8_t || type == DataCellType::Uint16_t || type == DataCellType::Uint32_t || type == DataCellType::Uint64_t)
                return (returnType)largeUnsigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        uint16_t getValue(typename std::enable_if<std::is_same<uint16_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Uint16_t || type == DataCellType::Uint32_t || type == DataCellType::Uint64_t)
                return (returnType)largeUnsigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        uint32_t getValue(typename std::enable_if<std::is_same<uint32_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Uint32_t || type == DataCellType::Uint64_t)
                return (returnType)largeUnsigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        uint64_t getValue(typename std::enable_if<std::is_same<uint64_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Uint64_t)
                return (returnType)largeUnsigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        int8_t getValue(typename std::enable_if<std::is_same<int8_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Int8_t || type == DataCellType::Int16_t || type == DataCellType::Int32_t || type == DataCellType::Int64_t)
                return (returnType)largeSigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        int16_t getValue(typename std::enable_if<std::is_same<int16_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Int16_t || type == DataCellType::Int32_t || type == DataCellType::Int64_t)
                return (returnType)largeSigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        int32_t getValue(typename std::enable_if<std::is_same<int32_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Int32_t || type == DataCellType::Int64_t)
                return (returnType)largeSigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        int64_t getValue(typename std::enable_if<std::is_same<int64_t, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Int64_t)
                return (returnType)largeSigned;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        float getValue(typename std::enable_if<std::is_same<float, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Float)
                return Float;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        double getValue(typename std::enable_if<std::is_same<double, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::Double)
                return Double;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        long double getValue(typename std::enable_if<std::is_same<long double, returnType>::value>::type* = nullptr)
        {
            if(type == DataCellType::LongDouble)
                return largeDouble;
            else
                throw Exception("Return type doesn't match storage type.", __ExceptionParams__);
        }
        template<typename returnType>
        string getValue(typename std::enable_if<std::is_same<string, returnType>::value>::type* = nullptr)
        {
            try
            {
                switch (type)
                {
                    case DataCellType::String:
                        return String;
                    case DataCellType::Pointer:
                        return string{"Binary Object"};
                    case DataCellType::Uint8_t:
                    case DataCellType::Uint16_t:
                    case DataCellType::Uint32_t:
                    case DataCellType::Uint64_t:
                        return string::FromNumber(largeUnsigned);
                    case DataCellType::Int8_t:
                    case DataCellType::Int16_t:
                    case DataCellType::Int32_t:
                    case DataCellType::Int64_t:
                        return string::FromNumber(largeSigned);
                    case DataCellType::Float:
                        return string::FromNumber(Float, decimalPrecision);
                    case DataCellType::Double:
                        return string::FromNumber(Double, decimalPrecision);
                    //case DataCellType::LongDouble:
                    default:
                        return string::FromNumber(largeDouble, decimalPrecision);
                }
            }
            catch (Exception ex)
            {
                throw Exception("Unable to convert cell to string.", __ExceptionParams__);
            }
        }
    };

    #undef __class__
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_DATACELL_HPP