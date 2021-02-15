#include "gen_bib.h"

Bibliography::Bibliography(std::string& content)
{
    this->content = content;
    getBibData();
    print();
}

std::string Bibliography::getCode() { return code; }

void Bibliography::print()
{
    for (auto bd : bibDataVector) {
        std::cout << "key: " << bd.key << " doc. kind: " << bd.document_kind << std::endl;
        for (auto iv : bd.info_values)
            std::cout << "field: " << iv.first << " value: " << iv.second << std::endl;
    }
}

void Bibliography::getBibData()
{
    auto offset = 0;
    std::vector<std::string> values;

    while (content[offset]) {
        if (content[offset] == '[') {
            while (content[++offset] != ']')
                key.push_back(content[offset]);            
        }
        if (content[offset] == ':') {
            while (content[++offset] != '{')
                document_kind.push_back(content[offset]);
            while (content[++offset] != '}')
                info_values.push_back(content[offset]);
            
            key = trim(key);
            document_kind = trim(document_kind);
            values = getBibValues();
            bibDataVector.push_back(BibData(key, document_kind, values));
            key.clear();
            document_kind.clear();
            info_values.clear();
        }
        offset++;
    }
}

std::vector<std::string> Bibliography::getBibValues()
{
    std::string line;
    std::vector<std::string> values;

    for (auto it = 0; info_values[it]; it++) {
        if (info_values[it] == '\n') {
            if (line[0] != '\0')
                values.push_back(line);
            line.clear();
        } else line.push_back(info_values[it]);
    }
    return values;
}

/****************** BibData ******************/

BibData::BibData(std::string& key, std::string& document_kind, std::vector<std::string>& values)
{
    this->key = key;
    this->document_kind = document_kind;
    this->values = values;

    getInfoValues();
}

void BibData::getInfoValues()
{
    char* token;
    std::string field;
    std::string value;

    for (auto val : values) {
        token = strtok(const_cast<char*>(val.c_str()), ":");
        field = trim(std::string(token));
        token = strtok(NULL, "\n");
        value = trim(std::string(token));
        info_values.push_back({field, value});
    }
}

/**************** trim function *************/

std::string trim(std::string str)
{
    auto begin = str.begin();
    while (begin != str.end() && std::isspace(*begin))
        begin++;

    auto end = str.end()-1;
    while (std::distance(begin, end) > 0 && std::isspace(*end))
        end--;
    return std::string(begin, end+1);
}