#include "FileSystem.hpp"
#include "Exception.hpp"

#include <sys/types.h>
#include <sys/stat.h>

#define __class__ "simplex::FileSystem"

namespace simplex::FileSystem
{
    bool exists(const string& path)
    {
        struct stat info;

        if(stat(path.toCString(), &info) != 0 )
            return false;
        else if(info.st_mode & S_IFDIR)
            return true;
        else
            return false;
    }

    string getExtension(const string& fullPath)
    {
        int position = fullPath.lastIndexOf(".");
        if(position == -1)
            throw Exception{"Invalid Path: "+fullPath, __ExceptionParams__};
        return fullPath.subString(position);
    }
}

#undef __class__