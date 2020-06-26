SET(CMAKE_SYSTEM_NAME Linux)

SET(CMAKE_C_COMPILER   emcc)
SET(CMAKE_CXX_COMPILER em++)
if(NOT DEFINED CMAKE_AR)
  find_program(CMAKE_AR NAMES emar)
endif()
if(NOT DEFINED CMAKE_RANLIB)
  find_program(CMAKE_RANLIB NAMES emranlib)
endif()

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)