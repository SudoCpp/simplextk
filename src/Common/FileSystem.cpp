#include "FileSystem.hpp"
#include "Exception.hpp"

#define __class__ "simplex::FileSystem"

namespace simplex::FileSystem
{
    string getExtension(string fullPath)
    {
        int position = fullPath.lastIndexOf(".");
        if(position == -1)
            throw Exception{"Invalid Path: "+fullPath, __ExceptionParams__};
        return fullPath.subString(position);
    }
}

#undef __class__