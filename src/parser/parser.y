%{

  #include <stdio.h>
  #include <stdlib.h>
  #include <glib.h>

  int yylex (void);

  void yyerror(const char* s);

  typedef struct {
    char *left;
    char *right;
  } Box;

%}

%code requires
{
#include "glib.h"
}

%union {
  char* image;
  GArray* mul;
}
%token <image> WS K_CHAR M_CHAR N_CHAR MUL ADD

%start begin

%type<image> term
%type<mul> multiply

%%

begin:
  expression                { g_print("Axioma detected.\n"); }
;

expression:
  expression ADD multiply   { g_print("expression + multiply.\n"); }
  | multiply                { g_print("multiply detected.\n"); }
;

multiply:
  multiply MUL term         {
                              g_print("multiply * term detected.\n");
                            }
  | term                    {
                              g_print("term detected. [%s]\n", $1);
                            }
;

term:
  K_CHAR                    { g_print("k detected [%s].\n", $1); $$ = $1; }
  | M_CHAR                  { g_print("m detected [%s].\n", $1); $$ = $1; }
  | N_CHAR                  { g_print("n detected [%s].\n", $1); $$ = $1; }
;

%%

void yyerror(const char* s) {
  fprintf(stderr, "\n\tParse error: %s\n", s);
  exit(1);
}
