project('simplex-toolkit','cpp')

simplextk_inc = include_directories('include')

sources = files(
    'src/CFileWrapper.cpp',
    'src/Console.cpp',
    'src/ConsoleReader.cpp',
    'src/ConsoleWriter.cpp',
    'src/DataTable.cpp',
    'src/DateTime.cpp',
    'src/Exception.cpp',
    'src/FileReader.cpp',
    'src/FileSystem.cpp',
    'src/FileWriter.cpp',
    'src/Logger.cpp',
    'src/Singleton.cpp',
    'src/string.cpp', 
    'src/StringReader.cpp', 
    'src/StringWriter.cpp', 
    'src/SupportsSignals.cpp',
    'src/XmlWriter.cpp')

simplextk = library('libsimplextk', sources, include_directories:simplextk_inc)
simplextk_dep = declare_dependency(link_with: simplextk, include_directories:simplextk_inc)
