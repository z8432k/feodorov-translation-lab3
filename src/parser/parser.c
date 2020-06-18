#include <stdio.h>
#include <glib.h>

#include "parser.h"
#include "actions.h"

gchar* image;

LexToken token;

static gboolean F(Token *tok)
{
    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            *tok = image[0];
            token = yylex();
            return TRUE;
        default:
            return FALSE;
    }
}

static gboolean H(Multiply mul)
{
    Token tok;

    switch (token) {
        case MUL:
            token = yylex();
            if (!F(&tok)) {
                return FALSE;
            }
            if (!H(mul)) {
                return FALSE;
            }
            break;
        case ADD:
        case EOL:
            return TRUE;
        default:
            return FALSE;
    }

    multiply_append(mul, tok);

    return TRUE;
}

static gboolean T(Multiply mul)
{
    Token tok;

    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            if (!F(&tok)) {
                return FALSE;
            }
            if (!H(mul)) {
                return FALSE;
            }
            break;
        default:
            return FALSE;
    }

    multiply_append(mul, tok);

    return TRUE;
}

static gboolean G(Addition summ)
{
    Multiply mul = new_multiply();

    switch (token) {
        case ADD:
            token = yylex();
            if (!T(mul)) {
                return FALSE;
            }
            if (!G(summ)) {
                return FALSE;
            }
            break;
        case EOL:
            return TRUE;
        default:
            return FALSE;
    }

    addition_append(summ, mul);

    return TRUE;
}

static gboolean E(Addition summ)
{
    Multiply mul = new_multiply();

    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            if (!T(mul)) {
                return FALSE;
            }
            if (!G(summ)) {
                return FALSE;
            }
            break;
        default:
            return FALSE;
    }

    addition_append(summ, mul);

    return TRUE;
}

static gboolean S(Addition summ)
{
    token = yylex();

    switch (token) {
        case N_CHAR:
        case M_CHAR:
        case K_CHAR:
            if (!E(summ)) {
                return FALSE;
            }
            break;
        default:
            return FALSE;
    }

    return TRUE;
}

gint parse(gchar **translate_result)
{
    Addition summ = new_addition();

    if (S(summ)) {
        g_print("\n\t Syntax OK.\n");
        *translate_result = translate(summ);
        return 0;
    }
    else {
        printf("FAIL.\n");
        return 1;
    }
}
