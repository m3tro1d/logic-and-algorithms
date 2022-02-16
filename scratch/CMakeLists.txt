cmake_minimum_required(VERSION 3.21)
project(lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab main.cpp)
add_custom_command(TARGET lab
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:lab> ${CMAKE_CURRENT_SOURCE_DIR})
