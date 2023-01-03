#include <iostream>
#include "hello.hpp"
#include "parser.hpp"
#include "grammar.hpp"
#include "errors.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;

    // Parser parser("export variable = `ls -a`\n");
    Parser parser("abc.sh sav asd < 435534 | cds csd | ncds");

    GrammarRule *ast;
    try
    {
        ast = parser.parse();
    }
    catch (ParseError& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    Pipe *pipe = dynamic_cast<Pipe *>(ast);
    if (pipe != nullptr)
    {
        std::cout << "ŚCIEŻKA KOMENDY" << std::endl;
    }

    Assignment *asgm = dynamic_cast<Assignment *>(ast);
    if (asgm != nullptr)
    {
        std::cout << "ŚCIEŻKA PRZYPISANIA" << std::endl;
    }

    // std::cout << assignment->commands[0]->program << std::endl;
    Hello();

    delete ast;
    return 0;
}