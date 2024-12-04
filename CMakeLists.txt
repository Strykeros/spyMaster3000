cmake_minimum_required(VERSION 3.22.1)
project(spyMaster3000
  VERSION 0.0.1
  DESCRIPTION "Tool for the utlimate spy."
  LANGUAGES CXX)

# For LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(outputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${outputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${outputDir}")

# Fetch googleTest as git submodule
include(cmake/updateSubmodules.cmake)

# include(CTest)
add_subdirectory(src)
# add_subdirectory(external)
# add_subdirectory(tests)
