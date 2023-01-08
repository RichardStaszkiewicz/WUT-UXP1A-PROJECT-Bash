#ifndef SHELL_UXP1A_PROGRAM_HPP
#define SHELL_UXP1A_PROGRAM_HPP

#include "interface.hpp"
#include "parser.hpp"
#include "interpretation.hpp"


class Program {
private:
    Interface &terminal;
    Parser &parser;
    Interpreter &interpreter;

    void execute(std::string parsable_string);

public:
    Program(Interface &terminal, Parser &parser, Interpreter &interpreter) : terminal(terminal), parser(parser),
                                                                             interpreter(interpreter) {};
    void run_interactive();
    void run_batch(int argc, char** argv);
};

#endif //SHELL_UXP1A_PROGRAM_HPP
