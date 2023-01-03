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


#endif