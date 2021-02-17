cmake_minimum_required(VERSION 3.0.0)
project(simplex-toolkit VERSION 1.0.0)

    #Determine if 32 or 64 bit
    set(OSBitness 32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
    endif()

    #Save outputs into bin folder
    set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FullOutputDir})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir})

    #Add Parent Directory so that other libraries can be easily found
    include_directories("include")
    include_directories("..")

#Add all the source files to build library
set(SourceFiles
    src/Console.cpp
    src/ConsoleReader.cpp
    src/ConsoleWriter.cpp
    src/Exception.cpp
    src/string.cpp
    src/StringReader.cpp
    src/StringWriter.cpp
    src/SupportsSignals.cpp)

    add_library(${PROJECT_NAME} SHARED ${SourceFiles})

    include(CTest)
    enable_testing()
    #Add testing executables
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}/tests/${PROJECT_NAME}")
    add_subdirectory(tests)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir})

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)