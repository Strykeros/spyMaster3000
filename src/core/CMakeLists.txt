include_directories(algos)
include_directories(util)

add_library(core
  lib.cpp
  spymaster.cpp
  algos/aes.cpp
  algos/des.cpp
  algos/playfair.cpp
)

