cmake_minimum_required(VERSION 3.20)
project(Sage_Log C)
set(CMAKE_C_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        src/sage_log.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(__minor __minor.c)
target_link_libraries(__minor Sage_Log)