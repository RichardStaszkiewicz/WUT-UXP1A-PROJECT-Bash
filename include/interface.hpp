#ifndef INTERFACE
#define INTERFACE
#include <string>
#include <iostream>

// TODO to be reworked, probably should implement some interface
class Interface
{
private:
    std::string current_dir;
public:
    Interface();
    Interface(std::string current_dir);
    void run_interactive();                     // ./program
    void run_batch(std::string parsable);       // ./program "{requested command}"
    //~Interface() = default;
};

#endif