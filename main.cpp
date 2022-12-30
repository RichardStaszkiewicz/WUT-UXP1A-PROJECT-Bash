#include <iostream>
#include <string>
#include <map>

#include "hello.hpp"
#include "parser.hpp"
#include "grammar.hpp"
#include "errors.hpp"
#include "interface.hpp"
// jak są problemy z linkowaniem nowych plików - po prostu wywołajcie Ctrl+S na CMakeLists.txt nie zmieniając niczego
// tzn, po prostu rekonfigurujcie CMakeCache

int main(int argc, char *argv[])
{
    Interface terminal;
    switch(argc)
    {
        case 1:
            std::cout << "interactive" <<std::endl;
            terminal.run_interactive();
            break;
        default:
            std::cout << "batch" <<std::endl;
    }

    return 0;
}