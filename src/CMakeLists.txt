include_directories(${CMAKE_SOURCE_DIR}/src/algos)
include_directories(${CMAKE_SOURCE_DIR}/src/util)

set(SOURCES
  main.cpp
  algos/des.cpp
  algos/caeser.cpp
  algos/playfair.cpp
  algos/aes.cpp
  util/utility.cpp
  util/args.cpp
)
add_executable(spymaster ${SOURCES})
