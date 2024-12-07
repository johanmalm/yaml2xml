// SPDX-License-Identifier: GPL-2.0-only
#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

static void
die_if_null(void *ptr)
{
	if (!ptr) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
}

static void *
xrealloc(void *ptr, size_t size)
{
	if (!size) {
		free(ptr);
		return NULL;
	}
	ptr = realloc(ptr, size);
	die_if_null(ptr);
	return ptr;
}

#define xmalloc(size) xrealloc(NULL, (size))

static void
buf_expand(struct buf *s, int new_alloc)
{
	if (s->alloc && new_alloc <= s->alloc) {
		return;
	}
	new_alloc = MAX(new_alloc, 256);
	new_alloc = MAX(new_alloc, s->alloc * 3 / 2);
	if (s->alloc) {
		assert(s->data);
		s->data = xrealloc(s->data, new_alloc);
	} else {
		assert(!s->len);
		s->data = xmalloc(new_alloc);
		s->data[0] = '\0';
	}
	s->alloc = new_alloc;
}

void
buf_add_fmt(struct buf *s, const char *fmt, ...)
{
	if (!fmt || !*fmt) {
		return;
	}
	va_list ap;

	va_start(ap, fmt);
	int n = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);

	if (n < 0) {
		return;
	}

	size_t size = (size_t)n + 1;
	buf_expand(s, s->len + size);

	va_start(ap, fmt);
	n = vsnprintf(s->data + s->len, size, fmt, ap);
	va_end(ap);

	if (n < 0) {
		return;
	}

	s->len += n;
	s->data[s->len] = 0;
}

void
buf_reset(struct buf *s)
{
	if (s->alloc) {
		free(s->data);
	}
	*s = BUF_INIT;
}
