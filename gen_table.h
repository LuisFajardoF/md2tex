#ifndef _GEN_TABLE_H_
#define _GEN_TABLE_H_

#include <iostream>
#include <vector>

extern bool use_siunitx;
extern bool use_booktabs;
extern bool use_xcolor;
extern bool use_colortbl;
extern bool use_pgfplotstable;

class Table 
{
    public:
        Table(std::string& content, std::string& caption);
        ~Table() {}
        std::string getCode();

    protected:
        std::string getContent();
        std::string getAlign(std::string& row_align);
        std::vector<std::string> getFormatAlign(std::string& row_align);
        std::string getHeader(std::string& header);
        std::string getRows();
        void fillRowsVector();

        std::string getBegin() const { return begin; }
        std::string getCentering() const { return centering; }
        std::string getCaption() const { return caption; }
        std::string getEnd() const { return end; }

        std::vector<std::string> rows;

    private:
        void setBegin();
        void setCentering();
        void setCaption(std::string& caption);
        void setEnd();
        std::string begin;
        std::string centering;
        std::string content;
        std::string caption; 
        std::string end;
        std::string code;
};

class TableStyle1 : public Table 
{
    public: 
        TableStyle1(std::string& content, std::string& caption);
        ~TableStyle1() {}
        std::string getCode();
    
    protected:
        std::string getContent();
        std::string getAlign(std::string& row_align);
        std::string getRows();

    private:
        std::string code;
};

class TableStyle1Colored : public TableStyle1
{
    public:
        TableStyle1Colored(std::string& content, std::string& caption, std::string& color);
        ~TableStyle1Colored() {}
        std::string getCode();
    
    protected:
        std::string getContent();
        std::string getRows();
    
    private:
        std::string color;
        std::string code;
};

class TableStyle2 : public TableStyle1 
{
    public: 
        TableStyle2(std::string& content, std::string& caption);
        ~TableStyle2() {}
        std::string getCode();
    
    protected:
        std::string getContent();
        std::string getRows();
    
    private:
        std::string code;
};

class TableStyle2Colored : public TableStyle1Colored
{
    public:
        TableStyle2Colored(std::string& content, std::string& caption, std::string& color);
        ~TableStyle2Colored() {}
        std::string getCode();

    protected:
        std::string getContent();
        std::string getRows();

    private:
        std::string color;
        std::string code;
};

class TableCSV
{
    public:
        TableCSV(std::string& content, std::string& caption);
        ~TableCSV() {}
        std::string getCode() const { return code; }
    
    protected:
        std::string getContent();
        std::string getBegin() const { return begin; }
        std::string getCentering() const { return centering; }
        std::string getCaption() const { return caption; }
        std::string getEnd() const { return end; }
    
    private:
        void setBegin();
        void setCentering();
        void setCaption(std::string& caption);
        void setEnd();
        std::string begin;
        std::string centering;
        std::string caption; 
        std::string end;
        std::string code;
    
    protected:
        std::string content;
};

class TableCSVStyle1 : public TableCSV
{
    public:
        TableCSVStyle1(std::string& content, std::string& caption);
        ~TableCSVStyle1() {}
        std::string getCode() const { return code; }

    protected:
        std::string getContent();
    
    private:
        std::string code;
};

class TableCSVStyle1Colored : public TableCSVStyle1
{
    public:
        TableCSVStyle1Colored(std::string& content, std::string& caption, std::string& color);
        ~TableCSVStyle1Colored() {}
        std::string getCode() const { return code; }
    
    protected:
        std::string getContent();
    
    private:
        std::string color;
        std::string code;
};

class TableCSVStyle2 : public TableCSVStyle1
{
    public:
        TableCSVStyle2(std::string& content, std::string& caption);
        ~TableCSVStyle2() {}
        std::string getCode() const { return code; }

    protected:
        std::string getContent();
    
    private:
        std::string code;
};

class TableCSVStyle2Colored : public TableCSVStyle1Colored
{
    public:
        TableCSVStyle2Colored(std::string& content, std::string& caption, std::string& color);
        ~TableCSVStyle2Colored() {}
        std::string getCode() const { return code; }

    protected:
        std::string getContent();

    private:
        std::string color;
        std::string code;
};

#endif
