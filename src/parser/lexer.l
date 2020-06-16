%option noyywrap

%{

#include <stdio.h>

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

                return K_CHAR;
}

{M_CHAR} {
                printf("\tFound 'm'\n");

                return M_CHAR;
}

{N_CHAR} {
                printf("\tFound 'n'\n");

                return N_CHAR;
}

{MUL} {
                printf("\tFound '+'\n");

                return MUL;
}

{ADD} {
                printf("\tFound '+'\n");

                return ADD;
}
%%
