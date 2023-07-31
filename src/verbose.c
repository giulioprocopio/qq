#define QQ_VERBOSE_C

#include <stdbool.h>
#include <stdlib.h>

#include "qq/verbose.h"

QQVerbose
qq_get_verbose(void)
{
    return qq_verbose;
}

void
qq_set_verbose(QQVerbose v)
{
    if (QQ_VERBOSE_MIN <= v && v <= QQ_VERBOSE_MAX)
        qq_verbose = v;
    else
        qq_verbose = QQ_DEFAULT;
}

void
qq_init_verbose(const char *restrict env)
{
    qq_set_verbose(QQ_INFO);

    char *verbose = getenv(env);
    qq_set_verbose(verbose != NULL ? atoi(verbose) : QQ_DEFAULT);
}

bool
qq_is_verbose(QQVerbose v)
{
    return v <= qq_get_verbose();
}