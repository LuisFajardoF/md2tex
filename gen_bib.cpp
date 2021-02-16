#include "gen_bib.h"

Bibliography::Bibliography(std::string& content)
{
    this->content = content;
    getBibData();
    bib_path = dev_mode? "../latex/bib" : "latex/bib"; 
    mkdir(bib_path.c_str(), S_IRWXU);
    genBib();
}

std::string Bibliography::getCode() 
{
    std::string code;
    for (auto bd : bibDataVector) {
        code += bd.getBibCode();
    }
    return code;
}

void Bibliography::getBibData()
{
    auto offset = 0;
    std::vector<std::string> values;
    InfoValues infoValues;
    std::string key, kind, info_values;

    while (content[offset]) {
        if (content[offset] == '[') {
            while (content[++offset] != ']')
                key.push_back(content[offset]);            
        }
        if (content[offset] == ':') {
            while (content[++offset] != '{')
                kind.push_back(content[offset]);
            while (content[++offset] != '}')
                info_values.push_back(content[offset]);
            
            key = trim(key);
            kind = trim(kind);
            values = getBibValues(info_values);
            infoValues = getInfoValues(values);
            bibDataVector.push_back(BibData(key, kind, infoValues));
            key.clear();
            kind.clear();
            info_values.clear();
        }
        offset++;
    }
}

InfoValues Bibliography::getInfoValues(std::vector<std::string>& values)
{
    InfoValues infoValues;
    char* token;
    std::string field, value;

    for (auto val : values) {
        token = strtok(const_cast<char*>(val.c_str()), ":");
        field = trim(std::string(token));
        token = strtok(NULL, "\n");
        value = trim(std::string(token));
        infoValues.push_back({field, value});
    }

    return infoValues;
}

std::vector<std::string> Bibliography::getBibValues(std::string& info_values)
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

void Bibliography::genBib()
{
    std::ofstream file(bib_path +"/bibliography.bib", std::ios::out);

    if (file.is_open())
        file << getCode();
    else
        std::cerr << "the file could not be opened" << std::endl; 
    file.close();
}

/****************** BibData ******************/

BibData::BibData(std::string& key, std::string& kind, InfoValues& infoValues)
{
    this->key = key;
    this->kind = kind;
    this->infoValues = infoValues;
}

std::string BibData::getBibCode()
{
    std::string code;
    std::transform(kind.begin(), kind.end(), kind.begin(), ::toupper);
    code += "@" + kind + " {\n"
        "\t" + key + ",\n"; 

    for (auto iv: infoValues) {
        std::transform(iv.first.begin(), iv.first.end(), iv.first.begin(), ::toupper);
        code += "\t" + iv.first + " = \"" + iv.second + "\",\n";
    }
    code += "}\n\n";
    return code;
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