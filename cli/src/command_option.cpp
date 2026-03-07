#include <command_option.h>

#include <stdexcept>
#include <string>

namespace cli::command
{

bool option::match_parameter(
    const parameter_t& param,
    std::string_view value)
{
    if(value.empty())
        return false;

    if(value.starts_with("-"))
        return false;

    try
    {
        switch(param._type)
        {
            case parameter_t::Type::INT:
            {
                std::stoi(std::string(value));
                return true;
            }

            case parameter_t::Type::DOUBLE:
            {
                std::stod(std::string(value));
                return true;
            }

            case parameter_t::Type::CHAR:
            {
                return value.size() == 1;
            }

            case parameter_t::Type::STRING:
            {
                return true;
            }
        }
    }
    catch(...)
    {
        return false;
    }

    return false;
}


size_t option::parse_parameters(
    int argc,
    char** argv,
    int start_index)
{
    size_t parsed = 0;

    for(size_t k = 0; k < _parameters.size(); ++k)
    {
        int arg_index = start_index + k;

        if(arg_index >= argc)
            break;

        std::string_view candidate = argv[arg_index];

        if(!match_parameter(_parameters[k], candidate))
            break;

        _parameters[k]._value = candidate;
        _parameters[k]._provided = true;

        ++parsed;
    }

    return parsed;
}


bool option::parse(
    int argc,
    char** argv)
{
    for(int i = 1; i < argc; ++i)
    {
        std::string_view arg = argv[i];

        bool match =
            arg == "--" + _name ||
            (!_short_name.empty() && arg == "-" + _short_name);

        if(!match)
            continue;

        _enabled = true;

        size_t consumed =
            parse_parameters(argc, argv, i + 1);

        i += consumed;

        return true;
    }

    return false;
}


std::string option::print_usage() const
{
    return {};
}
} // namespace cli::command