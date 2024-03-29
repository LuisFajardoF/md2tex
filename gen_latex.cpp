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
    std::string code = "\\end{document}";
    if (is_bibliography)
        code = "\t\\newpage\n\t\\printbibliography\n" + code;
    return code;
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

std::string Code::toc()
{
    return "\t\\tableofcontents\n";
}

std::string Code::lof()
{
    return "\t\\listoffigures\n";
}

std::string Code::lot()
{
    return "\t\\listoftables\n";
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

    fig_position = Code::Logic::options(params[params_size-1]);
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

std::string Code::tocSpacingParam(std::string& text)
{
    std::string code;
    
    if (text.compare("single") == 0)
        code += tocSpacingEnvironment("singlespacing");
    else if (text.compare("onehalf") == 0)
        code += tocSpacingEnvironment("onehalfspacing");
    else if (text.compare("double") == 0)
        code += tocSpacingEnvironment("doublespacing");
    else {
        code += tocSpacingEnvironment("singlespacing");
        Code::Colored::warningDefaultValue("spacing");
    }

    return code;
}

std::string Code::tocDepthParam(int depth)
{
    return "\t\\setcounter{tocdepth}{" + std::to_string(depth) + "}\n";
}

std::string Code::tocSpacingEnvironment(const std::string text)
{
    std::string begin = "\t\\begin{" + text + "}\n";
    std::string toc = "\t\t\\tableofcontents\n";
    std::string end = "\t\\end{" + text + "}\n";
    return begin + toc + end;
}

// Tables
std::string Code::table(std::string& params, std::string& content)
{
    std::string code, color;
    std::string* params_arr = Code::Logic::getParams(params);

    if (Code::Tables::isCSV(params_arr)) {
        Code::Logic::noSpacesStr(content);

        if (params_arr[1].find("style1") != std::string::npos) {
            color = Code::Tables::getColorTable(params_arr[1]);
            if (color == "undefined") {
                TableCSVStyle1 tableCSVStyle1(content, params_arr[0]);
                code = tableCSVStyle1.getCode();
            } 
            else {
                TableCSVStyle1Colored tableCSVStyle1Colored(content, params_arr[0], color);
                code = tableCSVStyle1Colored.getCode();
            }
        } 
        else if (params_arr[1].find("style2") != std::string::npos) {
            color = Code::Tables::getColorTable(params_arr[1]);
            if (color == "undefined") {
                TableCSVStyle2 tableCSVStyle2(content, params_arr[0]);
                code = tableCSVStyle2.getCode();
            } 
            else {
                TableCSVStyle2Colored tableCSVStyle2Colored(content, params_arr[0], color);
                code = tableCSVStyle2Colored.getCode();
            }
        }
        else {
            TableCSV tableCSV(content, params_arr[0]);
            code = tableCSV.getCode();
        }
    } 
    else {
        if (params_arr[1].find("style1") != std::string::npos) {
            color = Code::Tables::getColorTable(params_arr[1]);
            if (color == "undefined") {
                TableStyle1 tableStyle1(content, params_arr[0]);
                code = tableStyle1.getCode();
            }
            else {
                TableStyle1Colored tableStyle1Colored(content, params_arr[0], color);
                code = tableStyle1Colored.getCode();
            }
        } else if (params_arr[1].find("style2") != std::string::npos) {
            color = Code::Tables::getColorTable(params_arr[1]);
            if (color == "undefined") {
                TableStyle2 tableStyle2(content, params_arr[0]);
                code = tableStyle2.getCode();
            }
            else {
                TableStyle2Colored tableStyle2Colored(content, params_arr[0], color);
                code = tableStyle2Colored.getCode();
            }
        } 
        else {
            Table normalTable(content, params_arr[0]);
            code = normalTable.getCode();
        }
    }

    return code;
}

std::string Code::Tables::getColorTable(std::string& param)
{
    std::string color;
    std::string colors[] = {"black", "blue", "brown", "cyan", "darkgray", "gray", 
                            "green", "lightgray", "lime", "magenta", "olive", "orange", 
                            "pink", "purple", "red", "teal", "violet", "white", "yellow"};

    bool param_color = false, valid_color = false; 

    for (int i = 0; i < param.length(); i++) {
        if (param_color)
            color.push_back(param[i]);
        if (param[i] ==  '-')
            param_color = true;
    }

    for ( auto c : colors) {
        if (color == c ) {
            valid_color = true;
            break;
        }
    }

    return valid_color? color : "undefined";
}

bool Code::Tables::isCSV(std::string*& params_arr)
{
    if (params_arr[1].find("csv") != std::string::npos)
        return true;
    if (params_arr[2].find("csv") != std::string::npos)
        return true;
    
    return false;
}

// Lists
std::string Code::list(std::string& params, std::string& content)
{
    std::string code;    
    std::string* params_arr = Code::Logic::getParams(params);

    if (Code::Logic::trim(params_arr[0]) == "unordered-list") {
        auto u_list(new UnorderedList(params_arr, content));
        code = u_list->getCode();
    } else if (Code::Logic::trim(params_arr[0]) == "ordered-list") {
        auto o_list(new OrderedList(params_arr, content));
        code = o_list->getCode();
    } else if (Code::Logic::trim(params_arr[0]) == "nested-list") {
        auto n_list(new NestedList(params_arr, content));
        code = n_list->getCode();
    } else if (Code::Logic::trim(params_arr[0]) == "description-list") {
        auto d_list(new DescriptionList(params_arr, content));
        code = d_list->getCode();
    } else if (Code::Logic::trim(params_arr[0]) == "todo-list") {
        auto c_list(new ToDoList(params_arr, content));
        code = c_list->getCode();
    }

    return code;
}

// Bibliography
void Code::bibliography(std::string& content)
{
    new Bibliography(content);
}

// Code::Logic namespace
std::string Code::Logic::options(std::string param)
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

std::string Code::Logic::trim(std::string& str)
{
    auto begin = str.begin();
    while (begin != str.end() && std::isspace(*begin))
        begin++;

    auto end = str.end()-1;
    while (std::distance(begin, end) > 0 && std::isspace(*end))
        end--;
    return std::string(begin, end+1);
}

std::string* Code::Logic::getParams(std::string& params)
{
    std::string* params_arr = new std::string[3];
    params_arr[0] = params_arr[1] = params_arr[2] = "";

    for (int i = 0, off = 0; i < params.length(); i++) {
        if (params[i] != ';')
            params_arr[off].push_back(params[i]);
        else 
            off++;
    }

    return params_arr;
}

// Package struct
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

// Preamble struct
void Preamble::add(unsigned int preambleCode)
{
    std::vector<std::string>::iterator it;
    it = std::find(codes.begin(), codes.end(), code[preambleCode]);

    if (it == codes.end())
        codes.push_back(code[preambleCode]);
}

std::string Preamble::getCode()
{
    std::string code = "";

    for (auto it : codes)
        code += it;
    
    return code;
}

// Color struct 
std::string Color::open(unsigned int color)
{
    return colorInfo[color];
}

std::string Color::close()
{
    return "\033[0m";
}

// Colored namespace
void Code::Colored::warningDefaultValue(std::string text)
{
    Color color;
    std::cout << "The " 
            << color.open(Color::BrightYellow) 
            << text 
            << color.close() 
            << " parameter will take the default value" 
            << std::endl;
}