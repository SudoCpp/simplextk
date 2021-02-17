#include "Array.hpp"
#include <string>
#include <vector>

#define __class__ "Global"

int main(int argc, char* argv[])
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
        if (test.popAndReturn() == "d")
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