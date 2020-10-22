%require "3.3"
%language "c++"
%parse-param {Lexer& lexer}
%define parse.error verbose
%define api.value.type variant
%define api.parser.class {Parser}
%define api.namespace {Expr}

%code requires {
    class Lexer;
}

%{

#include "lexer.h"
#define yylex(arg) lexer.getNextToken(arg)

namespace Expr {
    void Parser::error(const std::string& msg) {
        throw("\033[1;31mLine "
            + std::to_string(lexer.getLineNo()) 
            + "\033[0m: " 
            + msg);
    }
}

%}

%token H1 "h1"
%token H2 "h2"
%token H3 "h3"

%token Eof 0
%token Error

%token<std::string> Word "word"
%type<std::string> expr

%%

input: expr_list
;

expr_list: expr_list expr { std::cout << $2 << "\n"; }
    | %empty
;

expr:  "h1" { $$ = "h1"; } 
    | "h2" { $$ = "h2"; } 
    | "h3" { $$ = "h3"; }
    | "word" { $$ = "word"; } 
;
%%