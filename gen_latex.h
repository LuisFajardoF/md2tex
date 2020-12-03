#ifndef _GEN_LATEX_H_
#define _GEN_LATEX_H_

#include <iostream> //debug
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

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
    std::string centering();
    std::string pagenumbering(std::string& text);
    std::string pagenumberingAsSet(std::string& text, std::string& page_number);
    std::string figureEnvironment(std::vector<std::string>& params, std::string& path);

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

    namespace Logic {
        void figurePosition(std::string param, std::string& position);
    };
};


struct Package
{
    enum
    {
        Graphicx,
    };

    Package() {}
    ~Package() {}
    using PackInfo = std::unordered_map<unsigned int, std::string>;
    std::vector<std::string> packs;

    // packages
    PackInfo packInfo = {
        {Graphicx, "graphicx"},
    };

    void add(unsigned int pack);
    std::string packsCode();
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