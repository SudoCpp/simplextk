/*
    BSD 3-Clause License
    
    Copyright (c) 2021, SudoCpp
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

namespace simplex
{
    class DataRow : public object
    {
        Dictionary<string, string> Columns;
        Array<string> ColumnNames;
        public:
        DataRow(Dictionary<string, string> columnsAndData);
        DataRow(Array<string> columnNames);
        DataRow(Array<string> columnNames, Array<string> columnValues);
        DataRow();

        Array<string> getColumnNames();
        void addColumn(string name);
        void addColumn(string name, string value);
        string& getCell(string name);
        string& getCell(int index);
        string getCell(string name) const;
        string getCell(int index) const;
        string operator[](int index) const;
        string& operator[](int index);
        string operator[](string columnName) const;
        string& operator[](string columnName);
    };

    class DataTable : public object
    {
        Array<DataRow> Rows;
        Array<string> ColumnNames;
        public:
        DataTable();
        DataTable(Array<string> columnNames);
        void addRow(DataRow row);
        void addRow(Array<string> values);
        void addColumn(string columnName);
        DataRow& getRow(int index);
        DataRow getRow(int index) const;
        DataRow operator[](int index) const;
        DataRow& operator[](int index);
    };
}

#endif //SIMPLEX_DATATABLE_HPP