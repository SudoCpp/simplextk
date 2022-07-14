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

#include "XmlReader.hpp"
#include "Exception.hpp"

#define __class__ "simplex::XmlReader"

namespace simplex
{
    XmlReader::XmlReader(StreamReader &stream) : stream{stream}, nextIsEnd{false} {}

    bool XmlReader::read()
    {
        string character;
        value = "";
        name = "";
        inElement = false;
        isValue = true;
        readingElement = false;
        attributes = Dictionary<string, string>{};
        attributeNameComplete = false;
        attributeValueComplete = false;
        beginQuote = false;
        isStartElement = false;
        attributeName = "";
        attributeValue = "";
        if (nextIsEnd)
        {
            name = nextName;
            nextIsEnd = false;
            return true;
        }

        for (int32_t loop = 0; stream.readString(character, 1); loop++)
        {
            if (character == "<")
            {
                isValue = false;
                nameComplete = false;
                readingElement = true;
                isStartElement = true;
                value = "";
            }
            else
            {
                if (character == "/" && !nameComplete)
                {
                    isStartElement = false;
                    continue;
                }
                else if (character == "/" && !beginQuote && nameComplete)
                {
                    nextIsEnd = true;
                    nextName = name;
                    continue;
                }

                if (readingElement)
                {
                    if (character == ">")
                    {
                        if (attributeName != "")
                            addAttribute(attributeName, attributeValue);
                        return true;
                    }
                    else if (!nameComplete)
                    {
                        if (character == " ")
                            nameComplete = true;
                        else
                            name += character;
                    }
                    else if (!attributeNameComplete)
                    {
                        if (character != "=")
                            attributeName += character;
                        else
                            attributeNameComplete = true;
                    }
                    else
                    {
                        if (character == "\"")
                        {
                            beginQuote = beginQuote ? false : true;
                            if (!beginQuote)
                            {
                                attributeNameComplete = true;
                                attributeValueComplete = true;
                                addAttribute(attributeName, attributeValue);
                            }
                        }
                        else if (character == " " && !beginQuote)
                        {
                            attributeNameComplete = false;
                            attributeValueComplete = false;
                            attributeName = "";
                            attributeValue = "";
                        }
                        else
                            attributeValue += character;
                    }
                }
                else if (character == "<")
                {
                    stream.rewind(1);
                    break;
                }
                else
                    value += character;
            }
        }
        
        value = value.trim();
        if(value != "")
            return true;
        else
            return false;
    }

    void XmlReader::addAttribute(string name, string value)
    {
        if (!attributes.containsKey(name))
            attributes.add(name, value);
    }
}

#undef __class__