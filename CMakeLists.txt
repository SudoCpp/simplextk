cmake_minimum_required(VERSION 3.8.0)
project(simplextk VERSION 2.8.0)

#Debian Packages required
# none
set (CMAKE_CXX_STANDARD 17)

set(ProjectType STATIC) #options are SHARED and STATIC

set(Packages

    )

set(SubProjects

    ) 

#Add all the source files to build library
set(SourceFiles
    # src/ByteArray.cpp
    src/Console.cpp
    src/ConsoleReader.cpp
    src/ConsoleWriter.cpp
    src/DataCell.cpp
    src/DataRow.cpp
    src/DataTable.cpp
    src/DateTime.cpp
    # src/DynamicLibrary.cpp
    src/Exception.cpp
    src/FileReader.cpp
    src/FileSystem.cpp
    src/FileWriter.cpp
    src/Logger.cpp
    # src/MemoryReader.cpp
    # src/MemoryWriter.cpp
    src/Singleton.cpp
    src/string.cpp
    src/StringReader.cpp
    src/StringWriter.cpp
    src/SupportsSignals.cpp
    src/Thread.cpp
    src/ThreadManager.cpp
    src/TreeNode.cpp
    src/XmlReader.cpp
    # src/XmlTreeNode.cpp
    src/XmlWriter.cpp)

        #Tabbed over values do not need to be edited
        if(NOT TARGET ${PROJECT_NAME})
            add_library(${PROJECT_NAME} ${ProjectType} ${SourceFiles})
#target_link_libraries(${PROJECT_NAME} "-l_additional_libraries")
            # Unix systems required the dl library for dynamically loading libraries
            if (UNIX)
                target_link_libraries(${PROJECT_NAME} "-ldl")
            endif()

            if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                target_link_libraries(${PROJECT_NAME} "-lstdc++fs")
                target_link_libraries(${PROJECT_NAME} "-lpthread")
            endif()

            # Include files for this project
            include_directories("include")

            # Go through all the packages that are required. Find them, and add support.
            foreach(Package IN LISTS Packages)
                find_package(${Package} REQUIRED)
                include_directories(${${Package}_INCLUDE_DIRS})
                target_link_libraries(${PROJECT_NAME} ${${Package}_LIBRARIES})
            endforeach()

            # Add all subprojects. 
            foreach(Project IN LISTS SubProjects)
                # This is like an include guard on a header file, they can only be added once
                if(NOT TARGET ${Project})
                    add_subdirectory("../${Project}" ${Project})
                endif()
                include_directories("../${Project}")
                target_link_libraries(${PROJECT_NAME} ${Project})
            endforeach()

            if(EXISTS tests)
                include(CTest)
                enable_testing()
                #Add testing executables
                set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}/tests/${PROJECT_NAME}")
                add_subdirectory(tests)
                set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir})
            endif()
        endif()

        #set(CPACK_PROJECT_NAME ${PROJECT_NAME})
        #set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
        #include(CPack)