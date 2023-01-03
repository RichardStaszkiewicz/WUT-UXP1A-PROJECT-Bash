#ifndef PARSER
#define PARSER

#include <string>
#include <memory>
#include "grammar.hpp"

class Parser
{

private: 
    int current;
    void advance();

    std::unique_ptr<Assignment> parseAssignment();
    std::unique_ptr<Assignable> parseAssignable();
    std::unique_ptr<Pipe> parsePipe();
    std::unique_ptr<Command> parseCommand();

public:
    std::unique_ptr<GrammarRule> parse();

    Parser(std::string request);
    ~Parser();
};

#endif