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

#include "string.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    std::string convert{argv[1]};
    if(convert == "0")
    {
        simplex::string lowerCase{"test"};
        std::string upperCase{"TEST"};
        if(lowerCase.toUpper().toStdString() == upperCase)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "1")
    {
        simplex::string upperCase{"TEST"};
        std::string lowerCase{"test"};
        if(upperCase.toLower().toStdString() == lowerCase)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "2")
    {
        simplex::string testString{"TEST"};
        if(testString.length() == 4)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "3")
    {
        simplex::string testString{"ATESTTEST"};
        if(testString.indexOf("TEST") == 1)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "4")
    {
        simplex::string testString{"ATESTTEST"};
        if(testString.indexOf("TEST", 2) == 5)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "5")
    {
        simplex::string testString{"ATESTTESTA"};
        if(testString.lastIndexOf("TEST") == 5)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "6")
    {
        // simplex::string testString1{"TEST"};
        // simplex::String testString2
        // if()
            return EXIT_SUCCESS;
        // else
        //     return EXIT_FAILURE;
    }
    else if(convert == "7")
    {
        simplex::string testString{"ATESTTEST"};
        if(testString.contains("TEST"))
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "8")
    {
        simplex::string testString{"ATESTTEST"};
        if(testString.containsCount("TEST") == 2)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "9")
    {
        simplex::string string1{"Test"};
        simplex::string string2("ing");
        if((string1 + string2).toStdString() == std::string("Testing"))
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "10")
    {
        simplex::string string1{"Test"};
        if((string1 + "ing").toStdString() == std::string("Testing"))
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "11")
    {
        simplex::string string1{"Test"};
        if(string1.subString(1).toStdString() == std::string("est"))
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "12")
    {
        simplex::string string1{"Test"};
        if(string1.subString(1,2).toStdString() == std::string("es"))
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "13")
    {
        if(simplex::string{"  Test  "}.trim() == simplex::string{"Test"})
            return EXIT_SUCCESS;
        else
           return EXIT_FAILURE;
    }
    else if(convert == "14")
    {
        if(simplex::string::FromNumber(12) + simplex::string::FromNumber(34) == simplex::string{"1234"})
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else if(convert == "15")
    {
        float number = 12.34;
        if(simplex::string::FromNumber(number, 2) == simplex::string{"12.34"})
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;
    }
    else
    {
        //Invalid Test Case
        return EXIT_FAILURE;
    }
    
}