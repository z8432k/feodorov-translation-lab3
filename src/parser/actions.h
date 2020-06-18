#include <glib.h>

#define new_multiply() (g_array_new(TRUE, TRUE, sizeof(Token)))
#define new_addition() (g_ptr_array_new())

typedef GArray* Multiply;
typedef GPtrArray* Addition;
typedef gchar Token;

Multiply multiply_append(Multiply multiply, Token token);

Addition addition_append(Addition addition, Multiply multiply);

gchar* translate(Addition summ);
