include_directories(${CMAKE_SOURCE_DIR}/src/algos)
include_directories(${CMAKE_SOURCE_DIR}/src/util)

set(SOURCES
  main.cpp
  algos/des.cpp
  algos/caeser.cpp
  algos/playfair.cpp
  util/utility.cpp
  util/args.cpp
  util/memdebug.cpp
)
add_executable(spymaster ${SOURCES})
