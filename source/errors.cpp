#include "errors.hpp"

ShellError::ShellError(const char* msg ): message(msg)
{
}

ShellError::~ShellError()
{
}

const char * ShellError::what () {
    return this->message;
}

ParseError::ParseError(const char* msg) : ShellError(msg)
{
}

ParseError::~ParseError()
{
}
