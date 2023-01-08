#include "program.hpp"
#include "errors.hpp"


void Program::run_interactive() {
    std::cout << "interactive" <<std::endl;
    std::string parsable_string = "";
    while (parsable_string != "exit")
    {
        getline(std::cin, parsable_string);
        execute(parsable_string);
    }
};

void Program::run_batch(int argc, char* argv[]) {
    std::cout << "batch" <<std::endl;
    std::string command;
    for(int i = 1; i < argc; i++) command += argv[i];
    execute(command);
}

void Program::execute(std::string parsable_string) {
    try {
        auto ast = parser.parse(parsable_string);
        ast->accept(interpreter);
    }
    catch (ShellError &e) {
        exit(1);
    }
};

// current_dir = std::string(std::filesystem::current_path());