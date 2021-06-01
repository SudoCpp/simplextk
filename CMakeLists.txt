cmake_minimum_required(VERSION 3.0.0)
project(simplex-toolkit VERSION 2.8.0)

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
    src/Common/CFileWrapper.cpp
    src/Common/Console.cpp
    src/Common/ConsoleReader.cpp
    src/Common/ConsoleWriter.cpp
    src/Common/DataTable.cpp
    src/Common/DateTime.cpp
    src/Common/Exception.cpp
    src/Common/FileReader.cpp
    src/Common/FileSystem.cpp
    src/Common/FileWriter.cpp
    src/Common/Logger.cpp
    src/Common/Singleton.cpp
    src/Common/string.cpp
    src/Common/StringReader.cpp
    src/Common/StringWriter.cpp
    src/Common/SupportsSignals.cpp
    src/Common/XmlWriter.cpp)

    add_library(${PROJECT_NAME} SHARED ${SourceFiles})
    
    #Set up links for all dependancies
    set (${PROJECT_NAME}_LIBS "m")

    #Link the libraries
    target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})

    include(CTest)
    enable_testing()
    #Add testing executables
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}/tests/${PROJECT_NAME}")
    add_subdirectory(tests)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir})

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)