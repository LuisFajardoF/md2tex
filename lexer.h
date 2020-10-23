#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "parser.h"

#define SIZE 1024


class Lexer
{
public:
    using semantic_type = Expr::Parser::semantic_type;
    using Token = Expr::Parser::token;

    Lexer(std::istream& in) : context(in), lineno(1) {}
    ~Lexer() {}
    
    int getNextToken(semantic_type *yylval);
    void yyfill(size_t n);
    std::string getText() { return std::string(context.token, context.current - context.token); }
    unsigned int getLineNo() { return lineno; }

private:
    enum class FillStatus { Ok, Error, Eof };

    struct Context {
        std::vector<char> buffer;
        char* limit;
        char* current;
        char* marker;
        char* token;
        bool eof;
        std::istream& in;

        Context(std::istream& in);
        ~Context() {}
        FillStatus fill(size_t need);
    };

    int TkEof() { return Token::Eof; }
    int TkError() { return Token::Error; }

    Context context;
    std::string text;
    unsigned int lineno;
};

#endif