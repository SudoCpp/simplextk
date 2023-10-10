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

#ifndef SIMPLEX_DATAROW_HPP
#define SIMPLEX_DATAROW_HPP

#include "object.hpp"
#include "string.hpp"
#include "Dictionary.hpp"
#include "Array.hpp"
#include "DataCell.hpp"

#include "FormattingDecorations.hpp"

namespace simplex
{
    class DataTable;
    class DataRow : public object
    {
        Dictionary<string, DataCell> columns;
        Array<string> columnNames;

        _internal:
        Array<DataCellType> columnTypes;

        public:
        DataRow(in Dictionary<string, DataCell> columnsAndData);
        DataRow(in Array<string> columnNames);
        DataRow(in Array<string> columnNames, in Array<DataCell> columnValues);
        DataRow();

        Array<string> getColumnNames();
        template<typename cellType>
        DataRow& addColumn(in string name);

        DataRow& addColumn(in string name, in ownership void* value, in size_t sizeOfValueInBytes);
        DataRow& addColumn(in string name, in uint8_t value);
        DataRow& addColumn(in string name, in uint16_t value);
        DataRow& addColumn(in string name, in uint32_t value);
        DataRow& addColumn(in string name, in uint64_t value);
        DataRow& addColumn(in string name, in int8_t value);
        DataRow& addColumn(in string name, in int16_t value);
        DataRow& addColumn(in string name, in int32_t value);
        DataRow& addColumn(in string name, in int64_t value);
        DataRow& addColumn(in string name, in float value, in uint8_t decimalPrecision);
        DataRow& addColumn(in string name, in double value, in uint8_t decimalPrecision);
        DataRow& addColumn(in string name, in long double value, in uint8_t decimalPrecision);
        DataRow& addColumn(in string name, in string value);
        DataCell& getCell(in string name);
        DataCell& getCell(in int32_t index);
        DataCell getCell(in string name) const;
        DataCell getCell(in int32_t index) const;
        DataCell operator[](in int32_t index) const;
        DataCell& operator[](in int32_t index);
        DataCell operator[](in string columnName) const;
        DataCell& operator[](in string columnName);
    };
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_DATAROW_HPP