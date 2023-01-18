#ifndef INTERPRETATION
#define INTERPRETATION

#include "grammar.hpp"
#include "parser.hpp"
#include <map>
#include <string>


class Assignment;
class Pipe;
class Assignable;
class Command;
class SelfProcessCommand;
class ParserInterface;


using t_int_matrix = std::vector<std::vector<int> >;
using t_pids = std::vector<pid_t>;


class InterpreterInterface {
public:
    virtual void execute(Assignment& assignment) = 0;
    virtual void execute(Pipe& assignment) = 0;
    virtual void execute(SelfProcessCommand& buildInCommand) = 0;
};


class Interpreter : public InterpreterInterface
{
private:
    ParserInterface* parser;

    std::map<std::string, std::string>& locals;

    std::string evaluate_assignable(const Assignable &assignable);

    std::vector<std::string> evaluate_arguments(const std::vector<Assignable*>& assignables);
    
    pid_t execute_command(const Command& command, int input_pipe=-1, int output_pipe=-1);

    static t_int_matrix createMultiplePipes(int pipesNumber);

    static void closeMultiplePipes(t_int_matrix::iterator pipesBegin, t_int_matrix::iterator pipesEnd);

    void executeSingleCommand(const Command &command, t_pids &pids);

    void executeMultipleCommands(const std::vector<Command *>& commands, t_pids &pids, t_int_matrix pipe_pairs);

    void executeCommands(t_pids &pids, t_int_matrix &pipe_pairs, std::vector<Command *>& commands);

    void executeCdCommand(const std::vector<std::string>& arguments);

public:
    explicit Interpreter(ParserInterface* parser, std::map<std::string, std::string>& locals) : parser(parser), locals(locals) {};

    void execute(Assignment& assignment) override;
    void execute(Pipe& assignment) override;
    void execute(SelfProcessCommand& buildInCommand) override;

    static void waitForChildrenExecution(const t_pids &pids) ;
};

#endif
