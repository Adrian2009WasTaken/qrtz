cmake_minimum_required(VERSION 3.28)

project(qrtz C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/display.c")

add_executable(qrtz src/main.c ${SOURCES})