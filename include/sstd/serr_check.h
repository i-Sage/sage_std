#pragma once
#include <stdio.h>
#include <stdlib.h>


typedef enum {
    ERR = -1,
    OK = 1,
    EXPECTED = 0
} err_type_t;


#define ERROR_CHECK(call, expected) do {                                                           \
        int _ret = (call);                                                                         \
        if (_ret != (expected)) {                                                                  \
            fprintf(stderr, "ERROR: call '%s' returned %d, expected %d\n", #call, _ret, expected); \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while(0)


#define CHECK(ptr) do {                                                                            \
    if ((ptr) == NULL) {                                                                           \
        fprintf(stderr, "ERROR: NULL POINTER DETECTED: %s AT %s:%d\n", #ptr, __FILE__, __LINE__);  \
        exit(EXIT_FAILURE);                                                                        \
    }                                                                                              \
} while(0)                                                                                          