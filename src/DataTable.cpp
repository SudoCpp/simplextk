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
#include "FileReader.hpp"
#include "FileWriter.hpp"

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
            int32_t numberColumns = columnNames.size();
            for(int32_t loop = 0; loop < numberColumns; loop++)
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

    string& DataRow::getCell(int32_t index)
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

    string DataRow::getCell(int32_t index) const
    {
        if(columnNames.size() > index)
            return columns.at(columnNames[index]);
        else
            throw IndexOutOfBoundsException("Unable to get cell, index out of bounds.", __ExceptionParams__);
    }

    string DataRow::operator[](int32_t index) const
    {
        return getCell(index);
    }

    string& DataRow::operator[](int32_t index)
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
    DataTable::DataTable() : rows{true} {}
    DataTable::DataTable(Array<string> columnNames) : rows{true}, columnNames{columnNames} {}
    DataTable::~DataTable()
    { }

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
        columnNames.add(columnName);
        for (auto row : rows)
            row->addColumn(columnName);
        return *this;
    }
    DataRow& DataTable::getRow(int32_t index)
    {
        return *rows[index];
    }
    DataRow DataTable::getRow(int32_t index) const
    {
        return *rows[index];
    }
    Array<string> DataTable::getColumnNames() const
    {
        return columnNames;
    }
    Array<DataRow *> DataTable::getRows()
    {
        return rows;
    }
    DataRow DataTable::operator[](int32_t index) const
    {
        return getRow(index);
    }
    DataRow& DataTable::operator[](int32_t index)
    {
        return getRow(index);
    }
    DataTable& DataTable::exportToCSV(StreamWriter& writer)
    {
        int numCols = columnNames.size();
        for (int loop = 0; loop < numCols; loop++)
            writer.write(convertToCSV(columnNames[loop], loop));
        writer.write("\n");
        
        for (DataRow *row : rows)
        {
            for(int loop = 0; loop < numCols; loop++)
                writer.write(convertToCSV(row->getCell(columnNames[loop]), loop));
            writer.write("\n");
        }
        return *this;
    }
    DataTable *DataTable::ImportFromCSV(StreamReader &reader)
    {
        DataTable *table = new DataTable{};
        string line;
        Array<string> fields{};
        bool headerComplete = false;
        string fieldValue = "";
        bool inQuote = false;
        bool lastCharacterQuote = false;
        string quotedText = "";
        while (reader.readLine(line))
        {
            int lineLength = line.length();
            for (int loop = 0; loop < lineLength; loop++)
            {
                if (line[loop] == '"' && lastCharacterQuote)
                {
                    inQuote = !inQuote;
                    lastCharacterQuote = false;
                    fieldValue += '"';
                }
                else if(line[loop] == '"')
                {
                    inQuote = !inQuote;
                    lastCharacterQuote = true;
                } 
                else 
                {
                    lastCharacterQuote = false;
                    if (line[loop] == ',' && !inQuote)
                    {
                        fields.add(fieldValue);
                        fieldValue = "";
                    }
                    else
                        fieldValue += line[loop];
                }
            }
            fields.add(fieldValue);
            fieldValue = "";

            if(!headerComplete)
            {
                headerComplete = true;
                for(string field : fields)
                    table->addColumn(field);
            }
            else
                table->addRow(fields);
            fields.clear();
        }
        return table;
    }
    string DataTable::convertToCSV(string field, int loop)
    {
        field = field.replace("\"", "\"\"");
        if (field.contains(","))
            field = "\"" + field + "\"";
        if (loop != 0)
            field = "," + field;
        return field;
    }
#undef __class__
}