#include <map>
#include "interface.hpp"
#include "parser.hpp"
#include "program.hpp"


using t_local_variables = std::map<std::string, std::string>;


int main(int argc, char *argv[]) {
    std::istream &in = std::cin;
    std::ostream &out = std::cout;
    Interface terminal;
    Parser parser;
    t_local_variables locals = {};  // TODO retrieve local variables from environment dynamically
    auto interpreter = Interpreter(locals);
    auto program = Program(parser, interpreter);

    if (argc == 1) {
        out << "interactive" <<std::endl;
        std::string parsable_string = "";
        while (parsable_string != "exit")
        {
            parsable_string = terminal.readInput(in);
            program.execute(parsable_string);
        }
    } else {
        out << "batch" <<std::endl;
        std::string command;
        for(int i = 1; i < argc; i++) command += argv[i];
        program.execute(command);
    }
}