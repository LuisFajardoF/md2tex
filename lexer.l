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
    bool is_image_path = false; // activa la regla [a-zA-Z0-9_.-/] para el path de imagenes
    bool is_table_env = true; 
%}

%x TEXT 
%x PARAMS 
%x LOGOTEXT
%x LABELTEXT
%x FIGURE TABLE

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
    if (is_param) {
        if (is_image_path) {
            is_image_path = false;
            BEGIN(LOGOTEXT);
        }
        return makeToken(yytext, yyleng, Token::Colon);
    }
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

"report" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Report);
    }
    BEGIN(TEXT);
}

"numbered" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Numbered);
    BEGIN(TEXT);
}

"pagenumbering" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::PageNumbering);
    BEGIN(TEXT);
}

"toc" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::ToC);
    BEGIN(TEXT);
}

"lof" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::LoF);
    BEGIN(TEXT);
}

"lot" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::LoT);
    BEGIN(TEXT);
}

"depth" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Depth);
    BEGIN(TEXT);
}

"spacing" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Spacing);
    BEGIN(TEXT);
}

"custom" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Custom);
    BEGIN(TEXT);
}

"gobble" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Gobble);
    }
    BEGIN(TEXT);
}

"arabic" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Arabic);
    }
    BEGIN(TEXT);
}

"roman" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Roman);
    }
    BEGIN(TEXT);
}

"Roman" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Roman);
    }
    BEGIN(TEXT);
}

"alph" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Alph);
    }
    BEGIN(TEXT);
}

"Alph" {
    if (is_param) {
        yylval.emplace<std::string>(yytext, yyleng);
        return makeToken(yytext, yyleng, Token::Alph);
    }
    BEGIN(TEXT);
}

"set" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Set);
    BEGIN(TEXT);
}

"institution" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Institution);
    BEGIN(TEXT);
}

"subject" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Subject);
    BEGIN(TEXT);
}

"place" {
    if (is_param)
        return makeToken(yytext, yyleng, Token::Place);
    BEGIN(TEXT);
}

"logo" {
    if (is_param) {
        is_image_path = true;
        return makeToken(yytext, yyleng, Token::Logo);
    }
    BEGIN(TEXT);
}

"!["[a-zA-Z0-9 ,;.:={}\n]+"]("[a-zA-Z0-9_.:/ -,\n]+")" {
    auto offset = strlen(yytext);

    while(yytext[offset] != '!')
        unput(yytext[--offset]);
    BEGIN(FIGURE);
    return makeToken(yytext, yyleng, Token::Figure);
}

<FIGURE>"[" {
    return makeToken(yytext, yyleng, Token::OpenBracket);
}

<FIGURE>"]" {
    return makeToken(yytext, yyleng, Token::CloseBracket);
}

<FIGURE>[a-zA-Z0-9_./= \n-]+ {
    yylval.emplace<std::string>(yytext, yyleng);
    return makeToken(yytext, yyleng, Token::FigureLabel);
}

<FIGURE>"{" {
    return makeToken(yytext, yyleng, Token::OpenKey);
}

<FIGURE>"}" {
    return makeToken(yytext, yyleng, Token::CloseKey);
}

<FIGURE>"," {
    return makeToken(yytext, yyleng, Token::Comma);
}

<FIGURE>"(" {
    return makeToken(yytext, yyleng, Token::OpenPar);
}

<FIGURE>")" {
    BEGIN(INITIAL);
    return makeToken(yytext, yyleng, Token::ClosePar);
}

<FIGURE>";" {
    return makeToken(yytext, yyleng, Token::Semicolon);
}

<FIGURE>":" {
    return makeToken(yytext, yyleng, Token::Colon);
}

<FIGURE>. { /* default rule FIGURE */ }

"!["[a-zA-Z0-9 \n\t:|.<>-]+"]{"[a-zA-Z0-9 \n\t:|.<>-]+"}" {
    auto offset = strlen(yytext);

    while(yytext[offset] != '!')
        unput(yytext[--offset]); 
    BEGIN(TABLE);
    return makeToken(yytext, yyleng, Token::Table); 
}

<TABLE>[a-zA-Z0-9 \n\t:|.<>-]+ {
    yylval.emplace<std::string>(yytext, yyleng);
    // std::cout << yytext << std::endl;
    return makeToken(yytext, yyleng, Token::TableLabel);
}

<TABLE>"[" {
    return makeToken(yytext, yyleng, Token::OpenBracket);
}

<TABLE>"]" {
    return makeToken(yytext, yyleng, Token::CloseBracket);
}

<TABLE>"{" {
    return makeToken(yytext, yyleng, Token::OpenKey);
}

<TABLE>"}" {
    BEGIN(INITIAL);
    return makeToken(yytext, yyleng, Token::CloseKey);
}

<TABLE>. { /* default rule TABLE */ }

[a-zA-Z0-9#{}:;<>!/¡`"@$%&*()-_\[\]=+^~\\'.,¿?] {
    yylval.emplace<std::string>(yytext, yyleng);
    if (yytext[0] != ' ')
        unput(yytext[0]);

    BEGIN(TEXT);
}

<LOGOTEXT>[a-zA-Z0-9_./-]{-}[ ]+ {
    yylval.emplace<std::string>(yytext, yyleng);
    BEGIN(INITIAL);
    return makeToken(yytext, yyleng, Token::ImageText);
}

<LOGOTEXT>. { /* default rule LOGOTEXT */ }

<TEXT>[a-zA-Z0-9#{}:;<>!/¡`"@$%&*()-_\[\]=+^~\\'.,¿? ]* {
    text = std::string(yytext, yyleng);
    bool is_emphasis = false;
    std::string special_cmd;

    auto offset = 0;
    while(text[offset]) 
    {
        // validacion temporal para saltos de linea
        if (text[offset] == ' ' 
            && text[offset+1] == ' '
            && text[offset+2] == '\0') {
                special_cmd = "\\newline\n";
                text.insert(offset, special_cmd);
                offset += special_cmd.length();
                // text.erase(offset, 2);
            }

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