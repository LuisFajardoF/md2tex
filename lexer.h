#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <string>
#include "parser.h"

using yyscan_t = void*;
using semantic_type = Expr::Parser::semantic_type;
using Token = Expr::Parser::token;

class Lexer
{
public:
    Lexer(std::istream &in);
    ~Lexer();

    int getNextToken(semantic_type *yylval)
    {
        return _getNextToken(*yylval, scanner);
    }

    std::string getText() { return text; }
    int getLineNo();

private:
    int _getNextToken(semantic_type& yylval, yyscan_t yyscanner);
    int makeToken(const char *txt, int len, int tk);

    std::istream &in;
    std::string text;
    yyscan_t scanner;
};

namespace AuxFuncs 
{
    void specialLatexCommands(char character, std::string& text, int& offset);
}

#endif