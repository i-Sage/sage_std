#include <sage_log/sage_log.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

int init_logger(Logger *logger, const char *file_name) {
    logger->__log_file = fopen(file_name, "w");
    if (logger->__log_file == NULL) {return -1;}
    if (pthread_mutex_init(&logger->__log_file_mutex, NULL) != 0) {
        fclose(logger->__log_file);
        return -1;
    }
    return 0;
}

void LOG(Logger *logger, const char *format, ...) {
    pthread_mutex_lock(&logger->__log_file_mutex);

    const time_t now = time(NULL);
    const struct tm *t = localtime(&now);
    fprintf(logger->__log_file, "[%04d-%02d-%02d %02d:%02d:%02d]",
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);

    va_list args;
    va_start(args, format);
    vfprintf(logger->__log_file, format, args);
    va_end(args);

    fprintf(logger->__log_file, "\n");
    fflush(logger->__log_file);

    pthread_mutex_unlock(&logger->__log_file_mutex);
}

void destroy_logger(Logger *logger) {
    pthread_mutex_destroy(&logger->__log_file_mutex);
    if (logger->__log_file != NULL) {
        fclose(logger->__log_file);
    }
}