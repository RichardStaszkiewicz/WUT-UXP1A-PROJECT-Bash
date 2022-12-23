#ifndef PARSER
#define PARSER

#include <string>
#include "grammar.hpp"

class Parser
{

private: 
    int current;
    void advance();

    Assignment* parseAssignment();
    Assignable* parseAssignable();
    Pipe* parsePipe();
    Command* parseCommand();

public:
    GrammarRule* parse();

    Parser(std::string request);
    ~Parser();
};

#endif