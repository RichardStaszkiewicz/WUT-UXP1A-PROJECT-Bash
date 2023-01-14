#ifndef SHELL_UXP1A_PROGRAM_HPP
#define SHELL_UXP1A_PROGRAM_HPP

#include "interface.hpp"
#include "parser.hpp"
#include "interpretation.hpp"


class Program {
private:
    ParserInterface &parser;
    InterpreterInterface &interpreter;

public:
    Program(ParserInterface &parser, InterpreterInterface &interpreter) : parser(parser), interpreter(interpreter) {};
    void execute(const std::string& parsable_string);
};

#endif //SHELL_UXP1A_PROGRAM_HPP
