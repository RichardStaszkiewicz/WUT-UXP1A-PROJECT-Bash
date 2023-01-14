#include "interface.hpp"
#include <string>
#include <iostream>
#include <filesystem>

Interface::Interface()
{
//    current_dir = std::string(std::filesystem::current_path());
}

Interface::Interface(std::string dir) : current_dir(dir) {};

void Interface::run_interactive()
{
//    std::string parsable_string = "";
//    while (parsable_string != "exit")
//    {
//        std::cout << "(" << current_dir << ")$ ";
//        getline(std::cin, parsable_string);
//        execute_parsable_string(parsable_string);
//    }
}

void Interface::run_batch(std::string parsable)
{
//    execute_parsable_string(parsable);
}
