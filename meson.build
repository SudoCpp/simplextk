project('siplex-toolkit','cpp')

simplex_inc = include_directories('include')

sources = files('src/Common/CFileWrapper.cpp',
    'src/Common/Console.cpp',
    'src/Common/ConsoleReader.cpp',
    'src/Common/ConsoleWriter.cpp',
    'src/Common/DataTable.cpp',
    'src/Common/DateTime.cpp',
    'src/Common/Exception.cpp',
    'src/Common/FileReader.cpp',
    'src/Common/FileSystem.cpp',
    'src/Common/FileWriter.cpp',
    'src/Common/Logger.cpp',
    'src/Common/Singleton.cpp',
    'src/Common/string.cpp', 
    'src/Common/StringReader.cpp', 
    'src/Common/StringWriter.cpp', 
    'src/Common/SupportsSignals.cpp',
    'src/Common/XmlWriter.cpp')

simplextk = library('libsimplex', sources, include_directories:simplex_inc)
simplex_dep = declare_dependency(link_with: simplextk, include_directories:simplex_inc)
