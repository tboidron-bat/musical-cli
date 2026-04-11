#pragma once

#include <option_parameter_t.h>

#include <vector>
#include <string>
#include <string_view>
#include <ostream>

namespace cli
{
    class Command;
}
namespace cli::command
{
class Option
{
protected:

    cli::Command& _command_ref;
    bool _enabled = false;

private:

    std::string _name;
    std::string _short_name;
    std::string _description;

    std::vector<option::parameter_t> _parameters;

public:

    Option(
        cli::Command& command,
        std::string name,
        std::string short_name,
        std::string description)
    :
        _command_ref(command),
        _name(std::move(name)),
        _short_name(std::move(short_name)),
        _description(std::move(description))
    {}

    virtual ~Option() = default;

    void add_parameter(option::parameter_t);


    virtual int execute() const = 0;    

    size_t parse(int argc, char** argv);    

public:

    std::string name() { return _name; }
    std::string short_name(){ return _short_name; }    

    const std::string& name() const { return _name; }
    const std::string& short_name() const { return _short_name; }






    const option::parameter_t& parameter(int index) const;    

    std::size_t parameter_count() const { return _parameters.size(); } 

    cli::Command& command() { return _command_ref; }
    const cli::Command& command() const { return _command_ref; }
    
    bool enabled() const;

    std::string print_usage() const;

    friend std::ostream& operator<<(std::ostream& os, const Option& opt);        
};
}