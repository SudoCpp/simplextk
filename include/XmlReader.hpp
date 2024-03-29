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

#ifndef SIMPLEX_XMLREADER_HPP
#define SIMPLEX_XMLREADER_HPP

#include "Array.hpp"
#include "StreamReader.hpp"
#include "string.hpp"
#include "Dictionary.hpp"

#include "FormattingDecorations.hpp"

namespace simplex
{
    class XmlReader : public object
    {
        public:
        XmlReader(in StreamReader& stream);
        bool read();

        string name;
        string value;
        Dictionary<string, string> attributes;
        bool isStartElement;
        bool isValue;
        
        private:
        void addAttribute(in string name, in string value);

        StreamReader& stream;
        bool inElement;
        bool nameComplete;
        bool readingElement;
        string attributeName;
        string attributeValue;
        bool attributeNameComplete;
        bool attributeValueComplete;
        bool beginQuote;
        string nextName;
        bool nextIsEnd;
    };
}

#include "EndFormattingDecorations.hpp"

#endif //SIMPLEX_XMLREADER_HPP