#include "program.hpp"
#include "errors.hpp"


void Program::execute(const std::string& parsable_string) {
    try {
        auto ast = parser.parse(parsable_string);
        if (ast) ast->accept(interpreter);
    }
    catch (ShellError &e) {
        exit(1);
    }
};

// current_dir = std::string(std::filesystem::current_path());