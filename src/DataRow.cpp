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

#include "DataRow.hpp"
#include "Exception.hpp"

namespace simplex
{
    #define __class__ "simplex::DataRow"

    template<>
    DataRow& DataRow::addColumn<void*>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Pointer);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<uint8_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Uint8_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<uint16_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Uint16_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<uint32_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Uint32_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<uint64_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Uint64_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<int8_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Int8_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<int16_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Int16_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<int32_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Int32_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<int64_t>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Int64_t);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<float>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Float);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<double>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::Double);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<long double>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::LongDouble);
        return *this;
    }
    template<>
    DataRow& DataRow::addColumn<string>(string name)
    {
        columnNames.add(name);
        columnTypes.add(DataCellType::String);
        return *this;
    }

    DataRow::DataRow(Dictionary<string, DataCell> columnsAndData) : columns{columnsAndData} {}
    DataRow::DataRow(Array<string> columnNames)
    {
        for(auto name : columnNames)
            columns.add(name, DataCell{""});
    }
    DataRow::DataRow(Array<string> columnNames, Array<DataCell> columnValues)
    {
        if(columnNames.size() == columnValues.size())
        {
            int32_t numberColumns = columnNames.size();
            for(int32_t loop = 0; loop < numberColumns; loop++)
            {
                columns.add(columnNames[loop], columnValues[loop]);
                this->columnNames.add(columnNames[loop]);
            }
        }
        else
            throw Exception("Mismatch: There are not the same amount of columns and values.", __ExceptionParams__);
    }
    DataRow::DataRow(){}

    Array<string> DataRow::getColumnNames()
    {
        return columnNames;
    }

    DataRow& DataRow::addColumn(string name, string value)
    {
        if(!columnNames.contains(name))
        {
            columnNames.add(name);
            columns.add(name, value);
            return *this;
        }
        else
            throw Exception("Column Names must be unique. A column name '" + name + "' already exists.", __ExceptionParams__);
    }

    DataCell& DataRow::getCell(string name)
    {
        return columns[name];
    }

    DataCell& DataRow::getCell(int32_t index)
    {
        if(columnNames.size() > index)
            return columns.at(columnNames[index]);
        else
            throw IndexOutOfBoundsException("Unable to get cell, index out of bounds.", __ExceptionParams__);
    }

    DataCell DataRow::getCell(string name) const
    {
        return columns[name];
    }

    DataCell DataRow::getCell(int32_t index) const
    {
        if(columnNames.size() > index)
            return columns.at(columnNames[index]);
        else
            throw IndexOutOfBoundsException("Unable to get cell, index out of bounds.", __ExceptionParams__);
    }

    DataCell DataRow::operator[](int32_t index) const
    {
        return getCell(index);
    }

    DataCell& DataRow::operator[](int32_t index)
    {
        return getCell(index);
    }

    DataCell DataRow::operator[](string columnName) const
    {
        return getCell(columnName);
    }
    
    DataCell& DataRow::operator[](string columnName)
    {
        return getCell(columnName);
    }
    #undef __class__
}