cmake_minimum_required(VERSION 3.14)

project(clang_scrap C)

add_executable(string string/main.c string/ext_string.c)

add_executable(sqlite sqlite3/main.c)
target_link_libraries(sqlite -lsqlite3)

set_property(TARGET string PROPERTY C_STANDARD 11)
