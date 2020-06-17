#include "parser.h"
#include <glib.h>

static void print_multiply(gpointer data, gpointer user_data)
{
    GArray *mul = data;

    g_print("\tMULTIPLY: %s\n", mul->data);
}



static GArray* find_shared_factors(GPtrArray *summ)
{
    if (summ->len <= 1) {
        return NULL;
    }

    GArray *result = g_array_new(TRUE, TRUE, sizeof(char));

    GArray *first_factor = g_ptr_array_index(summ, 0);

    char symbol;
    for (gsize i = 0; i < first_factor->len; i++) {
        symbol = g_array_index(first_factor, char, i);

        // g_ptr_array_foreach(summ, print_multiply, NULL);
        // g_ptr_array_foreach(summ, print_multiply, NULL);
        g_print("FIND SHARED [%c]:\n", symbol);
    }


    return result;
}

void yyerror(const char* s) {
    fprintf(stderr, "\n\tParse error: %s\n", s);
    exit(1);
}

GArray* new_multiply(gchar token)
{
    g_print("term detected. [%c]\n", token);

    GArray *out = g_array_new(TRUE, TRUE, sizeof(gchar));
    g_array_append_val(out, token);

    return out;
}

GArray* multiply_append(GArray *multiply, gchar token)
{
    g_print("multiply * term detected.\n");
    g_array_append_val(multiply, token);

    return multiply;
}

GPtrArray* new_addition(GArray *multiply)
{
    g_print("multiply detected.\n");

    GPtrArray *addition = g_ptr_array_new();
    g_ptr_array_add(addition, multiply);

    return addition;
}

GPtrArray* addition_append(GPtrArray *addition, GArray *multiply)
{
    g_print("expression + multiply.\n");

    g_ptr_array_add(addition, multiply);

    print_summ(addition);

    return addition;
}

void print_summ(GPtrArray *summ)
{
    g_print("SUM OF:\n");
    g_ptr_array_foreach(summ, print_multiply, NULL);

    find_shared_factors(summ);
}
