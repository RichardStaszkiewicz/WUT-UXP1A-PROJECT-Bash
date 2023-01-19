#include "errors.hpp"
#include "interface.hpp"
#include "parser.hpp"
#include "program.hpp"
#include <map>


using t_local_variables = std::map<std::string, std::string>;


int main(int argc, char *argv[]) {
    Interface terminal(std::cin, std::cout);
    Parser parser;
    t_local_variables locals = {};  // TODO retrieve local variables from environment dynamically
    auto interpreter = Interpreter(&parser, locals);
    auto program = Program(parser, interpreter);

    if (argc == 1) {
        terminal.writeOutput("interactive\n");
        std::string parsable_string = "";
        while (parsable_string != "exit")
        {
            terminal.writePrompt();
            parsable_string = terminal.readInput();
            try {
                program.execute(parsable_string);
            }
            catch (ShellError &e) {
                terminal.writeOutput(e.what());
            }
        }
    } else {
        terminal.writeOutput("batch\n");
        std::string command;
        for(int i = 1; i < argc; i++) command += argv[i];
        program.execute(command);
    }
}