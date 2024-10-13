cmake_minimum_required(VERSION 3.22.1)
project(spyMaster3000
  VERSION 0.0.1
  DESCRIPTION "Tool for the utlimate spy."
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch googleTest as git submodule
include(cmake/updateSubmodules.cmake)

include(CTest)
add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(tests)
