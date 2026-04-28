#pragma once

/* Compiler-provided type that stores variable argument state. */
typedef __builtin_va_list va_list;

/* Starts reading arguments that appear after the named parameter. */
#define va_start(v, l) __builtin_va_start(v, l)

/* Cleans up variable argument state after use. */
#define va_end(v) __builtin_va_end(v)

/* Reads the next argument as the requested type. */
#define va_arg(v, l) __builtin_va_arg(v, l)
