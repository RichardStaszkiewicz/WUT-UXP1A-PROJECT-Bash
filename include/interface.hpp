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
    std::string prompt = "UXP1a$ ";
public:
    Interface();
    Interface(std::istream& is, std::ostream& os);
    Interface(std::string current_dir);
    std::string readInput();
    int writeOutput(std::string message);
    int writePrompt();

    std::string get_current_dir();
    std::istream& get_in();
    std::ostream& get_out();
    void set_current_dir(std::string new_dir);
};

#endif