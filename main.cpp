#include "main.h"

bool dev_mode;

int main(int argc, char* argv[])
{
    if (std::string(argv[1]) == "--version") {
        std::cout << "v1.2.0" << std::endl;
        return 0;
    }

    std::ifstream in(argv[1], std::ios::in);    
    std::ofstream out;
    string_t code;

    Lexer lexer(in);
    Ast::AstNode *root;
    Expr::Parser parser(lexer, root);

    if (argv[2] != NULL)
        dev_arg = std::string(argv[2]);

    flagEval(dev_arg);
    
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
    std::string in_path;
    std::string file_name("");

    if (arg != NULL)
        in_path = std::string(arg);

    for (int i = in_path.length()-1; i >= 0; i--)
    {
        if (in_path[i] == '/')
            break;
        file_name.insert(file_name.begin(), in_path[i]);
    }

    for (int i = file_name.length()-1; file_name[i] != '.'; i--)
        file_name.pop_back();
    
    if (dev_arg == "--dev")
        return "../latex/tex/" + file_name + "tex";
    return "latex/tex/" + file_name + "tex";
}

// solo para entorno de desarrollo
void createLatexFoldersDev()
{
    mkdir("../latex", S_IRWXU);
    mkdir("../latex/tex", S_IRWXU);
    mkdir("../latex/images", S_IRWXU);
}

void createLatexFolders()
{
    mkdir("latex", S_IRWXU);
    mkdir("latex/tex", S_IRWXU);
    mkdir("latex/images", S_IRWXU);
}

void flagEval(std::string flag)
{
    if (flag == "--dev") {
        createLatexFoldersDev();
        dev_mode = true;
    }
    else {
        createLatexFolders(); 
        dev_mode = false;
    }
}