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

#include "DataTable.hpp"
#include "Exception.hpp"

namespace simplex
{
    #define __class__ "simplex::DataRow"

    DataRow::DataRow(Dictionary<string, string> columnsAndData) : columns{columnsAndData} {}
    DataRow::DataRow(Array<string> columnNames)
    {
        for(auto name : columnNames)
            columns.add(name, "");
    }
    DataRow::DataRow(Array<string> columnNames, Array<string> columnValues)
    {
        if(columnNames.size() == columnValues.size())
        {
            int numberColumns = columnNames.size();
            for(int loop = 0; loop < numberColumns; loop++)
                columns.add(columnNames[loop], columnValues[loop]);
        }
        else
            throw Exception("Mismatch: There are not the same amount of columns and values.", __ExceptionParams__);
    }
    DataRow::DataRow(){}

    Array<string> DataRow::getColumnNames()
    {
        return columnNames;
    }

    DataRow& DataRow::addColumn(string name)
    {
        return addColumn(name, "");
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

    string& DataRow::getCell(string name)
    {
        return columns[name];
    }

    string& DataRow::getCell(int index)
    {
        if(columnNames.size() > index)
            return columns.at(columnNames[index]);
        else
            throw IndexOutOfBoundsException("Unable to get cell, index out of bounds.", __ExceptionParams__);
    }

    string DataRow::getCell(string name) const
    {
        return columns[name];
    }

    string DataRow::getCell(int index) const
    {
        if(columnNames.size() > index)
            return columns.at(columnNames[index]);
        else
            throw IndexOutOfBoundsException("Unable to get cell, index out of bounds.", __ExceptionParams__);
    }

    string DataRow::operator[](int index) const
    {
        return getCell(index);
    }

    string& DataRow::operator[](int index)
    {
        return getCell(index);
    }

    string DataRow::operator[](string columnName) const
    {
        return getCell(columnName);
    }
    
    string& DataRow::operator[](string columnName)
    {
        return getCell(columnName);
    }
    #undef __class__
    #define __class__ "simplex::DataTable"
    DataTable::DataTable(){}
    DataTable::DataTable(Array<string> columnNames) : columnNames{columnNames} {}
    DataTable::~DataTable()
    {
        for(DataRow* row : rows)
            delete row;
    }
    DataTable& DataTable::addRow(DataRow* row)
    {
        rows.add(row);
        return *this;
    }
    DataTable& DataTable::addRow(const DataRow& row)
    {
        DataRow* temp = new DataRow{row};
        rows.add(temp);
        return *this;
    }
    DataTable& DataTable::addRow(const Array<string>& values)
    {
        rows.add(new DataRow{columnNames, values});
        return *this;
    }
    DataTable& DataTable::addColumn(string columnName)
    {
        for(auto row : rows)
            row->addColumn(columnName);
        return *this;
    }
    DataRow& DataTable::getRow(int index)
    {
        return *rows[index];
    }
    DataRow DataTable::getRow(int index) const
    {
        return *rows[index];
    }
    DataRow DataTable::operator[](int index) const
    {
        return getRow(index);
    }
    DataRow& DataTable::operator[](int index)
    {
        return getRow(index);
    }
    #undef __class__
}