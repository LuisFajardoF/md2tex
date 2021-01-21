#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <dirent.h>
#include <unistd.h>

#include "emoji.h"

enum class Option {
    Default,
    ManualConfig,
    Help,
    Version,
    Invalid
};

std::string execCLI(const std::string& cmd);
void getLinesOutput(std::string& cli_output, std::vector<std::string>& lines);
void getNamePackages(std::vector<std::string>& lines, std::vector<std::string>& packages);
bool checkPackagesInstalled(std::vector<std::string>& packages);
Option getOption(std::string option);
void initFoldersVector(std::string username);
bool findFolders();
bool folderExists(const std::string& path);

void help();
void version();
void invalidOption();

// paquetes de latex requeridos por md2tex
std::vector<std::string> packs_required = {
    "subfigure",
};

// carpetas requeridas en /home/<user>/texmf/tex/latex/
std::vector<std::string> folders_required;

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

    std::string open(unsigned int color) { return colorInfo[color]; }
    std::string close() { return "\033[0m"; }

    Color() {}
    ~Color() {}
};

#endif
