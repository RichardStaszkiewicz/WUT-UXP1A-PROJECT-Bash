#include "parser.hpp"
#include "grammar.hpp"
#include "errors.hpp"
#include "lex.yy.c"

#include <iostream>
#include <memory>

std::unique_ptr<GrammarRule> Parser::parse(const std::string& rawRequest)
{
    yy_scan_string(rawRequest.c_str());
    current = yylex();

    std::unique_ptr<GrammarRule> request = nullptr;

    if ((request = parseSelfProcessCommand()) != nullptr)
    {
        return request;
    }

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

std::unique_ptr<SelfProcessCommand> Parser::parseSelfProcessCommand()
{
    SelfProcessCommandType type;
    if (strcmp(yytext, "cd") == 0)
    {
        type = SelfProcessCommandType::CD;
    }
    else
    {
        return nullptr;
    }
    
    advance();

    std::vector<std::unique_ptr<Assignable>> arguments = parseAssignables();
    return std::make_unique<SelfProcessCommand>(type, arguments);
}

std::vector<std::unique_ptr<Assignable>> Parser::parseAssignables()
{
    std::unique_ptr<Assignable> argument;
    std::vector<std::unique_ptr<Assignable>> arguments;
    while ((argument = parseAssignable()) != nullptr)
    {
        arguments.push_back(std::move(argument));
    }

    return arguments;
}

std::unique_ptr<Assignment> Parser::parseAssignment()
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
        std::cerr << "Invalid input - '=' sign expected, got: " << yytext << std::endl;
        throw ParseError();
    }

    advance();
    std::unique_ptr<Assignable> assignable = parseAssignable();

    if (assignable == nullptr)
    {
        std::cerr << "Invalid input - assignable expression expected, got: " << yytext << std::endl;
        throw ParseError();
    }

    return std::make_unique<Assignment>(type, name, assignable.release());
}

std::unique_ptr<Assignable> Parser::parseAssignable()
{
    std::string value = yytext;

    AssignableType type;
    if (current == WORD || current == IDENTIFIER || current == PATH)
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
    return std::make_unique<Assignable>(type, value);
}

std::unique_ptr<Pipe> Parser::parsePipe()
{
    std::vector<std::unique_ptr<Command>> commands;
    
    commands.push_back(std::move(parseCommand()));

    while (current == PIPE)
    {
        advance();
        commands.push_back(std::move(parseCommand()));
    }

    return std::make_unique<Pipe>(commands);
}

std::unique_ptr<Command> Parser::parseCommand()
{
    if (current != IDENTIFIER && current != WORD && current != PATH)
    {
        std::cerr << "Parse error - WORD expected, got:  " << yytext << std::endl;
        throw ParseError();
    }

    std::string program = yytext;
    advance();

    std::unique_ptr<Assignable> argument;
    std::vector<std::unique_ptr<Assignable>> arguments;
    while ((argument = parseAssignable()) != nullptr)
    {
        arguments.push_back(std::move(argument));
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

    return std::make_unique<Command>(program, arguments, from, to);
}

void Parser::advance()
{
    current = yylex();

    if (current == UNKNOWN)
    {
        std::cerr << "Parsing error - Unknown token:  " << yytext << std::endl;
        throw ParseError();
    }
    
}
