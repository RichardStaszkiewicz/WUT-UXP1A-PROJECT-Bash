#include <iostream>
#include <string>
#include <map>

#include "hello.hpp"
#include "parser.hpp"
#include "grammar.hpp"
#include "errors.hpp"

int main()
{
    // Parser parser("ls -al > /home/jakub/Desktop/testtesttesttest.txt \n");
    // Parser parser("cat < /home/jakub/Desktop/redirect_from.txt \n");
    // Parser parser("cat < /home/jakub/Desktop/redirect_from.txt | grep TEST \n");
    // Parser parser("ls -al | grep CMake | sort > /home/jakub/Desktop/example_output.txt \n");
    // Parser parser("local variable = $test\n");

    Parser parser("echo `ls -al` | grep CMake | grep 7");

    std::map<std::string, std::string> locals{};
    Interpreter interpreter = Interpreter(locals);

    try
    {
        auto ast = parser.parse();
        ast->accept(interpreter);
    }
    catch (ShellError &e)
    {
        exit(1);
    }

    exit(0);
}