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

std::string Interface::get_current_dir() {return current_dir;}
std::istream& Interface::get_in() {return in;}
std::ostream& Interface::get_out() {return out;};
void Interface::set_current_dir(std::string new_dir) {current_dir = new_dir; return;};
