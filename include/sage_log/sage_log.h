#pragma once

#include <stdio.h>
#include <pthread.h>

/// @brief
typedef struct Logger {
    FILE            *__log_file;
    pthread_mutex_t __log_file_mutex;
} Logger;

/// @brief Initialize the Logger.
/// @param
int init_logger(Logger *logger, const char *file_name);

/// @brief Thread-safe Log Function.
/// @param
void LOG(Logger *logger, const char *format, ...);

/// @brief  Destroy the Logger (closes file, destroys the mutex)
/// @param
void destroy_logger(Logger *logger);