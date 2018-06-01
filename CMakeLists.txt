
cmake_minimum_required(VERSION 3.10) #checking CMake version

project(lab6) #name of the project

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories(./includes)

add_library(corasick_alg ./src/Corasick.cpp)
target_compile_features(corasick_alg PRIVATE cxx_std_11)

add_executable(def_corasick ./src/DefaultCorasick.cpp)
add_executable(joker_corasick ./src/JokerCorasick.cpp)


target_link_libraries(def_corasick corasick_alg)
target_link_libraries(joker_corasick corasick_alg)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(def_corasick_tests ./gtests/def_corasick_tests.cpp)
target_include_directories(def_corasick_tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(def_corasick_tests PRIVATE corasick_alg ${GTEST_LIBRARIES} pthread)

add_executable(joker_case_tests ./gtests/joker_case_tests.cpp)
target_include_directories(joker_case_tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(joker_case_tests PRIVATE corasick_alg ${GTEST_LIBRARIES} pthread)