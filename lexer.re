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

            "#" {
                text = getText();
                return Token::H1;
            }

            "##" {
                text = getText();
                return Token::H2;
            }

            "###" {
                text = getText();
                return Token::H3;
            }

            [a-zA-Z0-9']+ {
                text = getText();
                yylval->emplace<std::string>(text);
                // std::cout << text << '\n';
                return Token::Word;
            }

            [ \t] {continue;}
            "\n" {lineno++; continue;}

            '\x00' { return Token::Eof; }

            * { return TkError(); }
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