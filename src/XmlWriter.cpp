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

#include "XmlWriter.hpp"
#include "Exception.hpp"
#include "XmlReader.hpp"
#include "StringReader.hpp"

#define __class__ "simplex::XmlWriter"

namespace simplex
{
    XmlWriter::XmlWriter(StreamWriter &stream) : settings{}, stream(stream), levelDeep{0}, creatingElement{false}, valueAddedToElement{false} {}
    XmlWriter::XmlWriter(StreamWriter &stream, XmlWriterSettings settings) : settings{settings}, stream(stream), levelDeep{0}, creatingElement{false}, valueAddedToElement{false} {}

    XmlWriter::~XmlWriter() { close(); }

    void XmlWriter::close()
    {
        while (elements.size() > 0)
            createEndElement();
        stream.writeBuffer();
    }

    void XmlWriter::createElement(string elementName)
    {
        if (creatingElement)
            writeBuffer();
        creatingElement = true;
        buffer = indentation() + "<" + elementName;
        levelDeep++;
        elements.push(elementName);
    }

    void XmlWriter::createEndElement()
    {
        levelDeep--;
        if (creatingElement)
        {
            buffer += " />";
            stream.writeLine(buffer);
            creatingElement = false;
            buffer = "";
            elements.pop();
        }
        else if (elements.size() > 0)
        {
            if(!settings.valueOnNewLine && valueAddedToElement)
            {
                stream.writeLine("</" + elements.pop() + ">");
                valueAddedToElement = false;
            }
            else
                stream.writeLine(indentation() + "</" + elements.pop() + ">");
        }
        else
            throw IndexOutOfBoundsException{"No elements left to end.", __ExceptionParams__};
    }

    void XmlWriter::addAttribute(const string &attributeName, const string &attributeValue)
    {
        if (!creatingElement)
            throw Exception{"An Element is not being created. Can not add attribute: " + attributeName, __ExceptionParams__};
        else
            buffer += " " + attributeName + "=\"" + attributeValue + "\"";
    }

    void XmlWriter::addAttributes(const Dictionary<string, string> &attributes)
    {
        for (std::pair<string, string> attribute : attributes)
            addAttribute(attribute.first, attribute.second);
    }

    void XmlWriter::addValue(const string &value)
    {
        if(settings.valueOnNewLine)
        {
            if (creatingElement)
                writeBuffer();
            stream.writeLine(indentation() + value);
        }
        else
        {
            if(creatingElement)
            {
                buffer += ">";
                stream.write(buffer);
                creatingElement = false;
                buffer = "";
            }
            stream.write(value);
            valueAddedToElement = true;
        }
    }

    void XmlWriter::writeBuffer()
    {
        buffer += ">";
        stream.writeLine(buffer);
        creatingElement = false;
        buffer = "";
    }

    string XmlWriter::indentation()
    {
        string indentation = "";
        for (int loop = 0; loop < levelDeep; loop++)
            indentation += settings.indentionCharacters;
        return indentation;
    }

    void XmlWriter::writeXMLDeclaration()
    {
        stream.writeLine("<?xml version=\"" + settings.xmlVersionNumber + "\" encoding=\"" + (settings.xmlEncoding == XmlEncoding::utf8 ? "utf-8" : "utf-16") + "\" ?>");
    }

    void XmlWriter::addXMLString(const string &xml)
    {
        StringReader readerString{xml};
        XmlReader reader{readerString};
        while(reader.read())
        {
            if(reader.isStartElement)
            {
                createElement(reader.name);
                if(reader.attributes.size() > 0)
                    addAttributes(reader.attributes);
            }
            else
                createEndElement();
        }
    }
}

#undef __class__