cmake_minimum_required(VERSION 2.8)

project("QuaCode-MonteCarlo")

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_definitions(
  -Wall
  -O2
)

#
# Main
#

add_executable(meta.out
  src/main.cpp
  src/boat.cpp
  src/utils.cpp
  src/solution.cpp
  src/heuristic.hpp
  src/heuristicFactory.hpp
  src/localSearch.hpp
  src/localDescent.hpp
  src/tabuSearch.hpp
)