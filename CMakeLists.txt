cmake_minimum_required(VERSION 3.11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

add_executable(ch4.x ch4.c)

add_executable(ch4_editline.x ch4_editline.c)
target_link_libraries(ch4_editline.x edit)

add_executable(ch4_editline_win.x ch4_editline_win.c)
target_link_libraries(ch4_editline_win.x edit)

add_executable(strstr.x strstr.c)

add_executable(parser.x parser.c mpc.c)
target_link_libraries(parser.x edit m)
