#ifndef QQ_OUT_H
#define QQ_OUT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "qq/verbose.h"

#ifndef QQ_MSG_BUFSIZ
#    define QQ_MSG_BUFSIZ (size_t)1024
#endif

void
qq_out(QQVerbose verbose, int code, const char *label, const char *msg,
       FILE *stream, int line, const char *func, const char *file);

#define qq_outf(verbose, code, label, format, stream, ...)                 \
    ({                                                                     \
        char __qq_msg[QQ_MSG_BUFSIZ];                                      \
        snprintf(__qq_msg, QQ_MSG_BUFSIZ, format, ##__VA_ARGS__);          \
        qq_out(verbose, code, label, __qq_msg, stream, __LINE__, __func__, \
               __FILE__);                                                  \
    })

#define qq_error(code, format, ...) \
    qq_outf(QQ_ERROR, code, "ERROR", format, stderr, ##__VA_ARGS__)

#define qq_warning(code, format, ...) \
    qq_outf(QQ_WARNING, code, "WARNING", format, stderr, ##__VA_ARGS__)

#define qq_info(format, ...) \
    qq_outf(QQ_INFO, 0, "INFO", format, stdout, ##__VA_ARGS__)

#define qq_debug(format, ...) \
    qq_outf(QQ_DEBUG, 0, "DEBUG", format, stdout, ##__VA_ARGS__)

#define qq_trace(format, ...) \
    qq_outf(QQ_TRACE, 0, "TRACE", format, stdout, ##__VA_ARGS__)

#define qq_raise(code, format, ...)            \
    ({                                         \
        qq_error(code, format, ##__VA_ARGS__); \
        exit(code);                            \
    })

#endif