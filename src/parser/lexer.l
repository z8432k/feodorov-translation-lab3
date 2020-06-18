%option noyywrap

%{

#include <stdio.h>
#include <glib.h>

#include "parser.tab.h"

%}

WS              [ \t\n\r\v]+
K_CHAR          [k]
M_CHAR          [m]
N_CHAR          [n]
MUL             [*]
ADD             [+]

%%
{WS}            {}

{K_CHAR} {
                printf("\tFound 'k'\n");
                image = yytext;
                return K_CHAR;
}

{M_CHAR} {
                printf("\tFound 'm'\n");
                image = yytext;
                return M_CHAR;
}

{N_CHAR} {
                printf("\tFound 'n'\n");
                image = yytext;
                return N_CHAR;
}

{MUL} {
                printf("\tFound '*'\n");
                image = yytext;
                return MUL;
}

{ADD} {
                printf("\tFound '+'\n");
                image = yytext;
                return ADD;
}
%%
