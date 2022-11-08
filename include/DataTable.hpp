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

#ifndef SIMPLEX_DATATABLE_HPP
#define SIMPLEX_DATATABLE_HPP

#include "object.hpp"
#include "string.hpp"
#include "Dictionary.hpp"
#include "Array.hpp"
#include "StreamReader.hpp"
#include "StreamWriter.hpp"
#include "DataCell.hpp"
#include "DataRow.hpp"

#include "FormattingDecorations.hpp"

namespace simplex
{
    #define __class__ "simplex::DataTable"
    class DataTable : public object
    {
        Array<DataRow*> rows;
        Array<string> columnNames;
        Array<DataCellType> columnTypes;

        Array<DataCell> tempCells;

        DataTable& addRow()
        {
            addRow(tempCells);
            tempCells.clear();

            return *this;
        }

        public:
        DataTable();
        DataTable(in Array<string> columnNames);
        virtual ~DataTable();
        //Ownership is taken and auto deleted when DataTable is destructed
        DataTable& addRow(in ownership DataRow* row);
        DataTable& addRow(in const DataRow& row);
        DataTable& addRow(in const Array<DataCell>& values);
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<uint8_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Uint8_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }

                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<uint16_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Uint16_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<uint32_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Uint32_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<uint64_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Uint64_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<int8_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Int8_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<int16_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Int16_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<int32_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Int32_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<int64_t, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Int64_t)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<float, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Float)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<double, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::Double)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<long double, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::LongDouble)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<string, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::String)
                    tempCells.add(DataCell{columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        template<typename ColumnType, typename ...Args, std::enable_if_t<std::is_same<const char*, ColumnType>::value, bool> = true>
        DataTable& addRow(ColumnType columnValue1, Args... args)
        {
            uint8_t tempCellsSize = tempCells.size();
            if(tempCellsSize < columnNames.size())
            {
                if(columnTypes[tempCellsSize] == DataCellType::String)
                    tempCells.add(DataCell{(string)columnValue1});
                else
                {
                    tempCells.clear();
                    throw Exception("Trying to add a cell with wrong type to DataRow.", __ExceptionParams__);
                }


                addRow(args...);
            }
            else
            {
                tempCells.clear();
                throw Exception("Trying to add too many values, not enough columns.", __ExceptionParams__);
            }

            return *this;
        }
        
        
        template<typename columnType>
        DataTable& addColumn(string columnName);
        
        Array<string> getColumnNames() const;
        DataRow& getRow(in int32_t index);
        DataRow getRow(in int32_t index) const;
        Array<DataRow *> getRows();
        DataRow operator[](in int32_t index) const;
        DataRow& operator[](in int32_t index);
        DataTable& exportToCSV(inout StreamWriter &writer);

        static DataTable *ImportFromCSV(inout StreamReader& reader);

        private:
            string convertToCSV(in string field, int loop);
    };
    #undef __class__
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_DATATABLE_HPP