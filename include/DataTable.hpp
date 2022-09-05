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

#include "FormattingDecorations.hpp"

namespace simplex
{
    class DataRow : public object
    {
        Dictionary<string, string> columns;
        Array<string> columnNames;
        public:
        DataRow(in Dictionary<string, string> columnsAndData);
        DataRow(in Array<string> columnNames);
        DataRow(in Array<string> columnNames, in Array<string> columnValues);
        DataRow();

        Array<string> getColumnNames();
        DataRow& addColumn(in string name);
        DataRow& addColumn(in string name, in string value);
        string& getCell(in string name);
        string& getCell(in int32_t index);
        string getCell(in string name) const;
        string getCell(in int32_t index) const;
        string operator[](in int32_t index) const;
        string& operator[](in int32_t index);
        string operator[](in string columnName) const;
        string& operator[](in string columnName);
    };

    class DataTable : public object
    {
        Array<DataRow*> rows;
        Array<string> columnNames;
        public:
        DataTable();
        DataTable(in Array<string> columnNames);
        virtual ~DataTable();
        //Ownership is taken and auto deleted when DataTable is destructed
        DataTable& addRow(in ownership DataRow* row);
        DataTable& addRow(in const DataRow& row);
        DataTable& addRow(in const Array<string>& values);
        DataTable& addColumn(in string columnName);
        DataRow& getRow(in int32_t index);
        DataRow getRow(in int32_t index) const;
        DataRow operator[](in int32_t index) const;
        DataRow& operator[](in int32_t index);
    };
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_DATATABLE_HPP