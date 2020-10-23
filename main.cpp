#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "lexer.h"
#include "ast.h"

std::string outFileName(char const *arg);
void createLatexFolders();

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1], std::ios::in);    
    std::ofstream out;
    string_t code;

    Lexer lexer(in);
    Ast::AstNode *root;
    Expr::Parser parser(lexer, root);

    createLatexFolders();

    try {
        parser.parse();
        code = root->genLatex();
        out.open(outFileName(argv[1]));
        out << code;
    } catch (std::string &err) {
        std::cerr << err << '\n';
    }
    in.close();
}

std::string outFileName(char const *arg)
{
    std::string file_name("");

    auto idx = 0;
    while(arg[idx] != '\0') {
        if (arg[idx] == '/') 
            file_name = "../latex/tex/";
        idx++;
        file_name.push_back(arg[idx]);
    }
    
    idx = file_name.size()-1;
    while (file_name[idx--] != '.')
        file_name.pop_back();

    file_name += "tex";
    return file_name;
}

void createLatexFolders()
{
    mkdir("../latex", S_IRWXU);
    mkdir("../latex/tex", S_IRWXU);
}