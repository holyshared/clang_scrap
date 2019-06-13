cmake_minimum_required(VERSION 3.14)

add_executable(main main.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -fshort-wchar")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

set_property(TARGET main PROPERTY C_STANDARD 11)
