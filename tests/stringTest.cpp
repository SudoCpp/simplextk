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
    // else if(convert == "6")
    // {
    //     simplex::string testString{"ATESTTEST"};
    //     if(testString.lastIndexOf("TEST", 9) == 2)
    //         return EXIT_SUCCESS;
    //     else
    //         return EXIT_FAILURE;
    // }
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
        //if(simplex::string{"Test"}.toString() == simplex::string{"Test"})
            return EXIT_SUCCESS;
        //else
          //  return EXIT_FAILURE;
    }
    else if(convert == "14")
    {
        if(simplex::string::FromNumber(12) + simplex::string::FromNumber(34) == simplex::string{"1234"})
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