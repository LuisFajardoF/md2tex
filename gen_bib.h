#ifndef _GEN_BIB_H_
#define _GEN_BIB_H_

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>

extern bool dev_mode;

class BibData
{
    public:
        BibData(std::string& key, std::string& document_kind, std::vector<std::string>& values);

        void getInfoValues();
        
        std::string key;
        std::string document_kind;
        std::vector<std::string> values;
        std::vector<std::pair<std::string, std::string>> info_values;
};

class Bibliography
{
    public:
        Bibliography(std::string& content);

        std::string getCode();
        void getBibData();
        std::vector<std::string> getBibValues();
        void print();

    private:
        std::string content;
        std::string code;
        std::string key;
        std::string document_kind;
        std::string info_values;
        std::vector<BibData> bibDataVector;
        std::vector<std::string> bib_values;
};

std::string trim(std::string str);

#endif