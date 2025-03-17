#include "parser.h"
#include <iostream>
#include <stack>
#include <vector>

std::stack<std::string> parseStack;
std::vector<Token> tokens;
size_t tokenIndex = 0;

Token getNextToken() {
    Token token;
    int tokenType = yylex();
    token.value = yytext;

    switch (tokenType) {
        case NUMBER: token.type = NUMBER; break;
        case ID: token.type = ID; break;
        case TIMES: token.type = TIMES; break;
        case DIVIDE: token.type = DIVIDE; break;
        case PLUS: token.type = PLUS; break;
        case MINUS: token.type = MINUS; break;
        case LPAREN: token.type = LPAREN; break;
        case RPAREN: token.type = RPAREN; break;
        default: token.type = END;
    }

    return token;
}

void parse() {
    parseStack.push("$");
    Token token = getNextToken();

    while (true) {
        std::string top = parseStack.top();

        if (token.type == ID) {
            parseStack.push("ID");
            token = getNextToken();
            std::cout << "Shift: ID" << std::endl;
        }
        else if (token.type == NUMBER) {
            parseStack.push("NUMBER");
            token = getNextToken();
            std::cout << "Shift: NUMBER" << std::endl;
        }
        else if (top == "ID" || top == "NUMBER") {
            parseStack.pop();
            parseStack.push("F");
            std::cout << "Reduce: F -> ID/NUMBER" << std::endl;
        }
        else if (top == "F") {
            parseStack.pop();
            parseStack.push("T");
            std::cout << "Reduce: T -> F" << std::endl;
        }
        else if (parseStack.size() >= 3) {
            std::string f = parseStack.top(); parseStack.pop();
            std::string op = parseStack.top(); parseStack.pop();
            std::string t = parseStack.top(); parseStack.pop();
            
            if (f == "F" && op == "*" && t == "T") {
                parseStack.push("T");  
                std::cout << "Reduce: T -> T * F" << std::endl;
            } 
            else if (t == "T" && (token.type == PLUS || token.type == MINUS || token.type == END)) {
                parseStack.push("E");
                std::cout << "Reduce: E -> T" << std::endl;
            }
            else {
                std::cerr << "Syntax Error!" << std::endl;
                break;
            }
        }
        else if (top == "E" && token.type == PLUS) {
            parseStack.pop();
            parseStack.push("T");
            parseStack.push("+");
            parseStack.push("E");
            std::cout << "Reduce: E -> E + T" << std::endl;
        }
        else if (top == "E" && token.type == END) {
            std::cout << "Accept" << std::endl;
            break;
        }
        else {
            std::cerr << "Syntax Error!" << std::endl;
            break;
        }
    }
}