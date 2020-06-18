#include <stdlib.h>

#include "actions.h"

typedef struct {
    gsize step;
    GString* string;
} StringifyContext;

typedef struct {
    gsize shots;
    Token token;
    gboolean done;
} SharedFactorContext;

static inline void print_multiply(gpointer data, gpointer user_data)
{
    g_print("\tMULTIPLY: %s\n", ((Multiply) data)->data);
}

static void check_target_token(gpointer data, gpointer user_data) {
    Multiply multiply = data;
    SharedFactorContext *context = user_data;

    Token current_token;
    for (gsize i = 0; i < multiply->len; i++) {
        current_token = g_array_index(multiply, Token, i);

        if (current_token == context->token) {
            context->shots++;
            break;
        }
    }
}

static void remove_target_token(gpointer data, gpointer user_data)
{
    Multiply multiply = data;
    SharedFactorContext *context = user_data;

    Token current_token;
    for (gsize i = 0; i < multiply->len; i++) {
        current_token = g_array_index(multiply, Token, i);

        if (current_token == context->token) {
            g_array_remove_index(multiply, i);
            break;
        }
    }

    if (multiply->len == 0) {
        g_array_append_val(multiply, "1");
        context->done = TRUE;
    }
}

static Multiply shared_factor(Addition summ)
{
    Multiply result = new_multiply();

    Multiply first_factor = g_ptr_array_index(summ, 0);

    SharedFactorContext context = {
            0,
            0,
            FALSE
    };
    for (gsize i = 0; i < first_factor->len;) {
        context.token = g_array_index(first_factor, Token, i);

        g_print("\t\tFINDING SHARED FACTOR [%c]:\n", context.token);

        context.shots = 0;

        g_ptr_array_foreach(summ, check_target_token, &context);

        if (context.shots == summ->len) {
            g_array_append_val(result, context.token);
            g_ptr_array_foreach(summ, remove_target_token, &context);
        }
        else {
            i++;
        }

        if (context.done) {
            break;
        }
    }

    if (result->len == 0) {
        g_array_append_val(result, "1");
    }

    return result;
}

static inline void print_summ(Addition summ)
{
    g_print("\n");

    if (summ->len > 1) {
        g_print("\nSUM OF:\n");
    }

    g_ptr_array_foreach(summ, print_multiply, NULL);
}

static void stringify_combine_additions(gpointer data, gpointer user_data)
{
    Multiply multiply = data;
    StringifyContext *context = user_data;

    if (context->step > 0) {
        g_string_append(context->string, "+");
    }

    g_string_append(context->string, multiply->data);
    g_array_free(multiply, TRUE);

    context->step++;
}

static inline GString* stringify_addition(Addition summ)
{
    StringifyContext context = {
            0,
            g_string_new("")
    };

    g_ptr_array_foreach(summ, stringify_combine_additions, &context);

    g_ptr_array_free(summ, TRUE);

    return context.string;
}

Multiply multiply_append(Multiply multiply, Token token)
{
    g_array_append_val(multiply, token);

    return multiply;
}

Addition addition_append(Addition addition, Multiply multiply)
{
    g_ptr_array_add(addition, multiply);

    return addition;
}

gchar* translate(Addition summ)
{
    print_summ(summ);

    Multiply factor = shared_factor(summ);

    GString *summ_str = stringify_addition(summ);

    GString* tmp = g_string_new("");

    g_string_printf(tmp, "%s(%s)", factor->data, summ_str->str);

    gchar *result = tmp->str;

    g_string_free(tmp, FALSE);
    g_string_free(summ_str, TRUE);
    g_array_free(factor, TRUE);

    return result;
}

