#include <iostream>
#include <string>
#include <map>

#include "hello.hpp"
#include "parser.hpp"
#include "grammar.hpp"
#include "errors.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;

    // Parser parser("ls -al > /home/jakub/Desktop/redirect_from.txt \n");
    // Parser parser("cat < /home/jakub/Desktop/redirect_from.txt \n");
    // Parser parser("cat < /home/jakub/Desktop/redirect_from.txt | grep TEST \n");
    
    // Parser parser("ls -al | grep CMake | sort > /home/jakub/Desktop/example_output.txt \n");

    Parser parser("echo `ls -al`");


    //Parser parser("local variable = $test\n");
    // Parser parser("abc.sh sav asd < 435534 | cds csd | ncds");

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

    std::map<std::string, std::string> locals{};
    Interpreter interpreter = Interpreter(locals);

    ast->accept(interpreter);

    // Pipe *pipe = dynamic_cast<Pipe *>(ast);
    // if (pipe != nullptr)
    // {
    //     std::cout << "ŚCIEŻKA KOMENDY" << std::endl;
    // }

    // Assignment *asgm = dynamic_cast<Assignment *>(ast);
    // if (asgm != nullptr)
    // {
    //     std::cout << "ŚCIEŻKA PRZYPISANIA" << std::endl;
    // }

    // std::cout << assignment->commands[0]->program << std::endl;

    delete ast;
    return 0;
}