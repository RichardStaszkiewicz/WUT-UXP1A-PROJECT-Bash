#include "interface.hpp"
#include <string>
#include <iostream>
#include <filesystem>

Interface::Interface()
{
    current_dir = std::string(std::filesystem::current_path());
}

Interface::Interface(std::string dir) : current_dir(dir) {};

void Interface::run_interactive()
{
    std::string parsable_string = "";
    while (parsable_string != "exit")
    {
        std::cout << "(" << current_dir << ")$ ";
        getline(std::cin, parsable_string);
        std::cout << parsable_string;
    }
}
