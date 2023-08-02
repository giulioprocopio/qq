#ifndef QQ_VERBOSE_H
#define QQ_VERBOSE_H

typedef enum {
    QQ_QUIET = 0,
    QQ_ERROR = 1,
    QQ_WARNING = 2,
    QQ_INFO = 3,
    QQ_DEBUG = 4,
    QQ_TRACE = 5
} QQVerbose;

#define QQ_VERBOSE_MAX 5
#define QQ_VERBOSE_MIN 0

#ifndef QQ_DEFAULT
#    define QQ_DEFAULT QQ_INFO
#endif

#ifdef QQ_VERBOSE_C
QQVerbose qq_verbose = QQ_DEFAULT;
#else
extern QQVerbose qq_verbose;
#endif

#endif