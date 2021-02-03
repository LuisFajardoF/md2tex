#include "gen_list.h"

/****************** List ******************/
void List::fillItemsVector()
{
    std::string line;

    for (auto it = 0; content[it]; it++) {
        if (content[it] == '\n') {
            if (line[0] != '\0')
                items.push_back(line);
            line.clear();
        }
        else
            line.push_back(content[it]);
    }
}

/****************** Ordered List ******************/
OrderedList::OrderedList(std::string& params, std::string& content) : List(params, content)
{
    this->params = params;
    this->content = content;

    setBegin();
    setEnd();
}

std::string OrderedList::getCode()
{
    return getBegin()
        + getContent()
        + getEnd();
}

void OrderedList::setBegin() { begin = "\t\\begin{enumerate}\n"; }
void OrderedList::setEnd() { end = "\t\\end{enumerate}\n"; }

std::string OrderedList::getContent()
{
    fillItemsVector();
    return generateItems();
}

std::string OrderedList::generateItems()
{
    std::string code;
    char* token;
    int number;

    for (auto item : items) {
        token = strtok(const_cast<char*>(item.c_str()), ".-");
        number = atoi(token);
        if (number > 0 && number < INT32_MAX) {
            token = strtok(NULL, "\n");
            item = std::string(token);
            code += "\t\t\\item" + item + "\n"; 
        }
        else 
            code += "\t\t" + item + "\n";
    }
    return code;
}

/****************** Unordered List ******************/
UnorderedList::UnorderedList(std::string& params, std::string& content) : List(params, content)
{
    this->params = params;
    this->content = content;

    setBegin(); 
    setEnd(); 
}

std::string UnorderedList::getCode()
{
    return getBegin()
        + getContent() 
        + getEnd();
}

void UnorderedList::setBegin() { begin = "\t\\begin{itemize}\n"; }
void UnorderedList::setEnd() { end = "\t\\end{itemize}\n"; }

std::string UnorderedList::getContent()
{
    fillItemsVector();
    return generateItems();
}

std::string UnorderedList::generateItems()
{
    std::string out;

    for (auto item : items) {
        if (item[0] == '-' && item[1] == ' ' ||
        item[0] == '+' && item[1] == ' ' ||
        item[0] == '*' && item[1] == ' ' ) {
            item.erase(0, 1);
            out += "\t\t\\item" + item + "\n";
        } else {
            out += "\t\t" + item + "\n";
        }
    }    
    return out;
}

/****************** Nested List ******************/
NestedList::NestedList(std::string& params, std::string& content) : List(params, content) 
{
    this->params = params;
    this->content = content;
}

std::string NestedList::getCode()
{
    return getContent();
}

std::string NestedList::getContent()
{
    fillItemsVector();
    auto spaces(0);
    
    for (auto item : items) {
        for (auto i = 0, spaces = 0; i < item.length(); i++) {
            if (item[i] == ' ')
                spaces++;
            else {
                tags.push_back(spaces);
                break;
            }
        }
    }

    return generateItems();
}

std::string NestedList::generateItems()
{
    std::string code;
    auto it = 0, offset = 0;

    for (auto tag : tags) {
        offset = it+1;
        if (tag == 0) {
            code += getBeginEnvAndItems(0, items[it], "enumerate");

            if (it == (items.size()-1))
                code += tabs[0] + getEnd("enumerate");
        }
        else if (tag == 4) {
            code += getBeginEnvAndItems(1, items[it], "enumerate");
            
            if (it == (items.size()-1)) {
                for (auto i = 1; i >= 0; i--) {
                    code += tabs[i] + getEnd("enumerate");
                    active_envs[i] = false;
                }
            }
            else if (tags[offset] < 4) {
                if (tags[offset] == 0) {
                    code += tabs[1] + getEnd("enumerate");
                    active_envs[1] = false;
                }
            }
        }
        else if (tag == 8) {
            code += getBeginEnvAndItems(2, items[it], "enumerate");
            
            if (it == (items.size()-1)) {
                for (auto i = 2; i >= 0; i--) {
                    code += tabs[i] + getEnd("enumerate");
                    active_envs[i] = false;
                }
            }
            else if (tags[offset] < 8) {
                if (tags[offset] == 4 || tags[offset] < 4) {
                    code += tabs[2] + getEnd("enumerate");
                    active_envs[2] = false;
                } 
                if (tags[offset] == 0) {
                    code += tabs[1] + getEnd("enumerate");
                    active_envs[1] = false;
                }
            }
        }
        else if (tag == 12) {
            code += getBeginEnvAndItems(3, items[it], "enumerate");

            if (it == (items.size()-1)) {
                for (auto i = 3; i >= 0; i--) {
                    code += tabs[i] + getEnd("enumerate");
                    active_envs[i] = false;
                }
            }
            else if (tags[offset] < 12) {
                if (tags[offset] == 8 || tags[offset] < 8) {
                    code += tabs[3] + getEnd("enumerate");
                    active_envs[3] = false;
                }
                if (tags[offset] == 4 || tags[offset] < 4) {
                    code += tabs[2] + getEnd("enumerate");
                    active_envs[2] = false;
                } 
                if (tags[offset] == 0) {
                    code += tabs[1] + getEnd("enumerate");
                    active_envs[1] = false;
                }
            }
        }
        else if (tag == 16) {
            code += getBeginEnvAndItems(4, items[it], "itemize");

            if (it == (items.size()-1)) {
                for (auto i = 4; i >= 0; i--) {
                    code += tabs[i] + ((i > 3)? getEnd("itemize") : getEnd("enumerate"));
                    active_envs[i] = false;
                }
            }
            else if (tags[offset] < 16) {
                if (tags[offset] == 12 || tags[offset] < 12) {
                    code += tabs[4] + getEnd("itemize");
                    active_envs[4] = false;
                }
                if (tags[offset] == 8 || tags[offset] < 8) {
                    code += tabs[3] + getEnd("enumerate");
                    active_envs[3] = false;
                }
                if (tags[offset] == 4 || tags[offset] < 4) {
                    code += tabs[2] + getEnd("enumerate");
                    active_envs[2] = false;
                } 
                if (tags[offset] == 0) {
                    code += tabs[1] + getEnd("enumerate");
                    active_envs[1] = false;
                } 
            }
        }
        else if (tag == 20) {
            code += getBeginEnvAndItems(5, items[it], "itemize");

            if (it == (items.size()-1)) {
                for (auto i = 5; i >= 0; i--) {
                    code += tabs[i] + ((i > 3)? getEnd("itemize") : getEnd("enumerate"));
                    active_envs[i] = false;
                }
            }
            else if (tags[offset] < 20) {
                if (tags[offset] == 16 || tags[offset] < 16) {
                    code += tabs[5] + getEnd("itemize");
                    active_envs[5] = false;
                }
                if (tags[offset] == 12 || tags[offset] < 12) {
                    code += tabs[4] + getEnd("itemize");
                    active_envs[4] = false;
                }
                if (tags[offset] == 8 || tags[offset] < 8) {
                    code += tabs[3] + getEnd("enumerate");
                    active_envs[3] = false;
                }
                if (tags[offset] == 4 || tags[offset] < 4) {
                    code += tabs[2] + getEnd("enumerate");
                    active_envs[2] = false;
                } 
                if (tags[offset] == 0) {
                    code += tabs[1] + getEnd("enumerate");
                    active_envs[1] = false;
                } 
            }
        }
        it++;
    }

    return code;
}

std::string NestedList::getBeginEnvAndItems(int env_off, std::string& item, const std::string env)
{
    std::string code;
    if (!active_envs[env_off]) {
        code += tabs[env_off] + getBegin(env);
        active_envs[env_off] = true;
        code += getItem(item, env_off+1);
    } 
    else code += getItem(item, env_off+1);

    return code;
}

std::string NestedList::getItem(std::string& item, int tabs_off)
{
    char* token;

    token = strtok(const_cast<char*>(item.c_str()), ".-");
    token = strtok(NULL, "\n");
    return tabs[tabs_off] + "\\item" + std::string(token) + "\n";
}

std::string NestedList::getBegin(std::string env)
{
    return "\\begin{" + env + "}\n";
}

std::string NestedList::getEnd(std::string env)
{
    return "\\end{" + env + "}\n";
}