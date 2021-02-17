#include "Exception.hpp"
#include <string>

#define __class__ "Global"

int main(int argc, char* argv[])
{
    std::string convert{argv[1]};
    if(convert == "0")
    {
        try
        {
            throw simplex::Exception{"Testing", __ExceptionParams__};
            return 1;
        }
        catch(const simplex::Exception& ex)
        {
            return 0;
        }
    }
    else if(convert == "1")
    {
        try
        {
            throw simplex::IndexOutOfBoundsException{"Testing", __ExceptionParams__};
            return 1;
        }
        catch(const simplex::Exception& ex)
        {
            return 0;
        }
    }
    else if(convert == "2")
    {
        try
        {
            throw simplex::NotImplementedException{__ExceptionParams__};
            return 1;
        }
        catch(const simplex::Exception& ex)
        {
            return 0;
        }
    }
    else if(convert == "3")
    {
        try
        {
            throw simplex::NullException{"Testing", __ExceptionParams__};
            return 1;
        }
        catch(const simplex::Exception& ex)
        {
            return 0;
        }
    }
}

#undef __class__