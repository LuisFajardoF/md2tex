#ifndef _GEN_LATEX_H_
#define _GEN_LATEX_H_

#include <iostream> //debug
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <memory>

#include "gen_table.h"
#include "gen_list.h"

namespace Code 
{
    std::string documentClass();
    std::string documentClass(std::string& texclass);
    std::string beginDocument();
    std::string endDocument();
    std::string section(std::string& text, bool is_numbered);
    std::string subsection(std::string& text, bool is_numbered);
    std::string subsubsection(std::string& text, bool is_numbered);
    std::string paragraph(std::string& text);
    std::string subparagraph(std::string& text);
    std::string plainText(std::string& text);
    std::string newPage();
    std::string maketitle();
    std::string beginTitlePage();
    std::string endTitlePage();
    std::string beginFigure();
    std::string endFigure();
    std::string beginSubfigure();
    std::string endSubfigure();
    std::string centering();
    std::string caption(std::string& text);
    std::string pagenumbering(std::string& text);
    std::string toc();
    std::string lof();
    std::string lot();
    std::string pagenumberingAsSet(std::string& text, std::string& page_number);
    std::string singleFigureEnvironment(std::vector<std::string>& params, std::string& path);
    std::string multipleFigureEnvironment(std::vector<std::string>& params, std::string& path);
    std::string tocSpacingParam(std::string& text);
    std::string tocSpacingEnvironment(const std::string text);
    std::string tocDepthParam(int depth);
    std::string table(std::string& params, std::string& content);
    std::string list(std::string& params, std::string& content);
    
    // report cover
    std::string reportCoverLogo(std::string& text);
    std::string reportCoverTitle(std::string& text);
    std::string reportCoverInstitution(std::string& text);
    std::string reportCoverSubject(std::string& text);
    std::string reportCoverDate(std::string& text);
    std::string reportCoverPlace(std::string& text);
    std::string reportCoverAuthor(std::string& text);

    // default cover
    std::string defaultCoverLogo(std::string& text);
    std::string defaultCoverTitle(std::string& text);
    std::string defaultCoverAuthor(std::string& text);
    std::string defaultCoverDate(std::string& text);

    namespace Tables {
        std::string getColorTable(std::string& param);
        bool isCSV(std::string*& params_arr);
    }

    namespace Logic {
        std::string options(std::string param);
        std::string noSpacesStr(std::string& path);
        std::string trim(std::string& str);
        std::string includeGraphicsParams(std::vector<std::string>& params, bool singleFigure);
        std::string* getParams(std::string& params);
    };

    namespace Colored {
        void warningDefaultValue(std::string text);
    };
};

struct Package
{
    enum
    {
        Graphicx,
        Subfigure,
        Setspace,
        Siunitx,
        Booktabs,
        Xcolor,
        Colortbl,
        Pgfplotstable,
        Enumitem,
        Amssymb,
        Pifont
    };

    Package() {}
    ~Package() {}
    using PackInfo = std::unordered_map<unsigned int, std::string>;
    std::vector<std::string> packs;

    // packages
    PackInfo packInfo = {
        {Graphicx, "graphicx"},
        {Subfigure, "subfigure"},
        {Setspace, "setspace"},
        {Siunitx, "siunitx"},
        {Booktabs, "booktabs"},
        {Xcolor, "xcolor"},
        {Colortbl, "colortbl"},
        {Pgfplotstable, "pgfplotstable"},
        {Enumitem, "enumitem"},
        {Amssymb, "amssymb"},
        {Pifont, "pifont"},
    };

    void add(unsigned int pack);
    std::string packsCode();
};

struct Preamble
{
    enum 
    {
        Siunitx,
        ToDoList,
    };

    Preamble() {}
    ~Preamble() {}
    using Code = std::unordered_map<unsigned int, std::string>;
    std::vector<std::string> codes;

    // preamble code
    Code code;

    void add(unsigned int code);
    std::string getCode();
};

struct Color 
{
    enum
    {
        None = 0,
        White,
        Red,
        Green,
        Blue,
        Cyan,
        Yellow,
        Grey,
        Bright = 0x10,
        BrightRed    = Bright | Red,
        BrightGreen  = Bright | Green,
        LightGrey    = Bright | Grey,
        BrightWhite  = Bright | White,
        BrightYellow = Bright | Yellow,
    };

    std::unordered_map<unsigned int, std::string> colorInfo = {
        {None,      ""},    
        {White,     ""},    
        {Bright,    ""},    
        {Red,       "\033[0;31m"},    
        {Green,     "\033[0;32m"},    
        {Blue,      "\033[0;34m"},    
        {Cyan,      "\033[0;36m"},    
        {Yellow,    "\033[0;33m"},    
        {Grey,      "\033[1;30m"},    
        {LightGrey,     "\033[0;37m"},    
        {BrightRed,     "\033[1;31m"},    
        {BrightGreen,   "\033[1;32m"},    
        {BrightYellow,  "\033[1;33m"},    
        {BrightWhite,   "\033[1;37m"},
    };

    std::string open(unsigned int color);
    std::string close();

    Color() {}
    ~Color() {}
};

#endif