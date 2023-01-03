#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "grammar.hpp"
#include "interpretation.hpp"
#include "errors.hpp"

Interpreter::Interpreter(std::map<std::string, std::string> &locals) : locals(locals)
{
}

Interpreter::~Interpreter()
{
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
        // TODO: compute invquote
        return "";
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
        setenv(assignment.name.c_str(), value.c_str(), 1);

        // TODO: throw uncuccessfull
    }
}

pid_t Interpreter::execute_command(const Command &command)
{
    // arguments
    auto arguments = evaluate_arguments(command);
    char *args[arguments.size() + 2]{};

    args[0] = const_cast<char *>(command.program.c_str());
    args[arguments.size() + 1] = 0;

    for (size_t i = 1; i <= arguments.size(); i++)
    {
        args[i] = const_cast<char *>(arguments[i - 1].c_str());
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
            throw ParseError("TODO");
        }
    }

    if (command.redirectTo != nullptr)
    {
        redirect_to = open(command.redirectTo->c_str(), O_RDONLY);
        if (redirect_to == -1)
        {
            std::cerr << "Can't open file " << command.redirectFrom << std::endl;
            throw ParseError("TODO");
        }
    }

    // fork and exec
    auto pid = fork();

    if (pid == 0)
    {
        // pipes
        // TODO: pipes links

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

        execvp(command.program.c_str(), args);
        std::cerr << "Program " << command.program << " not found" << std::endl;
        exit(1);
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

std::vector<std::string> Interpreter::evaluate_arguments(const Command &command)
{
    std::vector<std::string> arguments{};

    for (auto assignable : command.arguments)
    {
        arguments.push_back(evaluate_assignable(*assignable));
    }

    return arguments;
}

void Interpreter::execute(Pipe &pipe)
{
    std::vector<pid_t> pids(pipe.commands.size());

    if (pipe.commands.size() == 1)
    {
        pids.push_back(execute_command(*pipe.commands[0]));
    }

    for (auto pid : pids)
    {
        int status;
        waitpid(pid, &status, 0);
        // TODO: check if status ok
    }
}