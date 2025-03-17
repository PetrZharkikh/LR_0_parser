#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>

// Определение токенов
enum TokenType {
    NUMBER, 
    ID,
    TIMES,
    DIVIDE,
    PLUS,
    MINUS,
    LPAREN,
    RPAREN,
    END
};

// Структура токена
struct Token {
    TokenType type;
    std::string value;
};

// Объявление лексера из FLEX

    extern int yylex();  // Основная функция FLEX
    extern char* yytext; // Текущий текстовый токен


// Функция для выполнения синтаксического анализа
void parse();

#endif // PARSER_H