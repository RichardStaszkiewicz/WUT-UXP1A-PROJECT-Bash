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
    void run_interactive();
    //void run_batch();
    //~Interface() = default;
};

#endif