#ifndef ERRORS
#define ERRORS

#include <exception>

class ShellError : public std::exception
{
public:
    ShellError();
    virtual ~ShellError();
};

class ParseError : public ShellError
{
public:
    ParseError();
    ~ParseError() override;
};

class InterpretError : public ShellError
{
public:
    InterpretError();
    ~InterpretError() override;
};

class AssignmentInterpretError : public InterpretError
{
public:
    AssignmentInterpretError();
    ~AssignmentInterpretError() override;
};

class AssignmentNameInterpretError : public AssignmentInterpretError
{
public:
    AssignmentNameInterpretError();
    ~AssignmentNameInterpretError() override;
};

class MemoryAssignmentInterpretError : public AssignmentInterpretError
{
public:
    MemoryAssignmentInterpretError();
    ~MemoryAssignmentInterpretError() override;
};

#endif