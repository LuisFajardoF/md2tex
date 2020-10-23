%require "3.3"
%language "c++"
%parse-param {Lexer& lexer}
%parse-param {Ast::AstNode *&root}
%define parse.error verbose
%define api.value.type variant
%define api.parser.class {Parser}
%define api.namespace {Expr}

%code requires {
    #include "ast.h"
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

%token<std::string> H1 "h1"
%token<std::string> H2 "h2"
%token<std::string> H3 "h3"
%token<std::string> Word "word"

%token Error
%token Eof 0 "EoF"

%type<Ast::AstNode *> section_list
%type<Ast::Section *> section

%%

input: section_list { root = $1; }
;

section_list: section_list section { 
            $$ = $1;
            dynamic_cast<Ast::BlockSection *>($$)->nv.push_back($2); 
        }
        | section {
            Ast::NodeVector sections;
            sections.push_back($1);
            $$ = new Ast::BlockSection(sections);
        }
;

section: "h1" "word" {
        $$ = new Ast::HeaderH1($1, $2);
    } 
    | "h2" "word" {
        $$ = new Ast::HeaderH2($1, $2); 
    } 
    | "h3" "word" {
        $$ = new Ast::HeaderH3($1, $2); 
    } 
;

%%