#ifndef GRAMMAR
#define GRAMMAR
#include <string>
#include <vector>
#include <memory>
#include "interpretation.hpp"

class Interpreter;

enum class SelfProcessCommandType { CD };
enum class AssignmentType { LOCAL, EXPORT };
enum class AssignableType { WORD, VARIABLE, QUOTE, INVQUOTE };

class GrammarRule
{
public:
    virtual void accept(InterpreterInterface& interpreter) = 0;
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

    void accept(InterpreterInterface& interpreter) override {
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

    static std::unique_ptr<Command> getEmptyCommand();
};

class SelfProcessCommand : public GrammarRule
{
public:
    SelfProcessCommandType type;
    std::vector<Assignable*> arguments;

    SelfProcessCommand(SelfProcessCommandType type, std::vector<std::unique_ptr<Assignable>>& arguments);

    void accept(InterpreterInterface& interpreter) override {
        interpreter.execute(*this);
    }

    ~SelfProcessCommand();
};

class Pipe : public GrammarRule
{
public:
    std::vector<Command*> commands;
    Pipe(std::vector<std::unique_ptr<Command>>& commands);

    void accept(InterpreterInterface& interpreter) override {
        interpreter.execute(*this);
    }

    ~Pipe() override;
};

#endif

