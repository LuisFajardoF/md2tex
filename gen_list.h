#ifndef _GEN_LIST_H_
#define _GEN_LIST_H_

#include <iostream>
#include <vector>
#include <string.h>

extern bool use_enumitem;
extern bool use_amssymb;
extern bool use_pifont;

class List
{
    public:
        List(std::string*& params, std::string& content);
        virtual std::string getCode() = 0;

    protected:
        std::string getBegin() { return begin; }
        std::string getEnd() { return end; }
        virtual std::string getContent() = 0;
        virtual std::string generateItems() = 0;
        virtual std::string getParamCode(std::string& param) = 0; 
        std::string getParams();
        void fillItemsVector();
        std::string trim(std::string str);
        
        std::string* params;
        std::string content;
        std::vector<std::string> items;
        std::string begin;
        std::string end;
};

class UnorderedList : public List
{
    public:
        UnorderedList(std::string*& params, std::string& content);
        std::string getCode() override;

    private:
        void setBegin(std::string params);
        void setEnd();
        std::string getContent() override;
        std::string generateItems() override;
        std::string getParamCode(std::string& param) override;
};

class OrderedList : public List
{
    public:
        OrderedList(std::string*& params, std::string& content);
        std::string getCode() override;

    private:
        void setBegin(std::string params);
        void setEnd();
        std::string getContent() override;
        std::string generateItems() override;
        std::string getParamCode(std::string& param) override;
};

class DescriptionList : public List
{
    public:
        DescriptionList(std::string*& params, std::string& content);
        std::string getCode() override;

    private:
        void setBegin(std::string params);
        void setEnd();
        std::string getContent() override;
        std::string generateItems() override;
        std::string getParamCode(std::string& param) override;
};

class ToDoList : public List
{
    public: 
        ToDoList(std::string*&params, std::string& content);
        std::string getCode() override;

    private:
        void setBegin();
        void setEnd();
        std::string getContent() override;
        std::string generateItems() override;
        std::string getParamCode(std::string& param) override { return ""; }
};

class NestedList : public List
{
    public:
        NestedList(std::string*& params, std::string& content);
        std::string getCode() override;

    private:
        std::string getContent() override;
        std::string generateItems() override;
        std::string getParamCode(std::string& param) override { return ""; }
        std::string getBegin(std::string env);
        std::string getEnd(std::string env);
        std::string getItem(std::string& item, int tab_arr_off);
        std::string getBeginEnvAndItems(int env_off, std::string& item, const std::string env);

        std::vector<int> tags;
        bool active_envs[6] = {false, false, false, false, false, false};
        std::string tabs[7] = {"\t", "\t\t", "\t\t\t", "\t\t\t\t", "\t\t\t\t\t", 
                                "\t\t\t\t\t\t", "\t\t\t\t\t\t\t"};
};

#endif