#ifndef __UTILS_H_
#define __UTILS_H_

#include <errno.h>
#include <stdio.h>

#define DIE(assertion, call_description)				\
    do {								\
            if (assertion) {					\
                    perror(call_description);			\
                    exit(errno);					\
            }							\
    } while (0)

#endif