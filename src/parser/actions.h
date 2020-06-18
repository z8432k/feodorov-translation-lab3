#include <glib.h>

typedef GArray* Multiply;
typedef GPtrArray* Addition;
typedef gchar Token;

Multiply new_multiply(gchar token);
Multiply multiply_append(Multiply multiply, Token token);

Token pass_token(Token token);
Addition new_addition(Multiply multiply);
Addition addition_append(Addition addition, Multiply multiply);

gchar* translate(Addition summ);
