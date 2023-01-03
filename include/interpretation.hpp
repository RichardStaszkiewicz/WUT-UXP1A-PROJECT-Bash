#ifndef INTERPRETATION
#define INTERPRETATION

#include <map>
#include <string>
#include "grammar.hpp"

class Assignment;
class Pipe;
class Assignable;
class Command;

class Interpreter
{
private:
    std::map<std::string, std::string>& locals;

    std::string evaluate_assignable(const Assignable &assignable);
    
    pid_t execute_command(const Command& command, int input_pipe=-1, int output_pipe=-1);
    std::vector<std::string> evaluate_arguments(const Command& command);

public:
    Interpreter(std::map<std::string, std::string>& locals);

    void execute(Assignment& assignment);
    void execute(Pipe& assignment);

    ~Interpreter();
};

#endif
