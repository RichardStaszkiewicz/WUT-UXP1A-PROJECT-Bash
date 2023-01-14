#ifndef INTERPRETATION
#define INTERPRETATION

#include <map>
#include <string>
#include "grammar.hpp"

class Assignment;
class Pipe;
class Assignable;
class Command;


class InterpreterInterface {
public:
    virtual void execute(Assignment& assignment) = 0;
    virtual void execute(Pipe& assignment) = 0;
};


class Interpreter : public InterpreterInterface
{
private:
    char** locals;

    std::string evaluate_assignable(const Assignable &assignable);
    
    pid_t execute_command(const Command& command, int input_pipe=-1, int output_pipe=-1);
    std::vector<std::string> evaluate_arguments(const Command& command);

public:
    explicit Interpreter(char** locals) : locals(locals) {};

    void execute(Assignment& assignment) override;
    void execute(Pipe& assignment) override;
};

#endif
