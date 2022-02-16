cmake_minimum_required(VERSION 3.21)
project(scratch)

set(CMAKE_CXX_STANDARD 17)

add_executable(scratch main.cpp)
add_custom_command(TARGET scratch
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:scratch> ${CMAKE_CURRENT_SOURCE_DIR})
