#include "gen_latex.h"

std::string Code::documentClass()
{
    return "\\documentclass{article}\n\n";
}

std::string Code::documentClass(std::string& texclass)
{
    return "\\documentclass{" + texclass + "}\n\n";
}

std::string Code::beginDocument()
{
    return "\\begin{document}\n";
}

std::string Code::endDocument()
{
    return "\\end{document}";
}

std::string Code::section(std::string& text, bool is_numbered)
{
    if (is_numbered)
        return "\n\t\\section{" + text + "}\n";
    return "\n\t\\section*{" + text + "}\n";
}

std::string Code::subsection(std::string& text, bool is_numbered)
{
    if (is_numbered)
        return "\n\t\\subsection{" + text + "}\n";
    return "\n\t\\subsection*{" + text + "}\n";
}

std::string Code::subsubsection(std::string& text, bool is_numbered)
{
    if (is_numbered)
        return "\n\t\\subsubsection{" + text + "}\n";
    return "\n\t\\subsubsection*{" + text + "}\n";
}

std::string Code::paragraph(std::string& text)
{
    return "\n\t\\paragraph{" + text + "}\n";
}

std::string Code::subparagraph(std::string& text)
{
    return "\n\t\\subparagraph{" + text + "}\n";
}

std::string Code::plainText(std::string& text)
{
    return "\t" + text + "\n";
}

std::string Code::newPage()
{
    return "\t\\newpage\n";
}

std::string Code::maketitle()
{
    return "\t\\maketitle\n";
}

std::string Code::beginTitlePage()
{
    return "\t\\begin{titlepage}\n";
}

std::string Code::endTitlePage()
{
    return "\t\\end{titlepage}\n";
}

std::string Code::beginFigure()
{
    return "\n\t\\begin{figure}";
}

std::string Code::endFigure()
{
    return "\t\\end{figure}\n";
}

std::string Code::beginSubfigure()
{
    return "\t\t\\begin{subfigure}";
}

std::string Code::endSubfigure()
{
    return "\t\t\\end{subfigure}\n";
}

std::string Code::centering()
{
    return "\t\t\\centering\n";
}

std::string Code::caption(std::string& caption)
{
    return "\t\t\\caption{" + caption + "}\n";
}

std::string Code::reportCoverTitle(std::string& text)
{
    return "\t\t\\Huge " + text + " \\par\n" +
            "\t\t\\vfill\n";
}

std::string Code::reportCoverDate(std::string& text)
{
    return "\t\t\\Large " + text + " \\par\n"
            "\t\t\\vfill\n";
}

std::string Code::reportCoverInstitution(std::string& text)
{
    return "\t\t\\scshape\\LARGE " + text + " \\par\n"
            "\t\t\\vfill\n";
}

std::string Code::reportCoverSubject(std::string& text)
{
    return "\t\t\\LARGE " + text + " \\par\n"
            "\t\t\\vfill\n";
}

std::string Code::reportCoverLogo(std::string& text)
{
    return "\t\t\\includegraphics[width=0.2\\textwidth]{../images/" + text + "}\\par\n";
}

std::string Code::defaultCoverLogo(std::string& text)
{
    return "\t\\begin{figure}[!t]\n"
            "\t\t\\centering\n"
            "\t\t\\includegraphics[width=0.2\\textwidth]{../images/" + text + "}\n"
            "\t\\end{figure}\n";
}

std::string Code::reportCoverPlace(std::string& text)
{
    return "\t\t\\large " + text + " \\par\n"
            "\t\t\\vfill\n";
}

std::string Code::reportCoverAuthor(std::string& text)
{
    std::string temp_text, code;
    std::vector<std::string> authors;
    int is_coauthor = text.find_first_of("&");

    if (is_coauthor != -1) {
        code += "\t\t\\large Autores \\par\n";
        for (auto offset = 0; text[offset]; offset++) {
            if (text[offset] == '&') {
                authors.push_back(temp_text);
                temp_text = "";
            } else if (text[offset] == '\\') {
            } else if (text[offset+1] == '\0') {
                temp_text.push_back(text[offset]);
                authors.push_back(temp_text);
            } else 
                temp_text.push_back(text[offset]);
        }
        for (auto i = 0; i < authors.size(); i++)
            code += "\t\t\\Large " + authors[i] + " \\par\n";
        code += "\t\t\\vfill\n";
    } 
    else {
        code += "\t\t\\large Autor \\par\n\t\t\\Large " +
                text + " \\par\n\t\t\\vfill\n";
    }
    return code;
}

std::string Code::defaultCoverTitle(std::string& text)
{
    return "\t\\title{" + text + "}\n";
}

std::string Code::defaultCoverAuthor(std::string& text)
{
    std::string temp_text, code;
    std::vector<std::string> authors;

    for (auto offset = 0; text[offset]; offset++) {
        if (text[offset] == '&') {
            temp_text += "\\and";
        } else if (text[offset] == '\\') {
        } else
            temp_text.push_back(text[offset]);
    }
    
    code += "\t\\author{" + temp_text + "}\n";
    return code;
}

std::string Code::defaultCoverDate(std::string& text)
{
    return "\t\\date{" + text + "}\n";
}

std::string Code::pagenumbering(std::string& text)
{
    return "\t\\pagenumbering{" + text + "}\n";
}

std::string Code::pagenumberingAsSet(std::string& text, std::string& page_number)
{
    return "\t\\pagenumbering{" + text + "}\n"
            "\t\\setcounter{page}{" + page_number + "}\n";
}

std::string Code::singleFigureEnvironment(std::vector<std::string>& params, std::string& path)
{
    int params_size = params.size();
    std::string fig_position; 
    std::string fig_params;
    
    if (params_size == 1)
        return Code::beginFigure() + "[!h]\n" + Code::centering() +
                "\t\t\\includegraphics[width=4cm, height=4cm]"
                "{../images/" + Code::Logic::noSpacesStr(path) + "}\n" + 
                Code::caption(params[0]) + Code::endFigure();

    fig_position = Code::Logic::figurePosition(params[params_size-1]);
    fig_params = Code::Logic::includeGraphicsParams(params, true);

    return Code::beginFigure() + "[" + fig_position + "]\n" + Code::centering() +
            "\t\t\\includegraphics[" + fig_params + "]{../images/" +
            Code::Logic::noSpacesStr(path) + "}\n" + Code::caption(params[0]) + 
            Code::endFigure();
}

std::string Code::multipleFigureEnvironment(std::vector<std::string>& params, std::string& path)
{
    int params_size = params.size();
    std::string fig_params;

    if (params_size == 1)
        return "\t\t\\subfigure[" + params[0] + "]{\n\t\t\t\\includegraphics[width=4cm, height=4cm]{"
            "../images/" + Code::Logic::noSpacesStr(path) + "}\n\t\t}\n";
    
    fig_params = Code::Logic::includeGraphicsParams(params, false);
    
    return "\t\t\\subfigure[" + params[0] + "]{\n\t\t\t\\includegraphics[" +
        fig_params + "]{../images/" + Code::Logic::noSpacesStr(path) + "}\n\t\t}\n";
}

// Code::Logic namespace
std::string Code::Logic::figurePosition(std::string param)
{
    std::string fig_position = "";

    for(auto it = 0; param[it]; it++) {
        switch(param[it]) {
            case 'o': fig_position.push_back('!'); break;
            case 'b': 
            case 'h': 
            case 'p': 
            case 't': 
                fig_position.push_back(param[it]);
                break;
            default: break;
        }
    }

    return fig_position;
}

std::string Code::Logic::includeGraphicsParams(std::vector<std::string>& params, bool singleFigure)
{
    std::string str_param = "";
    auto params_size = singleFigure? params.size()-1 : params.size();

    for (auto i = 1; i < params_size; i++) {
        char *token = std::strtok(const_cast<char*>(params[i].c_str()), "= \t\n");
        
        while (token != NULL) 
        {
            if (!std::strncmp(token, "w", 1))
                str_param += "width=";
            else if (!std::strncmp(token, "h", 1)) 
                str_param += "height=";
            else if (!std::strncmp(token, "s", 1))
                str_param += "scale=";
            else if (!std::strncmp(token, "a", 1))
                str_param += "angle=";
            else {
                str_param += token;
                if (i < params_size-1)
                    str_param += ", ";
            }

            token = std::strtok(NULL, "= \t\n");
        } 
        free(token);
    }
    return str_param;
}

std::string Code::Logic::noSpacesStr(std::string& path)
{
    path.erase(std::remove_if(path.begin(), path.end(), 
            [](char &ch) { 
                return std::isspace<char>(ch, std::locale::classic());
            }),
            path.end());
    
    return path;
}

// Package namespace
void Package::add(unsigned int pack)
{
    std::vector<std::string>::iterator it;
    it = std::find(packs.begin(), packs.end(), packInfo[pack]);

    if (it == packs.end())
        packs.push_back(packInfo[pack]);
}

std::string Package::packsCode()
{
    std::string code = "";

    for (auto it : packs)
        code += "\\usepackage{" + it + "}\n";
    
    if (code != "") 
        code += "\n";
    return code;
}

// Color namespace 
std::string Color::open(unsigned int color)
{
    return colorInfo[color];
}

std::string Color::close()
{
    return "\033[0m";
}