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
%token<std::string> H4 "h4"
%token<std::string> H5 "h5"
%token<std::string> Text "text"
%token<std::string> ImageText "imageText"
%token<std::string> FigureLabel "figureLabel"
%token<std::string> TableLabel "tableLabel"
%token<std::string> Default "default"
%token<std::string> NewPage "newpage"
%token<std::string> OpenParam "!--"
%token<std::string> CloseParam "--!"
%token<std::string> Colon ":"
%token<std::string> OpenKey "{"
%token<std::string> CloseKey "}"
%token<std::string> Cover "cover"
%token<std::string> Class "class"
%token<std::string> ToC "toc"
%token<std::string> LoF "lof"
%token<std::string> LoT "lot"
%token<std::string> Depth "depth"
%token<std::string> Spacing "spacing"
%token<std::string> Custom "custom"
%token<std::string> Title "title"
%token<std::string> Author "author"
%token<std::string> Date "date"
%token<std::string> Report "report"
%token<std::string> Institution "institution"
%token<std::string> Subject "subject"
%token<std::string> Place "place"
%token<std::string> Logo "logo"
%token<std::string> Numbered "numbered"
%token<std::string> PageNumbering "pagenumbering"
%token<std::string> Gobble "gobble"
%token<std::string> Arabic "arabic"
%token<std::string> Alph "alph"
%token<std::string> Roman "roman"
%token<std::string> Set "set"
%token<std::string> Figure "figure"
%token<std::string> Table "table"
%token<std::string> List "list"
%token<std::string> ListParams "listParams"
%token<std::string> ListContent "listContent"
%token<std::string> OpenBracket "["
%token<std::string> CloseBracket "]"
%token<std::string> OpenPar "("
%token<std::string> ClosePar ")"
%token<std::string> Comma ","
%token<std::string> Semicolon ";"
%token<std::string> OpenBib "```bib"
%token<std::string> CloseBib "bib```" // para diferenciar de otros tipos de cierre
%token<std::string> BibContent "bibContent"
%token<std::string> Error
%token Eof 0 "EoF"

%type<Ast::AstNode *> element_list
%type<Ast::Element *> element
%type<Ast::ParamsLevel1 *> param_level1_list
%type<Ast::ParamsLevel2 *> param_level2_list
%type<Ast::TocParams *> toc_params_list
%type<Ast::AstNode *> param_level1
%type<Ast::AstNode *> param_level2
%type<Ast::AstNode *> toc_params
%type<Ast::FigureParams *> figure_param
%type<Ast::MultipleFiguresParams *> multiple_figures_param
%type<Ast::MultipleFiguresLabel *> multiple_figures_label
%type<std::string> param_numbering

%%

input: element_list { root = $1; }
;

element_list: element_list element { 
            $$ = $1;
            dynamic_cast<Ast::BlockElement *>($$)->elements.push_back($2); 
        }
        | element {
            Ast::ElementVector elements;
            elements.push_back($1);
            $$ = new Ast::BlockElement(elements);
        }
;

element: "h1" "text" {
        $$ = new Ast::Section($2);
    } 
    | "h2" "text" {
        $$ = new Ast::SubSection($2); 
    } 
    | "h3" "text" {
        $$ = new Ast::SubSubSection($2); 
    } 
    | "h4" "text" {
        $$ = new Ast::Paragraph($2); 
    } 
    | "h5" "text" {
        $$ = new Ast::SubParagraph($2); 
    }
    | "text" {
        $$ = new Ast::PlainText($1);
    }
    | "figure" "[" "{" "figureLabel" "," "figureLabel" "}" ":" multiple_figures_param "]" "(" multiple_figures_label ")" {
        $$ = new Ast::MultipleFigures($4, $6, $9, $12);
    }
    | "figure" "[" "{" "figureLabel" "}" ":" multiple_figures_param "]" "(" multiple_figures_label ")" {
        $$ = new Ast::MultipleFigures($4, "", $7, $10);
    }
    | "figure" "[" figure_param "]" "(" "figureLabel" ")" {
        $$ = new Ast::Figure($3, $6);
    }
    | "table" "[" "tableLabel" "]" "{" "tableLabel" "}" {
        $$ = new Ast::Table($3, $6);
    }
    | "list" "listParams" "]" "{" "listContent" "}" {
        $$ = new Ast::List($2, $5);
    }
    | "```bib" "bibContent" "bib```" {
        $$ = new Ast::Bibliography($2);
    }
    | "newpage" {
        $$ = new Ast::NewPage();
    }
    | "!--" param_level1_list "--!" {
        $$ = $2;
    }
    | Error {
        error("invalid character");
    }
;

param_level1_list: param_level1_list param_level1 {
        $$ = $1;
        dynamic_cast<Ast::ParamsLevel1 *>($$)->elmtsl1.push_back($2);
    }
    | param_level1 {
        Ast::ElementVector elmtsl1;
        elmtsl1.push_back($1);
        $$ = new Ast::ParamsLevel1(elmtsl1);
    }
;

param_level1: "cover" ":" "default" "{" param_level2_list "}" {
        $$ = new Ast::DefaultCoverPage($3, $5);
    }
    | "cover" ":" "report" "{" param_level2_list "}" {
        $$ = new Ast::ReportCoverPage($3, $5);
    }
    | "class" ":" "text" {
        $$ = new Ast::LatexClass($3);
    }
    | "numbered" ":" "text" {
        $$ = new Ast::Numbered($3);
    }
    | "pagenumbering" ":" param_numbering "{" "set" ":" "text" "}" {
        $$ = new Ast::PageNumberingAsSet($3, $7);
    }
    | "pagenumbering" ":" param_numbering {
        $$ = new Ast::PageNumbering($3);
    }
    | "toc" ":" "text" {
        $$ = new Ast::ToC($3);
    }
    | "toc" ":" "custom" "{" toc_params_list "}" {
        $$ = new Ast::ComplexToc($3, $5);
    }
    | "lof" ":" "text" {
        $$ = new Ast::LoF($3);
    }
    | "lot" ":" "text" {
        $$ = new Ast::LoT($3);
    }
;

param_numbering: "arabic"
    | "roman"
    | "alph"
    | "gobble"
;

multiple_figures_param: multiple_figures_param ";" figure_param {
        $$ = $1;
        dynamic_cast<Ast::MultipleFiguresParams *>($$)->mfv.push_back($3);
    }
    | figure_param {
        Ast::MultipleFiguresVector mfv;
        mfv.push_back($1);
        $$ = new Ast::MultipleFiguresParams(mfv);
    }
;

multiple_figures_label: multiple_figures_label "," "figureLabel" {
        $$ = $1;
        dynamic_cast<Ast::MultipleFiguresLabel *>($$)->mfl.push_back($3);
    }
    | "figureLabel" {
        Ast::StringVector mfl;
        mfl.push_back($1);
        $$ = new Ast::MultipleFiguresLabel(mfl);
    }
;

figure_param: figure_param "," "figureLabel" {
        $$ = $1;
        dynamic_cast<Ast::FigureParams *>($$)->figureParams.push_back($3);
    }
    | "figureLabel" {
        Ast::StringVector params;
        params.push_back($1);
        $$ = new Ast::FigureParams(params);
    }
;

param_level2_list: param_level2_list param_level2 {
        $$ = $1;
        dynamic_cast<Ast::ParamsLevel2 *>($$)->elmtsl2.push_back($2);
    }
    | param_level2 {
        Ast::ElementVector elmtsl2;
        elmtsl2.push_back($1);
        $$ = new Ast::ParamsLevel2(elmtsl2);
    } 
;

toc_params_list: toc_params_list toc_params {
        $$ = $1;
        dynamic_cast<Ast::TocParams *>($$)->params.push_back($2);
    }
    | toc_params {
        Ast::ElementVector params;
        params.push_back($1);
        $$ = new Ast::TocParams(params);
    }
;

param_level2: "title" ":" "text" {
        $$ = new Ast::TitleParamL2($3);
    }
    | "date" ":" "text" {
        $$ = new Ast::DateParamL2($3);
    }
    | "author" ":" "text" {
        $$ = new Ast::AuthorParamL2($3);
    }
    | "institution" ":" "text" {
        $$ = new Ast::InstitutionParamL2($3);
    }
    | "subject" ":" "text" {
        $$ = new Ast::SubjectParamL2($3);
    }
    | "place" ":" "text" {
        $$ = new Ast::PlaceParamL2($3);
    }
    | "logo" ":" "imageText" {
        $$ = new Ast::LogoParamL2($3);
    }
;

toc_params: "depth" ":" "text" {
        $$ = new Ast::DepthParam($3);
    }
    | "spacing" ":" "text" {
        $$ = new Ast::SpacingParam($3);
    }
;

%%