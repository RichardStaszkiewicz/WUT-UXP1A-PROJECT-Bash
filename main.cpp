#include "interface.hpp"
#include "parser.hpp"
#include "program.hpp"
#include <map>


extern char **environ;


int main(int argc, char *argv[]) {
    Interface terminal;
    Parser parser;
    auto interpreter = Interpreter(environ);
    auto program = Program(parser, interpreter);

    if (argc == 1) { // interactive
        // TODO should use Interface (terminal) to communicate with user
        // something like -> do {program.execute(command)} while (command = terminal.getNextCommand())
        std::cout << "interactive" << std::endl;
        std::string parsable_string = "";
        while (parsable_string != "exit") {
            getline(std::cin, parsable_string);
            program.execute(parsable_string);
        }
    } else { // batch
        // TODO same, should use Interface like above
        std::cout << "batch" << std::endl;
        std::string command;
        for (int i = 1; i < argc; i++) command += argv[i];
        program.execute(command);
    }
}