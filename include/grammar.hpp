#ifndef GRAMMAR
#define GRAMMAR
#include <string>
#include <vector>
#include <memory>
#include "interpretation.hpp"

class Interpreter;

enum class AssignmentType { LOCAL, EXPORT };
enum class AssignableType { WORD, VARIABLE, QUOTE, INVQUOTE };

class GrammarRule
{
public:
    virtual void accept(Interpreter& Interpreter) = 0;
    virtual ~GrammarRule() = default;
};

class Assignable
{
public:
    AssignableType type;
    std::string value;

    Assignable(AssignableType type, std::string value);
};

class Assignment : public GrammarRule
{

public:
    AssignmentType type;
    std::string name;
    Assignable* expression;

    Assignment(AssignmentType type, std::string name,  Assignable* expression);

    void accept(Interpreter& interpreter) override {
        interpreter.execute(*this);
    }

    ~Assignment() override;
}; 

class Command
{
public:
    std::string program;
    std::vector<Assignable*> arguments;
    std::string* redirectFrom;
    std::string* redirectTo;

    // Command(std::string program, std::vector<Assignable*> arguments, 
    //     std::string* redirectFrom = nullptr, std::string* redirectTo = nullptr);

    Command(std::string program, std::vector<std::unique_ptr<Assignable>>& arguments, 
        std::string* redirectFrom = nullptr, std::string* redirectTo = nullptr);

    ~Command();
};

class Pipe : public GrammarRule
{
public:
    std::vector<Command*> commands;
    // Pipe(std::vector<Command*> commands);
    Pipe(std::vector<std::unique_ptr<Command>>& commands);

    void accept(Interpreter& interpreter) override {
        interpreter.execute(*this);
    }

    ~Pipe() override;
};

#endif

