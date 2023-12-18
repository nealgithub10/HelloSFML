cmake_minimum_required(VERSION 3.26)
project(openai)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(nlohmann)

add_executable(openai
        nlohmann/json.hpp
        nlohmann/main.cpp
        openai.hpp)
