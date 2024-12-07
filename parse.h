#ifndef PARSE_H
#define PARSE_H
#include <yaml.h>

struct buf;

bool process_root(yaml_parser_t *parser, struct buf *b, const char *toplevel_name);

#endif /* PARSE_H */
