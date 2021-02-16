#ifndef _GEN_BIB_H_
#define _GEN_BIB_H_

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <algorithm>
#include <fstream>

extern bool dev_mode;
using InfoValues = std::vector<std::pair<std::string, std::string>>;
std::string trim(std::string str);

class BibData
{
    public:
        BibData(std::string& key, std::string& kind, InfoValues& infoValues);
        std::string getBibCode();
    
    private:
        std::string key;
        std::string kind;
        InfoValues infoValues;
};

class Bibliography
{
    public:
        Bibliography(std::string& content);
        std::string getCode();

    private:
        std::string content;
        std::string bib_path;
        std::vector<BibData> bibDataVector;
        
        void getBibData();
        void genBib();
        std::vector<std::string> getBibValues(std::string& info_values);
        InfoValues getInfoValues(std::vector<std::string>& values);
};

#endif