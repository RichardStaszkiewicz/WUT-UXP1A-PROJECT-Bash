#include "grammar.hpp"

Assignment::Assignment(AssignmentType type, std::string name,  Assignable* expression) 
    : type(type), name(name), expression(expression) { }


Assignment::~Assignment() {
    if (expression != nullptr)
        delete expression;
    
    expression = nullptr;

};

Assignable::Assignable(AssignableType type, std::string value) : type(type), value(value) { }

Command::Command(std::string program, std::vector<Assignable*> arguments, 
        std::string* redirectFrom, std::string* redirectTo) 
        : program(program), arguments(arguments), redirectFrom(redirectFrom), redirectTo(redirectTo) { }


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

Pipe::Pipe(std::vector<Command*> commands) : commands(commands) { }

Pipe::~Pipe() {
    for (auto command : commands)
    {
        delete command;
    }
}
