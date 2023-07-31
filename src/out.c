#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "qq/out.h"
#include "qq/verbose.h"

void
qq_out(QQVerbose verbose, int code, const char *label, const char *msg,
       FILE *stream, int line, const char *func, const char *file)
{
    if (qq_is_verbose(verbose)) {
        fprintf(stream, "%s:%d:%s %s(%d): %s\n", file, line, func, label, code,
                msg);
    }
}