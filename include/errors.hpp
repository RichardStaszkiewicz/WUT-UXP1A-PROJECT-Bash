#ifndef ERRORS
#define ERRORS

#include <exception>

class ShellError : public std::exception
{
private:
    char* message;
public:
    explicit ShellError(char* message) : message(message) {};
    char* what() { return message; };
    ~ShellError() override;
};

class ParseError : public ShellError
{
public:
    explicit ParseError(char* message="");
    ~ParseError() override;
};

class InterpretError : public ShellError
{
public:
    explicit InterpretError(char *message="");
    ~InterpretError() override;
};

class AssignmentInterpretError : public InterpretError
{
public:
    explicit AssignmentInterpretError(char *message="");
    ~AssignmentInterpretError() override;
};

class AssignmentNameInterpretError : public AssignmentInterpretError
{
public:
    explicit AssignmentNameInterpretError(char *message="");
    ~AssignmentNameInterpretError() override;
};

class MemoryAssignmentInterpretError : public AssignmentInterpretError
{
public:
    explicit MemoryAssignmentInterpretError(char *message="");
    ~MemoryAssignmentInterpretError() override;
};

#endif