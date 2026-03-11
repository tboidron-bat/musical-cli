#pragma once

#include <vector>
#include <string>
#include <memory>

#include <CommandOption.h>

namespace cli
{
class Command
{
public:
    virtual ~Command() = default;

    virtual int run(int argc, char** argv) = 0;

protected:   
    std::vector<std::unique_ptr<cli::command::Option>> _options;    

public:

    // cli::command::Option& add_short_option(
    //     uint8_t id,
    //     std::string name,
    //     std::string short_name,
    //     std::string description)
    // {
    //     _options.emplace_back(
    //         id,
    //         std::move(name),
    //         std::move(short_name),
    //         std::move(description));

    //     return _options.back();
    // }    

public:
    virtual void print_usage() const = 0;        
    virtual void print_help() const = 0;   
    virtual void print_name() const = 0;                 
};

}
