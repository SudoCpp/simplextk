cmake_minimum_required(VERSION 3.0.0)
project(simplex-toolkit VERSION 1.0.0)

    #Add Parent Directory so that other libraries can be easily found
    include_directories("include")
    include_directories("..")

#Add all the source files to build library
set(SourceFiles
    src/string.cpp)

    add_library(${PROJECT_NAME} SHARED ${SourceFiles})

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)