#ifndef QQ_VERBOSE_H
#define QQ_VERBOSE_H

#include <stdbool.h>

typedef enum {
    QQ_SILENT = 0,
    QQ_ERROR = 1,
    QQ_WARNING = 2,
    QQ_INFO = 3,
    QQ_DEBUG = 4,
    QQ_TRACE = 5
} QQVerbose;

#define QQ_VERBOSE_MAX 5
#define QQ_VERBOSE_MIN 0

#ifdef QQ_VERBOSE_C
QQVerbose qq_verbose = QQ_INFO;
#else
extern QQVerbose qq_verbose;
#endif

QQVerbose
qq_get_verbose(void);

void
qq_set_verbose(QQVerbose v);

void
qq_init_verbose(const char *restrict env);

bool
qq_is_verbose(QQVerbose v);

#endif