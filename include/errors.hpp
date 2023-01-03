#ifndef ERRORS
#define ERRORS

#include <exception>

class ShellError : public std::exception
{
private:
    const char* message;
public:
    ShellError(const char* msg);

    virtual const char * what ();
    virtual ~ShellError();
};

class ParseError : public ShellError
{
public:
    ParseError(const char* msg);
    ~ParseError() override;
};


#endif