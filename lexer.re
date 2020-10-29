#include "lexer.h"

/*!max:re2c*/

void Lexer::yyfill(size_t state_number)
{
    do {
        FillStatus status = context.fill(state_number);
        switch(status) {
            case FillStatus::Eof: TkEof(); break;
            case FillStatus::Error: TkError(); break;
            default:
                break;
        }
    } while ( 0 );
}

int Lexer::getNextToken(semantic_type *yylval)
{
    while( true ) {
        context.token = context.current;
        /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:define:YYCURSOR = context.current;
            re2c:define:YYLIMIT = context.limit;
            re2c:define:YYMARKER = context.marker;
            re2c:define:YYFILL = "yyfill";
            re2c:define:YYFILL:naked = 0;

            TEXT = [a-zA-Z0-9\\'!@$%&*()_-+=|\[\]{}":;/?.>,<~`\\n];
            TEXT_WITH_SPACES = [a-zA-Z0-9\\'!@#$%&*()_-+=|\[\]{}":;/?.>,<~` ];
            TEXT_PARAM = [a-zA-Z0-9];

            "#"     { return Token::H1; }
            "##"    { return Token::H2; }
            "###"   { return Token::H3; }
            "####"  { return Token::H4; }
            "#####" { return Token::H5; }
            "---"   { return Token::NewPage; }
            "!--"   { return Token::OpenParam; }
            "--!"   { return Token::CloseParam; }
            ":"     { return Token::Colon; }
            "{"     { return Token::OpenKey; }
            "}"     { return Token::CloseKey; }
            "class" { return Token::Class;}
            "cover" { return Token::Cover; }
            "title" { return Token::Title; }
            "author" { return Token::Author; }
            "date"  { return Token::Date; }
            "default" { 
                text = getText();
                yylval->emplace<std::string>(text); 
                return Token::Default; 
            }
            
            TEXT    { goto block_text; }

            [ \t]   { continue; }
            "\n"    { lineno++; continue; }
            '\x00'  { return Token::Eof; }
            *       { return TkError(); }
        */

        block_text:
            /*!re2c
                TEXT_WITH_SPACES* {
                    text = getText();
                    yylval->emplace<std::string>(text);
                    return Token::Text;
                }
                "\n" { continue; }
            */
    }
}

Lexer::Context::Context(std::istream& in)
    : in(in), buffer(SIZE + YYMAXFILL)
{
    limit = buffer.data() + SIZE;
    current = limit;   
    token = limit;   
    eof = false;   
}

Lexer::FillStatus Lexer::Context::fill(size_t need) {
    if(eof)
        return FillStatus::Eof;
    const size_t free = token - buffer.data();
    if ( free < need) 
        return FillStatus::Error;
    memmove(buffer.data(), token, limit - token);
    limit -= free;
    current -= free;
    token -= free;
    marker -= free;
    in.read(limit, free);
    limit += in.gcount();

    if ( limit < buffer.data() + SIZE) {
        eof = true;
        memset(limit, 0, YYMAXFILL);
        limit += YYMAXFILL;
    }
    return FillStatus::Ok;
}