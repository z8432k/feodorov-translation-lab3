#include <stdlib.h>

#include "module.h"

static void print_multiply(gpointer data, gpointer user_data)
{
    Multiply mul = data;

    g_print("\tMULTIPLY: %s\n", mul->data);
}

static Multiply find_shared_factors(Addition summ)
{
    if (summ->len <= 1) {
        return NULL;
    }

    Multiply result = g_array_new(TRUE, TRUE, sizeof(char));

    Multiply first_factor = g_ptr_array_index(summ, 0);

    char symbol;
    for (gsize i = 0; i < first_factor->len; i++) {
        symbol = g_array_index(first_factor, Token, i);

        // g_ptr_array_foreach(summ, print_multiply, NULL);
        // g_ptr_array_foreach(summ, print_multiply, NULL);
        g_print("FIND SHARED [%c]:\n", symbol);
    }


    return result;
}

void yyerror(const char* s) {
    g_printerr("\n\tParse error: %s\n", s);
    exit(1);
}

Token pass_token(Token token)
{
    g_print("k detected [%c].\n", token);

    return token;
}

Multiply new_multiply(Token token)
{
    g_print("term detected. [%c]\n", token);

    Multiply out = g_array_new(TRUE, TRUE, sizeof(Token));
    g_array_append_val(out, token);

    return out;
}

Multiply multiply_append(Multiply multiply, Token token)
{
    g_print("multiply * term detected.\n");
    g_array_append_val(multiply, token);

    return multiply;
}

Addition new_addition(Multiply multiply)
{
    g_print("multiply detected.\n");

    Addition addition = g_ptr_array_new();
    g_ptr_array_add(addition, multiply);

    return addition;
}

Addition addition_append(Addition addition, Multiply multiply)
{
    g_print("expression + multiply.\n");

    g_ptr_array_add(addition, multiply);

    print_summ(addition);

    return addition;
}

void print_summ(Addition summ)
{
    g_print("SUM OF:\n");
    g_ptr_array_foreach(summ, print_multiply, NULL);

    find_shared_factors(summ);
}
