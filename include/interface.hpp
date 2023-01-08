#ifndef INTERFACE
#define INTERFACE
#include <string>
#include <iostream>

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