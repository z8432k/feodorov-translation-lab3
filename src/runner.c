#include <stdio.h>
#include "runner.h"
#include "parser.h"
#include "lexer.h"

void runner(char *str, gchar **result) {
    yy_scan_string(str);
    yyparse(result);
}

