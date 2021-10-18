cmake_minimum_required(VERSION 3.10.0)
project(hellogl VERSION 0.1.0)

add_executable(hellogl main.cpp)

find_package(glad CONFIG REQUIRED)
target_link_libraries(hellogl PRIVATE glad::glad)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(hellogl PRIVATE glfw)
