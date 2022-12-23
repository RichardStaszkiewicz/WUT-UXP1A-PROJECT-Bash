#ifndef GRAMMAR
#define GRAMMAR
#include <string>
#include <vector>

enum class AssignmentType { LOCAL, EXPORT };
enum class AssignableType { WORD, VARIABLE, QUOTE, INVQUOTE };

class GrammarRule
{
public:
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
    ~Assignment() override;
}; 

class Command
{
public:
    std::string program;
    std::vector<Assignable*> arguments;
    std::string* redirectFrom;
    std::string* redirectTo;

    Command(std::string program, std::vector<Assignable*> arguments, 
        std::string* redirectFrom = nullptr, std::string* redirectTo = nullptr);
    ~Command();
};

class Pipe : public GrammarRule
{
public:
    std::vector<Command*> commands;
    Pipe(std::vector<Command*> commands);
    ~Pipe() override;
};

#endif

