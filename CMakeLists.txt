cmake_minimum_required(VERSION 3.10)

project(C-Projects-From-Newbie C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(app
    baselib/string/small-string-opt/small_string_opt.c
    baselib/string/string-lazy/string-lazy.c
    baselib/string/tests/s_s_o.c
)
