cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project (AlgLoopAna)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(test1 "tests/test.cpp")
install (FILES "tests/test.txt" DESTINATION examples)
install (TARGETS test1 DESTINATION examples)