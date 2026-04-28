#pragma once

/* Writes one character to the active output device. */
int putchar(int ic);

/* Writes a buffer of characters with an explicit length. */
bool print(const char* data, size_t length);

/* Writes formatted text using a printf-style format string. */
int printf(const char* __restrict__ format, ...);
