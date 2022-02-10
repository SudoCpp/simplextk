cmake_minimum_required(VERSION 3.0.0)
project(simplextk VERSION 2.8.0)
#Add Parent Directory so that other libraries can be easily found
include_directories("include")
include_directories("..")

#Add all the source files to build library
set(SourceFiles
    src/Console.cpp
    src/ConsoleReader.cpp
    src/ConsoleWriter.cpp
    src/DataTable.cpp
    src/DateTime.cpp
    src/Exception.cpp
    src/FileReader.cpp
    src/FileSystem.cpp
    src/FileWriter.cpp
    src/Logger.cpp
    src/Singleton.cpp
    src/string.cpp
    src/StringReader.cpp
    src/StringWriter.cpp
    src/SupportsSignals.cpp
   # src/TreeNode.cpp
   # src/XmlReader.cpp
   # src/XmlTreeNode.cpp
    src/XmlWriter.cpp)

if(NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} STATIC ${SourceFiles})
endif()

include(CTest)
enable_testing()
#Add testing executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}/tests/${PROJECT_NAME}")
add_subdirectory(tests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir})

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)