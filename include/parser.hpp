#ifndef PARSER
#define PARSER

#include <string>
#include <memory>
#include "grammar.hpp"

class ParserInterface {
public:
    virtual std::unique_ptr<GrammarRule> parse(const std::string& request) = 0;
};

class Parser : public ParserInterface
{

private: 
    int current;
    void advance();

    std::unique_ptr<Assignment> parseAssignment();
    std::unique_ptr<Assignable> parseAssignable();
    std::unique_ptr<Pipe> parsePipe();
    std::unique_ptr<Command> parseCommand();

public:
    std::unique_ptr<GrammarRule> parse(const std::string& request) override;
};

#endif