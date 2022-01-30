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

#include "Array.hpp"
#include <string>
#include <vector>

#define __class__ "Global"

int32_t main(int32_t argc, char* argv[])
{
    std::string convert{argv[1]};
    if(convert == "0")
    {
        simplex::Array<std::string> test{ "a", "b", "c" };
        if (test[1] == "b")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "1")
    {
        std::vector<std::string> vec{"a", "b", "c" };
        simplex::Array<std::string> test{vec};
        if (test.at(1) == "b")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "2")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        if (test.at(1) == "b")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "3")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c", 0);
        if (test.at(1) == "a")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "4")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        std::vector<std::string> vec = test.toVector();
        if (vec[1] == "b")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "5")
    {
        std::vector<std::string> test{};
        test.push_back("a");
        test.push_back("b");
        test.push_back("c");
        simplex::Array<std::string> vec = simplex::Array<std::string>::FromVector(test);
        if (vec[1] == "b")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "6")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        if (test.contains("b"))
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "7")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        test.add("c");
        if (test.containsCount("c") == 2)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "8")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        test.add("c");
        if (test.indexOf("c") == 2)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "9")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        test.add("c");
        if (test.lastIndexOf("c") == 3)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "10")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        test.add("c");
        test.pop();
        if (test.lastIndexOf("c") == 2)
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "11")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        test.add("d");
        if (test.pop() == "d")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "12")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("b");
        test.add("c");
        test.add("d");
        test.reverse();
        if (test[0] == "d")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "13")
    {
        simplex::Array<std::string> test{};
        test.add("a");
        test.add("c");
        test.add("b");
        test.add("d");
        test.sort();
        if (test[2] == "c")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "14")
    {
        simplex::Array<std::string> test{};
        test.add("b");
        test.add("a",0);
        if (test[0] == "a")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "15")
    {
        simplex::Array<std::string> test{};
        test.add("b");
        test.add("a",0);
        if (test[1] == "b")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "16")
    {
        simplex::Array<std::string> test{"a","b"};
        simplex::Array<std::string> test1{"c","d"};
        test.add(test1);
        if (test[2] == "c")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
    else if(convert == "17")
    {
        simplex::Array<std::string> test{"a","b"};
        test.add({"c","d"});
        if (test[2] == "c")
            return EXIT_SUCCESS;
        else
            return EXIT_FAILURE;   
    }
}

#undef __class__