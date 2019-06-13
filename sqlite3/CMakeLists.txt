cmake_minimum_required(VERSION 2.8)

add_executable(main main.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-stack-protector -fshort-wchar")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

target_link_libraries(main -lsqlite3)
