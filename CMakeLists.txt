cmake_minimum_required(VERSION 3.20)
project(sstd C)


set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(ENABLE_TESTING TRUE)

set(SSTD_VERSION_MAJOR 1)
set(SSTD_VERSION_MINOR 1)
set(SSTD_VERSION_PATCH 0)


add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(${PROJECT_NAME} INTERFACE 
    -Wall -Wextra -Werror
)

target_compile_definitions(${PROJECT_NAME} INTERFACE
    SSTD_VERSION_MAJOR=${SSTD_VERSION_MAJOR}
    SSTD_VERSION_MINOR=${SSTD_VERSION_MINOR}
    SSTD_VERSION_PATCH=${SSTD_VERSION_PATCH}
)


if(ENABLE_TESTING)
    message("TESTING ENABLED")
    enable_testing()
    add_executable(serr_check tests/test_err_check.c)
    target_link_libraries(serr_check PRIVATE ${PROJECT_NAME})
    add_test(NAME ERR_TEST COMMAND serr_check) 
endif(ENABLE_TESTING)