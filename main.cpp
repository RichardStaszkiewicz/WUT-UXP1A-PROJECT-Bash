#include <iostream>
#include "hello.hpp"
#include "parser.hpp"
#include "grammar.hpp"

int main()
{
    std::cout << "Hello world!" <<std::endl;
    
    // Parser parser("export variable = `ls -a`\n");
    Parser parser("ls sav asd < 435534 | sd cds csd | ./dfc/cds/ cds wqd dqw > 342");

    GrammarRule* ast = parser.parse();
    
    Pipe* pipe = dynamic_cast<Pipe*>(ast);
    if (pipe != nullptr)
    {
        std::cout << "ŚCIEŻKA KOMENDY" << std::endl;
    }
    
    Assignment* asgm = dynamic_cast<Assignment*>(ast);
    if (asgm != nullptr)
    {
        std::cout << "ŚCIEŻKA PRZYPISANIA" << std::endl;
    }

    // std::cout << assignment->commands[0]->program << std::endl;
    Hello();

    delete ast;
    return 0;
}