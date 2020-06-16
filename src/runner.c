#include <stdio.h>
#include "runner.h"
#include "parser.h"
#include "lexer.h"

void runner(char *str) {
    yy_scan_string(str);
    yyparse();
    printf("\n\t Syntax OK.\n");
}

