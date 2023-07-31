# QQ verbosity C library

QQ is a simple C library that provides a fast way to add verbosity levels to
your C programs.

## Quick start

```c
#include <stdio.h>
#include <qq.h>

int mul(int a, int b) {
    int ab = a * b;
    qq_debug("%d + %d = %d", a, b, ab);

    return ab;
}

int
main(int argc, char **argv)
{
    qq_set_level(QQ_DEBUG);

    /* Will print debug information to stdout. */
    int ab = mul(2, 3);

    return 0;
}
```

There are various levels of verbosity.