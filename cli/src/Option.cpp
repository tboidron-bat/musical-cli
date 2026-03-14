#include <Option.h>

#include <stdexcept>
#include <iostream>

//#define DEBUG_COMMAND_OPTION

namespace cli::command
{
cli::Command& Option::command() const 
{
   return _command_ref;
}
bool Option::enabled() const 
{
    return _enabled;
}
void Option::add_parameter(option::parameter_t p) 
{
        _parameters.push_back(std::move(p));
}
const option::parameter_t& Option::parameter(int index) const
{
    if(index < 0 || static_cast<size_t>(index) >= _parameters.size())
    {
        throw std::out_of_range("Parameter index out of range");
    }

    return _parameters[index];
}
size_t Option::parse(int argc, char** argv)
{
    _enabled = false;

    int arg_index = -1;

    std::string long_name  = "--" + _name;
    std::string short_name = "-"  + _short_name;

    for(int i = 1; i < argc; ++i)
    {
        std::string_view arg = argv[i];

        if(arg == long_name || arg == short_name)
        {
            arg_index = i;
            break;
        }
    }

    if(arg_index == -1)
        return EXIT_FAILURE;

    for(auto& p : _parameters)
    {
        arg_index++;

        if(arg_index >= argc)
        {
            if(p._requirement ==
               option::parameter_t::Requirement::REQUIRED)
            {
                throw std::runtime_error(
                    "Missing required parameter: " + p._name);
            }

            break;
        }

        std::string_view value = argv[arg_index];

        if(!p.match_parameter(value))
        {
            if(p._requirement ==
               option::parameter_t::Requirement::REQUIRED)
            {
                throw std::runtime_error(
                    "Invalid value for parameter: " + p._name);
            }

            break;
        }

        p.parse(value);
    }

#ifdef DEBUG_COMMAND_OPTION    
    std::cout << "[Option: " << _name << "] enabled\n" << std::endl;
#endif

    _enabled = true;
    return EXIT_SUCCESS;
}
std::string Option::print_usage() const
{
    std::string usage;

    // if(!_short_name.empty())
    // {
    //     usage += "-";
    //     usage += _short_name;
    //     usage += ", ";
    // }

    // usage += "--";
    // usage += _name;

    // for(const auto& p : _parameters)
    // {
    //     if(p._requirement == option::parameter_t::Requirement::REQUIRED)
    //         usage += " <" + p._name + ">";
    //     else
    //         usage += " [" + p._name + "]";
    // }

    return usage;
}

} // namespace cli::command