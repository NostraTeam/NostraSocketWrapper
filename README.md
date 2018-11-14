# NostraSocketWrapper
A C wrapper for POSIX and Windows sockets.

GitHub: https://github.com/NostraTeam/NostraSocketWrapper

## Requirements

In order to build the library the following things are required:
- A compiler that supports C99 higher (see below for a list of compilers that were tested)
- CMake 3.8.2 or higher (https://cmake.org/)
- A build system supported by CMake (e.g. Make, Ninja or Visual Studio) 
- Optional: Doxygen (http://www.doxygen.nl/) and Graphviz (https://www.graphviz.org/) and a LaTeX compiler 
  (used to build the documentation)

The supported compilers are:
- MSVC (the Visual Studio Compiler)
- GCC
- Clang

The supported operating systems are:
- MS Windows (including MinGW and Cygwin)
- Linux
