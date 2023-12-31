# QQ verbosity C library

QQ is a simple C library that provides a fast way to add verbosity levels to
your C programs.  It is designed to work on top of any custom set of error codes
i.e. extensions of errno codes.

## Build and test

```bash
git clone --recursive https://github.com/giulioprocopio/qq.git && cd qq
make build
make test  # Optional
```

Or, cloning submodules manually:

```bash
git clone https://github.com/giulioprocopio/qq.git && cd qq
make submodules build
```

You have now generated the static library `libqq.*` and the header `qq.h` in
the `build` directory.

To include the library in your project, it is suggested to add it as a Git
submodule and link it statically via CMake.  In the source directory of your
project, add the submodule:

```bash
mkdir third_party && cd third_party
git submodule add https://github.com/giulioprocopio/qq.git
git submodule update --init --recursive
```

Then, in your `CMakeLists.txt`:

```cmake
add_subdirectory(third_party/qq)
target_link_libraries(<your_target> qq)
```

## Quick start

Generally, you will want to set a global level of verbosity for your program
and then use the `qq_*` macros to log messages at different levels, without
having to check the verbosity level every time.

```c
#include <stdio.h>
#include <qq.h>

int
mul(int a, int b)
{
    int ab = a * b;
    qq_debug("%d * %d = %d", a, b, ab);

    return ab;
}

int
main(int argc, char **argv)
{
    qq_set_verbose(QQ_DEBUG);

    /* Will print debug information to stdout. */
    int ab = mul(2, 3);

    return 0;
}
```

When the user doesn't set a verbosity level, the default is `QQ_DEFAULT` which
is `QQ_INFO`.

## APIs

#### `typedef enum { ... } QQVerbose`

The enumeration type that holds the different verbosity levels.  The levels are
ordered from the least verbose to the most verbose.

 * `QQ_QUIET`: No output;
 * `QQ_ERROR`: Only errors;
 * `QQ_WARNING`: Errors and warnings;
 * `QQ_INFO`: Errors, warnings and information;
 * `QQ_DEBUG`: Errors, warnings, information and debug messages;
 * `QQ_TRACE`: Any kind of message.

#### `(int) QQ_DEFAULT`

The default verbosity level.  It is set to `QQ_INFO`.

#### `(size_t) QQ_MSG_BUFSIZ`

The size of the buffer used to format messages.  It is set to `1024` by default,
but can be changed by defining `QQ_MSG_BUFSIZ` before including the header.

#### `(int) QQ_VERBOSE_MAX` and `(int) QQ_VERBOSE_MIN`

Respectively the maximum and minimum integer verbosity levels that can be set.

#### `QQVerbose qq_get_verbose(void)`

Returns the current verbosity level.

#### `void qq_out(QQVerbose level, int code, const char *label, const char *msg, FILE *stream, int line, const char *func, const char *file)`

Source function for `qq_*` macros.  It is not meant to be used directly.

#### `void qq_raise(int code, const char *fmt, ...)`

This macro is used to raise an error.  It is equivalent to `qq_error` but
exits the program with error code `code` after printing the message (if verbose
enough).

#### `void qq_set_verbose(QQVerbose level)`

Sets the verbosity level to the given value.  If the value is out of range, it
is clamped to `QQ_DEFAULT`.

#### `void qq_setenv_verbose(const char *env)`

Initializes the verbosity level from the given environment variable.  If the
variable is not set, defaults to `QQ_DEFAULT`.  If the variable is set but its
value is out of range, the verbosity is set to `QQ_QUIET`.

#### `void qq_*([int code,] const char *fmt, ...)`

This is a set of macros that are used to log messages at different verbosity
levels.  A macro `qq_<level>` corresponds to the level `QQ_<LEVEL>`.  E.g.
`qq_error` &#8594; `QQ_ERROR` and `qq_debug` &#8594; `QQ_DEBUG`, with exception
of `QQ_QUIET` which has no macro.

The macros' signatures and spec differ depending on the verbosity level.  All
macros take however a format string and its arguments as parameters.  The
format string is used to format the message that will be printed to the
correct stream.

 * `qq_error` and `qq_warning` also take an error code as first parameter.  The
   error code is used to format the message.  These functions will print to
    `stderr`.
 * `qq_info`, `qq_debug` and `qq_trace` only take format parameters and print to
   `stdout`.

## Extensions

#### `TRY`, `CATCH`, `FINALLY`, `ETRY` and `THROW`

These macros simplify the use of `setjmp` and `longjmp` to implement exception
handling in C.  They are inspired by the 
[Exceptions in C with Longjmp and Setjmp][0] article.

#### `EXIT`

A wrapper around `exit`.


[0]: http://groups.di.unipi.it/~nids/docs/longjump_try_trow_catch.html