%{
#include "parser.h"
#include <cstdlib>
%}
%option noyywrap
%%
[0-9]+      { return NUMBER; }  // Числа
[xyz]       { return ID; }      // Переменные x, y, z
"*"         { return TIMES; }   // Умножение
"/"         { return DIVIDE; }  // Деление
"+"         { return PLUS; }    // Сложение
"-"         { return MINUS; }   // Вычитание
"("         { return LPAREN; }  // Открывающая скобка
")"         { return RPAREN; }  // Закрывающая скобка
[ \t\n]+    { /* Игнорируем пробелы и переносы строк */ }
.           { return END; }     // Любой другой символ -> конец
%%
int yywrap() { return 1; }