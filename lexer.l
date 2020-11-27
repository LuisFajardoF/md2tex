%option noyywrap yylineno reentrant

%{
    #include "lexer.h"
    #define YY_EXTRA_TYPE std::istream*
    #define YY_DECL int Lexer::_getNextToken(semantic_type& yylval, yyscan_t yyscanner)
    #define YY_INPUT(buffer, result, max_size) \
        do { \
            std::istream *in = yyget_extra(yyscanner); \
            in->read(buffer, max_size); \
            result = in->gcount(); \
        } while(false)
    
    bool is_param = false;
%}

%x TEXT
%x PARAMS

%%

"# " {
    BEGIN(TEXT);
    return makeToken(yytext, yyleng, Token::H1);
}

"## " {
    BEGIN(TEXT);
    return makeToken(yytext, yyleng, Token::H2);
}

"### " {
    BEGIN(TEXT);
    return makeToken(yytext, yyleng, Token::H3);
}

"#### " {
    BEGIN(TEXT);
    return makeToken(yytext, yyleng, Token::H4);
}

"##### " {
    BEGIN(TEXT);
    return makeToken(yytext, yyleng, Token::H5);
}

"---" {
    return makeToken(yytext, yyleng, Token::NewPage);
}

"!--" {
    is_param = true;
    return makeToken(yytext, yyleng, Token::OpenParam);
}

"--!" {
    is_param = false;
    return makeToken(yytext, yyleng, Token::CloseParam);
}

":" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Colon);
    BEGIN(TEXT);
}

"{" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::OpenKey);
    BEGIN(TEXT);
}

"}" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::CloseKey);
    BEGIN(TEXT);
}

"class" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Class);
    BEGIN(TEXT);
}

"cover" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Cover);
    BEGIN(TEXT);
}

"title" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Title);
    BEGIN(TEXT);
}

"author" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Author);
    BEGIN(TEXT);
}

"date" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Date);
    BEGIN(TEXT);
}

"default" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Default);
    }
    BEGIN(TEXT);
}

[a-zA-Z0-9#{}:;<>!/¡`"@$%&*()-_\[\]=+^~\\'.,¿?] {
    yylval.emplace<std::string>(yytext, yyleng);
    if (yytext[0] != ' ')
        unput(yytext[0]);
    BEGIN(TEXT);
}

<TEXT>[a-zA-Z0-9 #{}:;<>!/¡`"@$%&*()-_\[\]=+^~\\'.,¿?]* {
    text = std::string(yytext, yyleng);
    std::string special_cmd;

    auto offset = 0;
    while(text[offset]) 
    {
        switch(text[offset]) 
        {
            case '#':
            case '{':
            case '}':
            case '$':
            case '%':
            case '&':
            case '_':
                text.insert(offset, "\\");
                offset++;
            break;
            case '<':
                AuxFuncs::specialLatexCommands('<', text, offset);
            break;
            case '>':
                AuxFuncs::specialLatexCommands('>', text, offset);
            break;
            case '^':
                AuxFuncs::specialLatexCommands('^', text, offset);
            break;
            case '~':
                AuxFuncs::specialLatexCommands('~', text, offset);
            break;
            case '\\':
                AuxFuncs::specialLatexCommands('\\', text, offset);
            break;
            default:
                break;
        }
        offset++;
    }

    yylval.emplace<std::string>(text);
    BEGIN(INITIAL);
    return Token::Text;
}

[ \n]       { }
^[ \t]*\n   { /*wsp*/ }

. {
    std::cout << yytext << std::endl;
    return makeToken(yytext, yyleng, Token::Error);
}

%%

Lexer::Lexer(std::istream &in) : in(in)
{
    yylex_init_extra(&in, &scanner);
}

Lexer::~Lexer()
{
    yylex_destroy(scanner);
}

int Lexer::getLineNo()
{
    return yyget_lineno(scanner);
}

int Lexer::makeToken(const char *txt, int len, int tk)
{
    std::string tt(txt, len);
    text = std::move(tt);
    return tk;
}

void AuxFuncs::specialLatexCommands(char character, std::string& text, int& offset)
{
    std::string str;

    // erase a character within the text
    text.erase(offset, 1);

    switch (character)
    {
        case '<': str = "\\textless"; break;
        case '>': str = "\\textgreater"; break;
        case '^': str = "\\textasciicircum"; break;
        case '~': str = "\\textasciitilde"; break;
        case '\\': str = "\\textbackslash"; break;
        default:
            break;

    }

    text.insert(offset, str);
    offset += str.length();
}