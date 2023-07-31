#ifndef QQ_STATEMENTS_H
#define QQ_STATEMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define TRY                         \
    do {                            \
        jmp_buf ex_buf__;           \
        switch (setjmp(ex_buf__)) { \
            case 0:                 \
                while (1) {
#define CATCH(x) \
    break;       \
    case x:
#define FINALLY \
    break;      \
    }           \
    default: {
/* `ETRY` is not actually compliant with the C standard as every identifier or
 * macro starting with capital E and followed by another capital letter or
 * number is actually reserved for the standard <errno.h> include file,
 * Fortunately, `ETRY` seems not to be used by any current <errno.h> that I was
 * able to check. */
#define ETRY \
    break;   \
    }        \
    }        \
    }        \
    while (0)
#define THROW(x) longjmp(ex_buf__, x)

#define EXIT(x)  \
    do {         \
        exit(x); \
    } while (0)

#endif