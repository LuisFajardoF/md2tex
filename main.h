#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "lexer.h"

std::string dev_arg = "";

std::string outFileName(char const *arg);
void createLatexFoldersDev();
void createLatexFolders();
void flagEval(std::string flag);

#endif
