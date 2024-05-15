#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ErrorFile.h"
#include "InterpreterFile.h"
#include "Parser.h"
#include "ConflictResolver.h"
#include "Scanner.h"

std::string readFile(std::string_view path);
void run(std::string_view source);
void runFile(std::string_view path);
void runPrompt();