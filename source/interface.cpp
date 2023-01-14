#include "interface.hpp"
#include <string>
#include <iostream>
#include <filesystem>
#include <map>

Interface::Interface()
{
//    current_dir = std::string(std::filesystem::current_path());
}

Interface::Interface(std::istream& is, std::ostream& os) : in(is), out(os) {};

Interface::Interface(std::string dir) : current_dir(dir) {};

std::string Interface::readInput()
{
    std::string parsable_string;
    getline(in, parsable_string);
    return parsable_string;
}

int Interface::writeOutput(std::string message)
{
    out << message;
    return 0;
}