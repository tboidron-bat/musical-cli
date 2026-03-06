#pragma once

#include <vector>
#include <string>
#include <option_t.h>
#include <command_option.h>

namespace cli
{

class Command
{
public:
    virtual ~Command() = default;

    virtual std::string get_name() const = 0;
    virtual std::string get_description() const = 0;    
    virtual std::string get_usage() const = 0;        
    virtual std::string get_help() const = 0;            

    virtual int run(int argc, char** argv) = 0;

protected:

    std::vector<cli::command::option> _options;    

    cli::command::option& add_option(
        uint8_t id,
        std::string name,
        std::string short_name,
        std::string description)
    {
        _options.emplace_back(
            id,
            std::move(name),
            std::move(short_name),
            std::move(description));

        return _options.back();
    }    
};

}
