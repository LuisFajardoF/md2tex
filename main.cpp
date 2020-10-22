#include <iostream>
#include <fstream>
#include "lexer.h"

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1], std::ios::in);    
    Lexer lexer(in);

    try {
        Expr::Parser parser(lexer);
        parser.parse();
    } catch (std::string &err) {
        std::cerr << err << '\n';
    }
    in.close();
}