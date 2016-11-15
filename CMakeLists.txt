cmake_minimum_required(VERSION 2.8)
project(MOBA)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")


add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
