cmake_minimum_required(VERSION 3.14)

project(HelloSFML)

message("Hello Neal")

option(CURL_STATIC_LINKING "Set to ON to build libcurl with static linking."  OFF)

if(CURL_STATIC_LINKING)
    message("-DCURL_STATICLIB [added]")
    add_definitions(-DCURL_STATICLIB)
endif()

add_definitions(-DJSON_USE_IMPLICIT_CONVERSIONS=0)

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
find_package(CURL REQUIRED)

include_directories(${SFML_INCLUDE_DIRS}
        "FreePoints-/include/openai"
        /usr/local/include
        ${CURL_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES FreePoints-/examples/00-showcase.cpp)
set(SOURCE_FILES FreePoints-/main.cpp)



add_subdirectory(FreePoints-/examples)
add_executable(HelloSFML ${SOURCE_FILES})
#include_directories("include/openai")

#include_directories(/usr/local/include)

target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${CURL_LIBRARIES})