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
    bool is_emphasis = false;

    auto offset = 0;
    while(text[offset]) 
    {

        AuxFuncs::emphasisCommands(text, offset, is_emphasis);
            
        switch(text[offset]) 
        {
            case '#':
            case '{':
            case '}':
            case '$':
            case '%':
            case '&':
            case '_':
            case '\'':
            case '~':
            case '^':
                text.insert(offset, "\\");
                offset++;
            break;
            case '<':
                AuxFuncs::specialLatexCommands('<', text, offset);
            break;
            case '>':
                AuxFuncs::specialLatexCommands('>', text, offset);
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
        case '\\': str = "\\textbackslash"; break;
        default:
            break;

    }

    text.insert(offset, str);
    offset += str.length();
}

bool AuxFuncs::emphasisCommands(std::string& text, int& offset, bool& is_emphasis)
{
    std::string special_cmd;
    int state = 0;


    if (!is_emphasis) 
    {
        is_emphasis = true;

        if ((text[offset] == '*' && text[offset+1] == '*' && text[offset+2] != ' ' && text[offset+2] != '\0')
            || (text[offset] == '_' && text[offset+1] == '_' && text[offset+2] != ' ' && text[offset+2] != '\0'))
            state = 1;  //begin bold validate
        else if ((text[offset] == '*' && text[offset+1] != '*' && text[offset+1] != ' ')
            || (text[offset] == '_' && text[offset+1] != '_' && text[offset+1] != ' '))
            state = 2; //begin italic validate
        else if (text[offset] == '~' && text[offset+1] == '~' && text[offset+2] != ' ' && text[offset+2] != '\0')
            state = 3; //begin underline validate
    
        switch(state)
        {
            case 1:
                special_cmd = "\\textbf{";
                text.insert(offset, special_cmd);
                offset += special_cmd.length();
                text.erase(offset, 2);
                break;
            case 2:
                special_cmd = "\\textit{";
                text.insert(offset, special_cmd);    
                offset += special_cmd.length();
                text.erase(offset, 1);
                break; 
            case 3:
                special_cmd = "\\underline{";
                text.insert(offset, special_cmd);    
                offset += special_cmd.length();
                text.erase(offset, 2);
                break; 
            default:
                is_emphasis = false;
                break;
        }
    } 
    else {
        is_emphasis = false;

        if ((text[offset] == '*' && text[offset+1] == '*' && text[offset-1] != ' ')
            || (text[offset] == '_' && text[offset+1] == '_' && text[offset-1] != ' ')
            || (text[offset] == '~' && text[offset+1] == '~' && text[offset-1] != ' '))
            state = 1; //end bold and underline validate
        else if ((text[offset] == '*' && text[offset-1] != ' ')
            || (text[offset] == '_' && text[offset-1] != ' '))
            state = 2; //end italic and validate

        switch(state)
        {
            case 1:
                special_cmd = "}";
                text.insert(offset, special_cmd);
                offset += special_cmd.length();
                text.erase(offset, 2);
                break;
            case 2:
                special_cmd = "}";
                text.insert(offset, special_cmd);    
                offset += special_cmd.length();
                text.erase(offset, 1);
                break;
            default:
                is_emphasis = true;
                break;
        }
    }
    return is_emphasis;
}