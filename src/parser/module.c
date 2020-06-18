#include <stdlib.h>

#include "module.h"

#define _new_multiply() (g_array_new(TRUE, TRUE, sizeof(Token)))
#define _new_addition() (g_ptr_array_new())

typedef struct {
    gsize step;
    GString* string;
} StringifyContext;

typedef struct {
    gsize shots;
    Token token;
    gboolean done;
} SharedFactorContext;

static void print_multiply(gpointer data, gpointer user_data)
{
    Multiply mul = data;

    g_print("\tMULTIPLY: %s\n", mul->data);
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
    Multiply result = _new_multiply();

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

static void print_summ(Addition summ)
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

static GString* stringify_addition(Addition summ)
{
    StringifyContext context = {
            0,
            g_string_new("")
    };

    g_ptr_array_foreach(summ, stringify_combine_additions, &context);

    g_ptr_array_free(summ, TRUE);

    return context.string;
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

    Multiply multiply = _new_multiply();
    g_array_append_val(multiply, token);

    return multiply;
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

    Addition addition = _new_addition();
    g_ptr_array_add(addition, multiply);

    return addition;
}

Addition addition_append(Addition addition, Multiply multiply)
{
    g_print("expression + multiply.\n");

    g_ptr_array_add(addition, multiply);

    return addition;
}

void translate(Addition summ)
{
    g_print("Axioma deteted.\n");

    print_summ(summ);

    Multiply factor = shared_factor(summ);

    GString *summ_str = stringify_addition(summ);

    g_print("\nRESULT: %s(%s)", factor->data, summ_str->str);

    g_string_free(summ_str, TRUE);
    g_array_free(factor, TRUE);
}

