#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

GArray* new_multiply(gchar token);
GArray* multiply_append(GArray *multiply, gchar token);

GPtrArray* new_addition(GArray *multiply);
GPtrArray* addition_append(GPtrArray *addition, GArray *multiply);

void print_summ(GPtrArray *summ);
