#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <optional>

namespace cli
{

struct globalconfig_t
{
    bool help = false;
    bool version = false;
    bool verbose = false;
    bool json = false;

    std::vector<std::string> positional_args;  
    
    std::unordered_map<std::string, std::vector<std::string>> options;       
};

class ArgumentParser
{
public:
    static globalconfig_t parse(int argc, char** argv);
};

}
