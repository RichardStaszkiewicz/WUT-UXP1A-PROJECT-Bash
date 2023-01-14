#ifndef INTERFACE
#define INTERFACE
#include <string>
#include <iostream>

class Interface
{
private:
    std::string current_dir;
    std::istream& in = std::cin;
    std::ostream& out = std::cout;
public:
    Interface();
    Interface(std::istream& is, std::ostream& os);
    Interface(std::string current_dir);
    std::string readInput();
    int writeOutput(std::string message);
};

#endif