#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>

//Token inizialization
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

//Token struct
struct Token {
    TokenType type;
    std::string value;
};



extern int yylex();  //Main flex function
extern char* yytext; //Current token


//Parsing function
void parse();

#endif