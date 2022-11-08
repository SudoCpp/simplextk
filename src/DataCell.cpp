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

#include "DataCell.hpp"
#include "Exception.hpp"

namespace simplex
{
    #define __class__ "simplex::DataCell"
    DataCell::DataCell() 
        : type{DataCellType::NotSet} 
    {}
    DataCell::DataCell(void* value, size_t sizeOfValueInBytes) 
        : data{value}, sizeInBytes{sizeOfValueInBytes}, type{DataCellType::Pointer} 
    {}
    DataCell::DataCell(uint8_t value)
        : largeUnsigned{value}, type{DataCellType::Uint8_t} 
    {}
    DataCell::DataCell(uint16_t value) 
        : largeUnsigned{value}, type{DataCellType::Uint16_t} 
    {}
    DataCell::DataCell(uint32_t value) 
        : largeUnsigned{value}, type{DataCellType::Uint32_t}
    {}
    DataCell::DataCell(uint64_t value) 
        : largeUnsigned{value}, type{DataCellType::Uint64_t} 
    {}
    DataCell::DataCell(int8_t value) 
        : largeSigned{value}, type{DataCellType::Int8_t} 
    {}
    DataCell::DataCell(int16_t value) 
        : largeSigned{value}, type{DataCellType::Int16_t}
    {}
    DataCell::DataCell(int32_t value) 
        : largeSigned{value}, type{DataCellType::Int32_t} 
    {}
    DataCell::DataCell(int64_t value) 
        : largeSigned{value}, type{DataCellType::Int64_t} 
    {}
    DataCell::DataCell(float value) 
        : Float{value}, type{DataCellType::Float} 
    {}
    DataCell::DataCell(double value) 
        : Double{value}, type{DataCellType::Double} 
    {}
    DataCell::DataCell(long double value) 
        : largeDouble{value}, type{DataCellType::LongDouble} 
    {}
    DataCell::DataCell(string value) 
        : String{value}, type{DataCellType::String} 
    {}
    void* DataCell::getValue() 
    { 
        return data; 
    }

    DataCell::~DataCell()
    {
        if(type == DataCellType::Pointer && data != nullptr)
            free(data);
    }

    void DataCell::setValue(void* value, size_t sizeOfValueInBytes)
    {
        if(data != nullptr)
            free(data);
        data = value;
        sizeInBytes = sizeOfValueInBytes;
        type = DataCellType::Pointer;
    }
    void DataCell::setValue(uint8_t value)
    {
        largeUnsigned = value;
        type = DataCellType::Uint8_t;
    }
    void DataCell::setValue(uint16_t value)
    {
        largeUnsigned = value;
        type = DataCellType::Uint16_t;
    }
    void DataCell::setValue(uint32_t value)
    {
        largeUnsigned = value;
        type = DataCellType::Uint32_t;
    }
    void DataCell::setValue(uint64_t value)
    {
        largeUnsigned = value;
        type = DataCellType::Uint64_t;
    }
    void DataCell::setValue(int8_t value)
    {
        largeSigned = value;
        type = DataCellType::Int8_t;
    }
    void DataCell::setValue(int16_t value)
    {
        largeSigned = value;
        type = DataCellType::Int16_t;
    }
    void DataCell::setValue(int32_t value)
    {
        largeSigned = value;
        type = DataCellType::Int32_t;
    }
    void DataCell::setValue(int64_t value)
    {
        largeSigned = value;
        type = DataCellType::Int64_t;
    }
    void DataCell::setValue(float value, uint8_t decimalPrecision)
    {
        Float = value;
        this->decimalPrecision = decimalPrecision;
        type = DataCellType::Float;
    }
    void DataCell::setValue(double value, uint8_t decimalPrecision)
    {
        Double = value;
        this->decimalPrecision = decimalPrecision;
        type = DataCellType::Double;
    }
    void DataCell::setValue(long double value, uint8_t decimalPrecision)
    {
        largeDouble = value;
        this->decimalPrecision = decimalPrecision;
        type = DataCellType::LongDouble;
    }
    void DataCell::setValue(string value)
    {
        String = value;
        type = DataCellType::String;
    }
    
    #undef __class__
}