%{

int yylex (void);

void yyerror(const char* s);

#include <glib.h>

%}

%code requires
{
#include "module.h"
}

%union {
  char image;
  GArray* mul;
  GPtrArray* summ;
}
%token <image> WS K_CHAR M_CHAR N_CHAR MUL ADD

%start begin

%type<image> term
%type<mul> multiply
%type<summ> addition

%%

begin:
  addition                  { g_print("Axioma detected.\n"); }
;

addition:
  addition ADD multiply     { addition_append($1, $3); }
  | multiply                { $$ = new_addition($1); }
;

multiply:
  multiply MUL term         { $$ = multiply_append($1, $3); }
  | term                    { $$ = new_multiply($1); }
;

term:
  K_CHAR                    { g_print("k detected [%c].\n", $1); $$ = $1; }
  | M_CHAR                  { g_print("m detected [%c].\n", $1); $$ = $1; }
  | N_CHAR                  { g_print("n detected [%c].\n", $1); $$ = $1; }
;

%%

// Felix, qui potuit rerum cognoscere causas
