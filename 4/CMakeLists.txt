cmake_minimum_required (VERSION 3.1)
project(3_december)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "-Wall -pedantic -Werror")

include_directories(include)

add_executable(run 
	src/main.cpp
  src/guard.cpp
  src/parser.cpp
)
