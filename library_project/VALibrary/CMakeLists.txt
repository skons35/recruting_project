# CMakeList.txt : CMake project for my VALibrary, include source and define
# project specific logic here.

#   Vincent Alleaume  11/2021 , recruting test

cmake_minimum_required (VERSION 3.8)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/VALibrary/dep/inc)

FILE(GLOB sources ${CMAKE_SOURCE_DIR}/VALibrary/dep/src/*.cpp)
ADD_LIBRARY(vaLibraryLib ${sources})

SET_PROPERTY(TARGET vaLibraryLib
  PROPERTY 
  # enable c++17 compliance, and get  std::<optional> usable with vs2019 for instance
  CXX_STANDARD 17)
  
ADD_EXECUTABLE(vaLibrary ${CMAKE_SOURCE_DIR}/VALibrary/src/vaLibrary.cpp)

target_link_libraries(vaLibrary vaLibraryLib)

SET_PROPERTY(TARGET vaLibrary
  PROPERTY 
  # enable c++17 compliance, and get  std::<optional> usable with vs2019 for instance
  CXX_STANDARD 17)

# install part related :

SET_PROPERTY(TARGET vaLibrary
  PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
 
INSTALL(TARGETS vaLibraryLib DESTINATION lib)
INSTALL(TARGETS vaLibrary DESTINATION bin)

# could also copy an EXISITNG 'run' folder into destination folder : ('run' must exist, or cmake error)
#INSTALL(DIRECTORY run DESTINATION ${CMAKE_BINARY_DIR}/run)