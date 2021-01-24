#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <fstream>

void execMD2TEX(const std::string& file_name)
{ 
    std::string cmd = "../md2tex ../md/" + file_name + ".md";
    CHECK (system(cmd.c_str()) == 0);
}

void compareFiles(const std::string& file_name)
{
    std::ifstream s_file, g_file;
    std::string s_out, g_out;
    std::string s_path = "../latex/" + file_name + ".tex";
    std::string g_path = "latex/tex/" + file_name + ".tex";
    std::string read_line;

    execMD2TEX(file_name);

    s_file.open(s_path);
    g_file.open(g_path);

    if (!s_file.is_open())
        std::cerr << "error: path " << file_name << " is invalid!" << std::endl;
    if (!g_file.is_open())
        std::cerr << "error: path " << file_name << " is invalid!" << std::endl;
    
    while (std::getline(s_file, read_line))
        s_out += read_line;
    
    while (std::getline(g_file, read_line))
        g_out += read_line;
    
    s_file.close();   
    g_file.close();

    REQUIRE(s_out != "");
    REQUIRE(g_out != "");       
    CHECK(s_out == g_out);
}

TEST_CASE("plain-text") 
{
    compareFiles("plain-text");
}

TEST_CASE("emphasis-text") 
{
    compareFiles("emphasis-text");
}

TEST_CASE("headers")
{
    compareFiles("headers");
}

TEST_CASE("list-of-figures")
{
    compareFiles("list-of-figures");
}

TEST_CASE("cover-default")
{
    compareFiles("cover-default");
}

TEST_CASE("cover-report")
{
    compareFiles("cover-report");
}

TEST_CASE("multiple-figures")
{
    compareFiles("multiple-figures");
}

TEST_CASE("numbered-headers")
{
    compareFiles("numbered-headers");
}

TEST_CASE("pagenumbering")
{
    compareFiles("pagenumbering");
}

TEST_CASE("simple-figures")
{
    compareFiles("simple-figures");
}

TEST_CASE("table-of-contents")
{
    compareFiles("table-of-contents");
}
