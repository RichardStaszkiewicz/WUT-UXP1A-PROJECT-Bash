#ifndef INTERPRETATION
#define INTERPRETATION

#include <map>
#include <string>
#include "grammar.hpp"

class Assignment;
class Pipe;
class Assignable;
class Command;


using t_int_matrix = std::vector<std::vector<int> >;
using t_pids = std::vector<pid_t>;


class InterpreterInterface {
public:
    virtual void execute(Assignment& assignment) = 0;
    virtual void execute(Pipe& assignment) = 0;
};


class Interpreter : public InterpreterInterface
{
private:
    std::map<std::string, std::string>& locals;

    std::string evaluate_assignable(const Assignable &assignable);
    
    pid_t execute_command(const Command& command, int input_pipe=-1, int output_pipe=-1);
    std::vector<std::string> evaluate_arguments(const Command& command);

    static t_int_matrix createMultiplePipes(int pipesNumber);

    static void closeMultiplePipes(t_int_matrix::iterator pipesBegin, t_int_matrix::iterator pipesEnd);

    void executeSingleCommand(const Command &command, t_pids pids);

    void executeMultipleCommands(const std::vector<Command *>& commands, t_pids pids, t_int_matrix pipe_pairs);

    void executeCommands(t_pids &pids, t_int_matrix &pipe_pairs, std::vector<Command *>& commands);

public:
    explicit Interpreter(std::map<std::string, std::string>& locals) : locals(locals) {};

    void execute(Assignment& assignment) override;
    void execute(Pipe& assignment) override;

};

#endif
