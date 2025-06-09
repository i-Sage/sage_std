#pragma once

#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#include "serr_check.h"


typedef struct Logger {
    FILE            *log_file;
    pthread_mutex_t  log_file_mutex;
} Logger;


void init_logger(Logger *logger, const char *file_name) {
    logger->log_file = fopen(file_name, "w");
    CHECK(logger->log_file);
    ERROR_CHECK(pthread_mutex_init(&logger->log_file_mutex, NULL), 0);
}


void LOG(Logger *logger, const char *format, ...) {
    ERROR_CHECK(pthread_mutex_lock(&logger->log_file_mutex), EXPECTED);
    const time_t now = time(NULL);
    const struct tm *t = localtime(&now);
    CHECK(logger->log_file);
    fprintf(logger->log_file, "[%04d-%02d-%02d %02d:%02d:%02d]",
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec
    );
    va_list args;
    va_start(args, format);
    vfprintf(logger->log_file, format, args);
    va_end(args);
    fprintf(logger->log_file, "\n");
    fflush(logger->log_file);
    ERROR_CHECK(pthread_mutex_unlock(&logger->log_file_mutex), EXPECTED);
}


void destroy_logger(Logger *logger) {
    ERROR_CHECK(pthread_mutex_destroy(&logger->log_file_mutex), EXPECTED);
    CHECK(logger->log_file);
    ERROR_CHECK(fclose(logger->log_file), EXPECTED);
}
