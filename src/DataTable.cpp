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
    #define __class__ "simplex::DataTable"
 template<>
    DataTable& DataTable::addColumn<void*>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Pointer);
        for (auto row : rows)
            row->addColumn<void*>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<uint8_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Uint8_t);
        for (auto row : rows)
            row->addColumn<uint8_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<uint16_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Uint16_t);
        for (auto row : rows)
            row->addColumn<uint16_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<uint32_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Uint32_t);
        for (auto row : rows)
            row->addColumn<uint32_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<uint64_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Uint64_t);
        for (auto row : rows)
            row->addColumn<uint64_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<int8_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Int8_t);
        for (auto row : rows)
            row->addColumn<int8_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<int16_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Int16_t);
        for (auto row : rows)
            row->addColumn<int16_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<int32_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Int32_t);
        for (auto row : rows)
            row->addColumn<int32_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<int64_t>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Int64_t);
        for (auto row : rows)
            row->addColumn<int64_t>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<float>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Float);
        for (auto row : rows)
            row->addColumn<float>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<double>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::Double);
        for (auto row : rows)
            row->addColumn<double>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<long double>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::LongDouble);
        for (auto row : rows)
            row->addColumn<long double>(columnName);
        return *this;
    }
    template<>
    DataTable& DataTable::addColumn<string>(string columnName)
    {
        columnNames.add(columnName);
        columnTypes.add(DataCellType::String);
        for (auto row : rows)
            row->addColumn<string>(columnName);
        return *this;
    }

    DataTable::DataTable() : rows{true} {}
    DataTable::DataTable(Array<string> columnNames) : rows{true}, columnNames{columnNames} {}
    DataTable::~DataTable()
    { }

    DataTable& DataTable::addRow(DataRow* row)
    {
        if (row->columnTypes.size() == columnTypes.size())
        {
            uint8_t numColumnTypes = columnTypes.size();
            for(int loop = 0; loop < numColumnTypes; loop++)
                if(row->columnTypes[loop] != columnTypes[loop])
                    throw Exception("Column types don't match between row and DataTable.", __ExceptionParams__);
            rows.add(row);
            return *this;
        }
        else
            throw Exception("Row doesn't have enough columns to match DataTable.", __ExceptionParams__);
    }
    DataTable& DataTable::addRow(const DataRow& row)
    {
        if (row.columnTypes.size() == columnTypes.size())
        {
            uint8_t numColumnTypes = columnTypes.size();
            for(int loop = 0; loop < numColumnTypes; loop++)
                if(row.columnTypes[loop] != columnTypes[loop])
                    throw Exception("Column types don't match between row and DataTable.", __ExceptionParams__);
            DataRow* temp = new DataRow{row};
            rows.add(temp);
            return *this;
        }
        else
            throw Exception("Row doesn't have enough columns to match DataTable.", __ExceptionParams__);
    }
    DataTable& DataTable::addRow(const Array<DataCell>& values)
    {
        if (values.size() == columnTypes.size())
        {
            uint8_t numColumnTypes = columnTypes.size();
            for(int loop = 0; loop < numColumnTypes; loop++)
                if(values[loop].type != columnTypes[loop])
                {
                    tempCells.clear();
                    throw Exception("DataCell types don't match types in DataTable.", __ExceptionParams__);
                }
            try
            {
                rows.add(new DataRow{columnNames, values});
            }
            catch (Exception ex)
            {
                tempCells.clear();
                throw;
            }
            return *this;
        }
         else
         {
            tempCells.clear();
            throw Exception("Number of DataCells in array don't match DataTable.", __ExceptionParams__);
         }
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
                writer.write(convertToCSV(row->getCell(columnNames[loop]).getValue<string>(), loop));
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
                    table->addColumn<string>(field);
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
    string DataTable::DataCellTypeAsString(DataCellType type)
    {
        if(type == DataCellType::Uint8_t)
            return "uint8_t";
        else if(type == DataCellType::Uint16_t)
            return "uint16_t";
        else if(type == DataCellType::Uint32_t)
            return "uint32_t";
        else if(type == DataCellType::Uint64_t)
            return "uint64_t";
        else if(type == DataCellType::Int8_t)
            return "int8_t";
        else if(type == DataCellType::Int16_t)
            return "int16_t";
        else if(type == DataCellType::Int32_t)
            return "int32_t";
        else if(type == DataCellType::Int64_t)
            return "int64_t";
        else if(type == DataCellType::Float)
            return "float";
        else if(type == DataCellType::Double)
            return "double";
        else if(type == DataCellType::LongDouble)
            return "long double";
        else if(type == DataCellType::String)
            return "string";
        else if(type == DataCellType::Pointer)
            return "void*";
        else
            return "not set";
    }

#undef __class__
}