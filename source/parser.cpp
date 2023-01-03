#include "parser.hpp"
#include "grammar.hpp"
#include "errors.hpp"
#include <iostream>

#include "lex.yy.c"

Parser::Parser(std::string request)
{
    yy_scan_string(request.c_str());
    current = yylex();
}

Parser::~Parser()
{
}

GrammarRule *Parser::parse()
{
    GrammarRule *request = nullptr;

    if ((request = parseAssignment()) != nullptr)
    {
        return request;
    }

    if ((request = parsePipe()) != nullptr)
    {
        return request;
    }

    return nullptr;
}

Assignment *Parser::parseAssignment()
{
    AssignmentType type;
    if (current == LOCAL)
    {
        type = AssignmentType::LOCAL;
    }
    else if (current == EXPORT)
    {
        type = AssignmentType::EXPORT;
    }
    else
    {
        return nullptr;
    }

    advance();
    std::string name = yytext;

    advance();
    if (strcmp(yytext, "=") != 0)
    {
        throw ParseError("Invalid input - '=' sign expected");
    }

    advance();
    Assignable *assignable = parseAssignable();

    if (assignable == nullptr)
    {
        throw ParseError("Invalid input - assignable expression expected");
    }

    return new Assignment(type, name, assignable);
}

Assignable *Parser::parseAssignable()
{
    std::string value = yytext;

    AssignableType type;
    if (current == WORD || current == IDENTIFIER)
    {
        type = AssignableType::WORD;
    }
    else if (current == VARIABLE)
    {
        type = AssignableType::VARIABLE;
        value.erase(0, 1);
    }
    else if (current == QUOTE)
    {
        type = AssignableType::QUOTE;
        value.erase(0, 1);
        value.pop_back();
    }
    else if (current == INVQUOTE)
    {
        type = AssignableType::INVQUOTE;
        value.erase(0, 1);
        value.pop_back();
    }
    else
    {
        return nullptr;
    }

    advance();
    return new Assignable(type, value);
}

Pipe *Parser::parsePipe()
{
    std::vector<Command *> commands;
    
    commands.push_back(parseCommand());

    while (current == PIPE)
    {
        advance();
        commands.push_back(parseCommand());
    }

    return new Pipe(commands);
}

Command *Parser::parseCommand()
{
    if (current != IDENTIFIER && current != WORD && current != PATH)
    {
        throw ParseError("Parse error - WORD expected");
    }

    std::string program = yytext;
    advance();

    Assignable *argument;
    std::vector<Assignable *> arguments;
    while ((argument = parseAssignable()) != nullptr)
    {
        arguments.push_back(argument);
    }

    std::string *from = nullptr;
    std::string *to = nullptr;

    for (size_t i = 0; i < 2; i++)
    {
        if (current == FROM)
        {
            advance();
            from = new std::string(yytext);
            advance();
        }

        if (current == TO)
        {
            advance();
            to = new std::string(yytext);
            advance();
        }
    }

    return new Command(program, arguments, from, to);
}

void Parser::advance()
{
    current = yylex();

    if (current == UNKNOWN)
    {
        throw ParseError("Parsing error - Unknown token");
    }
    
}
