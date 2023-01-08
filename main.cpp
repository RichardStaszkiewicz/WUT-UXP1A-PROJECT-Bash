#include <map>
#include "interface.hpp"
#include "parser.hpp"
#include "program.hpp"


using t_local_variables = std::map<std::string, std::string>;


int main(int argc, char *argv[]) {
    Interface terminal;
    Parser parser;
    t_local_variables locals = {};  // TODO retrieve local variables from environment dynamically
    auto interpreter = Interpreter(locals);
    auto program = Program(terminal, parser, interpreter);

    if (argc == 1) {
        program.run_interactive();
    } else {
        program.run_batch(argc, argv);
    }
}