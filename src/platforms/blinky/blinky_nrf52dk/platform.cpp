// Copyright 2020 Embedded Artistry LLC
// SPDX-License-Identifier: MIT

#include <printf.h>

// We don't print anything, so supply an empty defintion
extern "C" void _putchar(char c)
{
	(void)c;
}
