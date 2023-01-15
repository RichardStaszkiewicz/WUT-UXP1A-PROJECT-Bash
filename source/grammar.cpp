#include "grammar.hpp"
#include "interpretation.hpp"
#include <memory>

Assignment::Assignment(AssignmentType type, std::string name,  Assignable* expression) 
    : type(type), name(name), expression(expression) { }


Assignment::~Assignment() {
    if (expression != nullptr)
        delete expression;
    
    expression = nullptr;

};

Assignable::Assignable(AssignableType type, std::string value) : type(type), value(value) { }

// Command::Command(std::string program, std::vector<Assignable*> arguments, 
//         std::string* redirectFrom, std::string* redirectTo) 
//         : program(program), arguments(arguments), redirectFrom(redirectFrom), redirectTo(redirectTo) { }

Command::Command(std::string program, std::vector<std::unique_ptr<Assignable>>& arguments, 
        std::string* redirectFrom, std::string* redirectTo)
        : program(program), redirectFrom(redirectFrom), redirectTo(redirectTo)
    {
        for (auto& uargument : arguments)
        {
            this->arguments.push_back(uargument.release());
        }
    }

Command::~Command() {
    for(auto assignable : arguments)
    {
        delete assignable;
    }

    if (redirectFrom)
    {
        /* code */
    }
    
}

std::unique_ptr<Command> Command::getEmptyCommand() {
    std::vector<std::unique_ptr<Assignable>> emptyVect;
    return std::make_unique<Command>("", emptyVect);
}

// Pipe::Pipe(std::vector<Command*> commands) : commands(commands) { }

Pipe::Pipe(std::vector<std::unique_ptr<Command>>& commands) : commands(*(new std::vector<Command*>))
{
    for (auto& ucommand : commands)
    {
        this->commands.push_back(ucommand.release());
    }
}

Pipe::~Pipe() {
    for (auto command : commands)
    {
        delete command;
    }
}