// SPDX-License-Identifier: GPL-2.0-only
#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <yaml.h>
#include "buf.h"
#include "parse.h"

int main(int argc, char **argv) {
	if (argc > 1) {
		printf("usage: %s < input.yaml > output.xml\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *toplevel_name = "labwc_config";

	struct buf b = BUF_INIT;
	yaml_parser_t parser;
	yaml_parser_initialize(&parser);
	yaml_parser_set_input_file(&parser, stdin);

	bool success = process_root(&parser, &b, toplevel_name);
	if (success) {
		printf("%s", b.data);
	}

	buf_reset(&b);
	yaml_parser_delete(&parser);
	return EXIT_SUCCESS;
}
