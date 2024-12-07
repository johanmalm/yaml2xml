/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef BUF_H
#define BUF_H

struct buf {
	char *data;
	int alloc;
	int len;
};

#define BUF_INIT ((struct buf){.data = ""})

void buf_add_fmt(struct buf *s, const char *fmt, ...);
void buf_reset(struct buf *s);

#endif /* LABWC_BUF_H */
