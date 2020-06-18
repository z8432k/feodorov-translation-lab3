#include <stdio.h>
#include "parser.h"

char* image;

LexToken token;

static int F()
{
    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            token = yylex();
            return 1;
        default:
            return 0;
    }
}

static int H()
{
    switch (token) {
        case MUL:
            token = yylex();
            if (!F()) {
                return 0;
            }
            if (!H()) {
                return 0;
            }
            break;
        case ADD:
        case EOL:
            return 1;
        default:
            return 0;
    }

    return 1;
}

static int T()
{
    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            if (!F()) {
                return 0;
            }
            if (!H()) {
                return 0;
            }
            break;
        default:
            return 0;
    }

    return 1;
}

static int G()
{
    switch (token) {
        case ADD:
            token = yylex();
            if (!T()) {
                return 0;
            }
            if (!G()) {
                return 0;
            }
            break;
        case EOL:
            return 1;
        default:
            return 0;
    }

    return 1;
}

static int E()
{
    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            if (!T()) {
                return 0;
            }
            if (!G()) {
                return 0;
            }
            break;
        default:
            return 0;
    }

    return 1;
}

static int S()
{
    token = yylex();

    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            if (!E()) {
                return 0;
            }
            break;
        default:
            return 0;
    }

    return 1;
}

int parse(char **translate_result)
{
    if (S()) {
        return printf("OK\n");
    }
    else {
        return printf("FAIL.\n");
    }
}
