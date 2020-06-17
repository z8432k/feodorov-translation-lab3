%option noyywrap

%{

#include <stdio.h>
#include <glib.h>

#include "parser.h"

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
                yylval.image = strdup(yytext);

                return K_CHAR;
}

{M_CHAR} {
                printf("\tFound 'm'\n");
                yylval.image = strdup(yytext);

                return M_CHAR;
}

{N_CHAR} {
                printf("\tFound 'n'\n");
                yylval.image = strdup(yytext);

                return N_CHAR;
}

{MUL} {
                printf("\tFound '*'\n");
                yylval.image = strdup(yytext);

                return MUL;
}

{ADD} {
                printf("\tFound '+'\n");
                yylval.image = strdup(yytext);

                return ADD;
}
%%
