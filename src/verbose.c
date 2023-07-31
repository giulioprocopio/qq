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
    qq_verbose = v;
}

void
qq_init_verbose(const char *restrict env)
{
    qq_set_verbose(QQ_INFO);

    char *verbose = getenv(env);
    int verbose_level = verbose != NULL ? atoi(verbose) : 3;

    if (QQ_VERBOSE_MIN < verbose_level && verbose_level < QQ_VERBOSE_MAX)
        qq_set_verbose((QQVerbose)verbose_level);
    else
        qq_set_verbose(QQ_INFO);
}

bool
qq_is_verbose(QQVerbose v)
{
    return v <= qq_get_verbose();
}