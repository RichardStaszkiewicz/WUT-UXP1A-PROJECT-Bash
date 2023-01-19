#include "errors.hpp"
#include "grammar.hpp"
#include "interpretation.hpp"
#include "parser.hpp"
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 2000

int switch_std_input(int output_pipe)
{
    int old_out = dup(1);
    close(1);
    dup2(output_pipe, 1);
    close(output_pipe);

    return old_out;
}

void unswitch_std_input(int old_output)
{
    close(1);
    dup2(old_output, 1);
    close(old_output);
}

std::string Interpreter::evaluate_assignable(const Assignable &assignable)
{
    if (assignable.type == AssignableType::WORD)
    {
        return assignable.value;
    }
    else if (assignable.type == AssignableType::QUOTE)
    {
        return assignable.value;
    }
    else if (assignable.type == AssignableType::VARIABLE)
    {
        auto local_iter = locals.find(assignable.value);
        if (local_iter != locals.end())
        {
            return local_iter->second;
        }

        const char *external = getenv(assignable.value.c_str());
        if (external != nullptr)
        {
            return external;
        }

        return "";
    }
    else if (assignable.type == AssignableType::INVQUOTE)
    {
        int pipe_pair[2];
        pipe(pipe_pair);

        int old_out = switch_std_input(pipe_pair[1]);

        try
        {
            auto ast = parser->parse(assignable.value);
            ast->accept(*this);
        }
        catch (const ParseError &e)
        {
            unswitch_std_input(old_out);
            throw e;
        }

        unswitch_std_input(old_out);

        char buffer[BUFFER_SIZE];
        read(pipe_pair[0], buffer, BUFFER_SIZE);
        close(pipe_pair[0]);

        return std::string(buffer);
    }

    return "";
}

void Interpreter::execute(Assignment &assignment)
{
    std::string value = evaluate_assignable(*assignment.expression);

    if (assignment.type == AssignmentType::LOCAL)
    {
        locals[assignment.name] = value;
    }
    else if (assignment.type == AssignmentType::EXPORT)
    {
        try {
            setenv(assignment.name.c_str(), value.c_str(), 1);
        }
        catch(int num){
            if(num == EINVAL) throw AssignmentNameInterpretError(nullptr);
            if(num == ENOMEM) throw MemoryAssignmentInterpretError(nullptr);
        }
        catch(...){
            throw AssignmentInterpretError(nullptr);
        }
    }
}

pid_t Interpreter::execute_command(const Command &command, int input_pipe, int output_pipe)
{
    // arguments
    auto arguments = evaluate_arguments(command.arguments);
    std::vector<char*> args;

    args.emplace_back(const_cast<char *>(command.program.c_str()));

    for (const auto& argument : arguments)
    {
        args.emplace_back(const_cast<char *>(argument.c_str()));
    }

    // open redirections if exists
    int redirect_to = -1;
    int redirect_from = -1;

    if (command.redirectFrom != nullptr)
    {
        std::cout << *command.redirectFrom << std::endl;
        redirect_from = open(command.redirectFrom->c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (redirect_from == -1)
        {
            std::cerr << "Can't open file " << command.redirectFrom << std::endl;
            throw InterpretError(nullptr);
        }
    }

    if (command.redirectTo != nullptr)
    {
        redirect_to = open(command.redirectTo->c_str(), O_RDONLY);
        if (redirect_to == -1)
        {
            std::cerr << "Can't open file " << command.redirectFrom << std::endl;
            throw InterpretError(nullptr);
        }
    }

    // fork and exec
    auto pid = fork();

    if (pid == 0)
    {
        // pipes
        if (input_pipe > 1)
        {
            close(0);
            dup2(input_pipe, 0);
            close(input_pipe);
        }

        if (output_pipe > 1)
        {
            close(1);
            dup2(output_pipe, 1);
            close(output_pipe);
        }

        // redirecions
        if (redirect_from > 1)
        {
            close(1);
            dup2(redirect_from, 1);
            close(redirect_from);
        }

        if (redirect_to > 1)
        {
            close(0);
            dup2(redirect_to, 0);
            close(redirect_to);
        }

        execvp(command.program.c_str(), args.data());
        if (command.program != "exit" && !command.program.empty())
            std::cerr << "Program " << command.program << " not found" << std::endl;
        exit(1);
    }

    // close pipes
    if (input_pipe > 1)
    {
        close(input_pipe);
    }

    if (output_pipe > 1)
    {
        close(output_pipe);
    }

    // close redirections
    if (redirect_from > 1)
    {
        close(redirect_from);
    }

    if (redirect_to > 1)
    {
        close(redirect_from);
    }

    return pid;
}

std::vector<std::string> Interpreter::evaluate_arguments(const std::vector<Assignable*> &assignables)
{
    std::vector<std::string> arguments{};

    for (auto assignable : assignables)
    {
        arguments.push_back(evaluate_assignable(*assignable));
    }

    return arguments;
}

void Interpreter::execute(Pipe &pipe_obj)
{
    t_pids pids;
    t_int_matrix pipe_pairs = createMultiplePipes(pipe_obj.commands.size() - 1);

    executeCommands(pids, pipe_pairs, pipe_obj.commands);
    waitForChildrenExecution(pids);
}

t_int_matrix Interpreter::createMultiplePipes(int pipesNumber) {
    std::vector<int> initialSinglePipeState(2, -1);
    t_int_matrix pipes(pipesNumber, initialSinglePipeState);

    for (auto it=pipes.begin(); it < pipes.end(); it++) {
        if (pipe(it->data()) == -1) {
            perror("Error creating pipes");
            closeMultiplePipes(pipes.begin(), it);
            exit(EXIT_FAILURE);
        }
    }

    return pipes;
};

void Interpreter::closeMultiplePipes(t_int_matrix ::iterator pipesBegin, t_int_matrix ::iterator pipesEnd) {
    for (auto it = pipesBegin; it < pipesEnd; it++) {
        close(it->at(0));
        close(it->at(1));
    }
}

void Interpreter::executeCommands(t_pids &pids, t_int_matrix &pipe_pairs, std::vector<Command *>& commands) {
    if (commands.size() == 1) {
        executeSingleCommand(*commands[0], pids);
    } else {
        executeMultipleCommands(commands, pids, pipe_pairs);
    }
}

void Interpreter::executeSingleCommand(const Command &command, t_pids &pids) {
    pids.push_back(execute_command(command));
}

void Interpreter::executeMultipleCommands(const std::vector<Command *>& commands, t_pids &pids, t_int_matrix pipe_pairs) {
    int commands_count = commands.size();

    pids.push_back(execute_command(*commands[0], -1, pipe_pairs[0][1]));
    for (int i = 1; i < commands_count - 1; i++)
    {
        pids.push_back(execute_command(*commands[i], pipe_pairs[i - 1][0], pipe_pairs[i][1]));
    }
    pids.push_back(execute_command(*commands[commands_count - 1], pipe_pairs[commands_count - 2][0], -1));
}

void Interpreter::waitForChildrenExecution(const t_pids &pids) {
    for (auto pid : pids) {
        if (waitpid(pid, nullptr, 0) == -1){
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

void Interpreter::execute(SelfProcessCommand& buildInCommand) {
    auto arguments = evaluate_arguments(buildInCommand.arguments);

    if (buildInCommand.type == SelfProcessCommandType::CD)
    {
        executeCdCommand(arguments);
        return;
    }

    std::cerr << "Unknown type of build in command" << std::endl;
    throw InterpretError(nullptr);
}

void Interpreter::executeCdCommand(const std::vector<std::string>& arguments) {
    if (arguments.size() != 1)
    {
        std::cerr << "Invalid number of arguments: expected 1, actual: " << arguments.size() << std::endl;
        throw InterpretError(nullptr);
    }

    int result = chdir(arguments[0].c_str());
    
    if (result != 0)
    {
        switch (errno)
        {
        case ENOENT:
            std::cerr << "Directory does not exists: " << arguments[0] << std::endl;
            throw new InterpretError(nullptr);

        case ENOTDIR:
            std::cerr << "Path does not p[oint a directory: " << arguments[0] << std::endl;
            throw new InterpretError(nullptr);

        case EACCES:
            std::cerr << "Search permission is denied: " << arguments[0] << std::endl;
            throw new InterpretError(nullptr);
        
        case ENAMETOOLONG:
            std::cerr << "Path is too long: " << arguments[0] << std::endl;
            throw new InterpretError(nullptr);

        default:
            std::cerr << "Access error: " << arguments[0] << std::endl;
            throw new InterpretError(nullptr);
        }
    }
}
