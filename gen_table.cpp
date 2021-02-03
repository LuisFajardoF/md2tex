#include "gen_table.h"

bool use_booktabs = false;
bool use_xcolor = false;
bool use_colortbl = false;
bool use_siunitx = false;
bool use_pgfplotstable = false;

/********************* Class: Table **********************/

Table::Table(std::string& content, std::string& caption)
{
    this->content = content;

    setBegin();
    setCentering();
    setCaption(caption);
    setEnd();
}

std::string Table::getCode()
{
    return getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

void Table::setBegin() { begin = "\n\t\\begin{table}[h!]\n"; }
void Table::setCentering() { centering = "\t\t\\centering\n"; }
void Table::setEnd() { end = "\t\\end{table}\n"; }

void Table::setCaption(std::string& caption)
{
    this->caption = "\t\t\\caption{" + caption + "}\n";
}

std::string Table::getContent()
{
    std::string outContent = "";

    fillRowsVector();

    outContent += "\t\t\\begin{tabular}{" + getAlign(rows[1]) + "} \\hline\n"
                "\t\t\t" + getHeader(rows[0]) + " \\\\ \\hline\n";
    rows.erase(rows.begin());
    rows.erase(rows.begin());

    outContent += getRows();
    outContent += "\t\t\\end{tabular}\n";

    return outContent;
}

std::string Table::getAlign(std::string& row_align)
{
    std::string outAlign = "|";
    std::vector<std::string> alignVector;

    alignVector = getFormatAlign(row_align);

    for ( auto col : alignVector ) {
        if (col[0] == ':' && col[col.length()-1] == ':')
            outAlign += "c|";
        else if (col[0] == ':')
            outAlign += "l|";
        else if (col[col.length()-1] == ':')
            outAlign += "r|";
        else if (col[0] == '<' && col[col.length()-1] == '>') {
            use_siunitx = true;
            outAlign += "S|";
        } else 
            outAlign += "l|";
    }

    return outAlign;
}

std::string Table::getHeader(std::string& header)
{
    std::string formatHeader = "";
    std::string outHeader = "";

    for (int i = 0; i < header.length(); i++) 
    {
        if (header[i] != '|')
            formatHeader.push_back(header[i]);
        else {
            outHeader += "\\textbf{" + formatHeader + "} & ";
            formatHeader.erase();
        } 
    }

    outHeader += "\\textbf{" + formatHeader + "}";
    return outHeader;
}

std::vector<std::string> Table::getFormatAlign(std::string& row_align)
{
    std::string format_align = "";
    std::vector<std::string> alignVector;

    for (int i = 0; i < row_align.length(); i++)
    {
        if (row_align[i] != '|')
            format_align.push_back(row_align[i]);
        else {
            alignVector.push_back(format_align);
            format_align.erase();
        }
    }
    alignVector.push_back(format_align);   

    return alignVector;
}

std::string Table::getRows()
{
    std::string outRows = "";

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            if (rows[i][j] == '|')
                rows[i][j] = '&';
        }
        outRows += "\t\t\t" + rows[i] + " \\\\ \\hline\n";
    }

    return outRows;
}

void Table::fillRowsVector()
{
    std::string delimiter = "\n";
    size_t position = 0;

    while ((position = content.find(delimiter)) != std::string::npos) 
    {
        rows.push_back(content.substr(0, position));
        content.erase(0, position + delimiter.length());
    }

    rows.erase(rows.begin());
}

/********************* Class: TableStyle1 *******************/

TableStyle1::TableStyle1(std::string& content, std::string& caption) : Table(content, caption)
{ 
    use_booktabs = true; 
}

std::string TableStyle1::getCode()
{
    return getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

std::string TableStyle1::getContent()
{
    std::string outContent = "";

    fillRowsVector();

    outContent += "\t\t\\begin{tabular}{" + getAlign(rows[1]) + "} \n"
                "\t\t\t\\toprule\n"
                "\t\t\t" + getHeader(rows[0]) + " \\\\ \\midrule\n";
    rows.erase(rows.begin());
    rows.erase(rows.begin());

    outContent += getRows();
    outContent += "\t\t\t\\bottomrule\n";
    outContent += "\t\t\\end{tabular}\n";

    return outContent;
}

std::string TableStyle1::getAlign(std::string& row_align)
{
    std::string outAlign = "";
    std::vector<std::string> alignVector;

    alignVector = getFormatAlign(row_align);

    for ( auto col : alignVector ) {
        if (col[0] == ':' && col[col.length()-1] == ':')
            outAlign += "c";
        else if (col[0] == ':')
            outAlign += "l";
        else if (col[col.length()-1] == ':')
            outAlign += "r";
        else if (col[0] == '<' && col[col.length()-1] == '>') {
            use_siunitx = true;
            outAlign += "S";
        } else 
            outAlign += "l";
    }

    return outAlign;
}

std::string TableStyle1::getRows()
{
    std::string outRows = "";

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            if (rows[i][j] == '|')
                rows[i][j] = '&';
        }
        outRows += "\t\t\t" + rows[i] + " \\\\ \n";
    }

    return outRows;
}

/********************* Class: TableStyle1Colored *******************/

TableStyle1Colored::TableStyle1Colored(std::string& content, std::string& caption, std::string& color)
: TableStyle1(content, caption)
{
    use_xcolor = true;
    use_colortbl = true;
    this->color = color;
}

std::string TableStyle1Colored::getCode()
{
    return getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

std::string TableStyle1Colored::getContent()
{
    std::string outContent = "";

    fillRowsVector();

    outContent += "\t\t\\begin{tabular}{" + getAlign(rows[1]) + "} \n"
                "\t\t\t\\toprule\n"
                "\t\t\t" + getHeader(rows[0]) + " \\\\ \\midrule \\rowcolor{" + color + "!10}\n";
    rows.erase(rows.begin());
    rows.erase(rows.begin());

    outContent += getRows();
    outContent += "\t\t\t\\bottomrule\n";
    outContent += "\t\t\\end{tabular}\n";

    return outContent;
}

std::string TableStyle1Colored::getRows()
{
    std::string outRows = "";
    int back_opacity;

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            if (rows[i][j] == '|')
                rows[i][j] = '&';
        }
        back_opacity = (i % 2 == 0)? 30 : 10;

        if (i == (rows.size()-1))
            outRows += "\t\t\t" + rows[i] + " \\\\ \n";
        else
            outRows += "\t\t\t" + rows[i] + " \\\\ \\rowcolor{" + color + "!"+ std::to_string(back_opacity) +"}\n";
    }

    return outRows;
}

/********************* Class: TableStyle2 *******************/

TableStyle2::TableStyle2(std::string& content, std::string& caption) : TableStyle1(content, caption) 
{}

std::string TableStyle2::getCode()
{
    return getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

std::string TableStyle2::getContent()
{
    std::string outContent = "";

    fillRowsVector();

    outContent += "\t\t\\begin{tabular}{" + getAlign(rows[1]) + "} \n"
                "\t\t\t\\toprule\n"
                "\t\t\t" + getHeader(rows[0]) + " \\\\ \\midrule\n";
    rows.erase(rows.begin());
    rows.erase(rows.begin());

    outContent += getRows();
    outContent += "\t\t\t\\bottomrule\n";
    outContent += "\t\t\\end{tabular}\n";

    return outContent;
}


std::string TableStyle2::getRows()
{
    std::string outRows = "";

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            if (rows[i][j] == '|')
                rows[i][j] = '&';
        }
        if ( i == (rows.size() - 2) )
            outRows += "\t\t\t" + rows[i] + " \\\\ \\midrule\n";
        else
            outRows += "\t\t\t" + rows[i] + " \\\\ \n";
    }

    return outRows;
}

/********************* Class: TableStyle2Colored *******************/

TableStyle2Colored::TableStyle2Colored(std::string& content, std::string& caption, std::string& color) 
: TableStyle1Colored(content, caption, color) 
{ 
    this->color = color; 
}

std::string TableStyle2Colored::getCode()
{
    return getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

std::string TableStyle2Colored::getContent()
{
    std::string outContent = "";

    fillRowsVector();

    outContent += "\t\t\\begin{tabular}{" + getAlign(rows[1]) + "} \n"
                "\t\t\t\\toprule \\rowcolor{" + color + "!30}\n"
                "\t\t\t" + getHeader(rows[0]) + " \\\\ \\midrule \n";
    rows.erase(rows.begin());
    rows.erase(rows.begin());

    outContent += getRows();
    outContent += "\t\t\t\\bottomrule\n";
    outContent += "\t\t\\end{tabular}\n";

    return outContent;
}

std::string TableStyle2Colored::getRows()
{
    std::string outRows = "";

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            if (rows[i][j] == '|')
                rows[i][j] = '&';
        }

        if ( i == (rows.size() - 2) )
            outRows += "\t\t\t" + rows[i] + " \\\\ \\midrule \\rowcolor{" + color + "!10}\n";
        else
            outRows += "\t\t\t" + rows[i] + " \\\\ \n";
    }

    return outRows;
}

/********************* Class: TableCSV *******************/

TableCSV::TableCSV(std::string& content, std::string& caption) 
{
    use_pgfplotstable = true;
    this->content = content;

    setBegin();
    setCentering();
    setCaption(caption);
    setEnd();

    code = getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

void TableCSV::setBegin() { begin = "\n\t\\begin{table}[h!]\n"; }
void TableCSV::setCentering() { centering = "\t\t\\centering\n"; }
void TableCSV::setEnd() { end = "\t\\end{table}\n"; }

void TableCSV::setCaption(std::string& caption)
{
    this->caption = "\t\t\\caption{" + caption + "}\n";
}

std::string TableCSV::getContent()
{
    return "\t\t\\pgfplotstabletypeset[\n"
        "\t\t\tcol sep=comma,\n"
        "\t\t\tstring type,\n"
        "\t\t\tassign column name/.style={/pgfplots/table/column name={\\textbf{#1}}},\n"
        "\t\t\tevery head row/.style={before row=\\hline},\n"
        "\t\t\tevery last row/.style={after row=\\hline},\n"
        "\t\t\tevery even row/.style={before row=\\hline, after row=\\hline},\n"
        "\t\t\tevery last column/.style={column type/.add={}{|}},\n"
        "\t\t\tevery even column/.style={column type/.add={|}{|}}\n"
        "\t\t]{" + content + "}\n";
}

/********************* Class: TableCSVStyle1 *******************/

TableCSVStyle1::TableCSVStyle1(std::string& content, std::string& caption) : TableCSV(content, caption)
{ 
    use_booktabs = true; 
    code = getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

std::string TableCSVStyle1::getContent()
{
    return "\t\t\\pgfplotstabletypeset[\n"
        "\t\t\tcol sep=comma,\n"
        "\t\t\tstring type,\n"
        "\t\t\tassign column name/.style={/pgfplots/table/column name={\\textbf{#1}}},\n"
        "\t\t\tevery head row/.style={before row=\\toprule, after row=\\midrule},\n"
        "\t\t\tevery last row/.style={after row=\\midrule},\n"
        "\t\t]{" + content + "}\n";
}

/********************* Class: TableCSVStyle1Colored *******************/

TableCSVStyle1Colored::TableCSVStyle1Colored(std::string& content, std::string& caption, std::string& color) 
: TableCSVStyle1(content, caption)
{
    use_xcolor = true;
    use_colortbl = true;
    this->color = color;

    code = getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

std::string TableCSVStyle1Colored::getContent()
{
    return "\t\t\\pgfplotstabletypeset[\n"
        "\t\t\tcol sep=comma,\n"
        "\t\t\tstring type,\n"
        "\t\t\tevery head row/.style={before row=\\toprule, after row=\\midrule},\n"
        "\t\t\tassign column name/.style={/pgfplots/table/column name={\\textbf{#1}}},\n"
        "\t\t\tevery even row/.style={after row ={\\rowcolor{" + color +"!30}}, before row={\\rowcolor{" + color + "!10}}},\n"
        "\t\t\tevery last row/.style={after row=\\midrule},\n"
        "\t\t]{" + content + "}\n";
}

/********************* Class: TableCSVStyle2 *******************/

TableCSVStyle2::TableCSVStyle2(std::string& content, std::string& caption) : TableCSVStyle1(content, caption) 
{ 
    code = getBegin() + getCentering() + getContent() + getCaption() + getEnd(); 
}

std::string TableCSVStyle2::getContent()
{
    return "\t\t\\pgfplotstabletypeset[\n"
        "\t\t\tcol sep=comma,\n"
        "\t\t\tstring type,\n"
        "\t\t\tevery head row/.style={before row=\\toprule, after row=\\midrule},\n"
        "\t\t\tassign column name/.style={/pgfplots/table/column name={\\textbf{#1}}},\n"
        "\t\t\tevery last row/.style={before row=\\midrule, after row=\\bottomrule},\n"
        "\t\t]{" + content + "}\n";
}

/********************* Class: TableCSVStyle2Colored *******************/

TableCSVStyle2Colored::TableCSVStyle2Colored(std::string& content, std::string& caption, std::string& color)
: TableCSVStyle1Colored(content, caption, color) 
{ 
    this->color = color; 
    code = getBegin() + getCentering() + getContent() + getCaption() + getEnd();
}

std::string TableCSVStyle2Colored::getContent()
{
    return "\t\t\\pgfplotstabletypeset[\n"
        "\t\t\tcol sep=comma,\n"
        "\t\t\tstring type,\n"
        "\t\t\tevery head row/.style={before row=\\rowcolor{" + color + "!30} \\toprule, after row=\\midrule},\n"
        "\t\t\tassign column name/.style={/pgfplots/table/column name={\\textbf{#1}}},\n"
        "\t\t\tevery last row/.style={before row=\\rowcolor{" + color + "!10} \\midrule, after row=\\bottomrule},\n"
        "\t\t]{" + content + "}\n";
}
