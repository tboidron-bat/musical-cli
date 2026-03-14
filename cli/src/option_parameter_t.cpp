#include <option_parameter_t.h>

#include <sstream>
#include <string>
#include <string_view>

namespace cli::command::option
{

bool parameter_t::match_parameter(std::string_view value)
{
    if(value.empty() || value[0] == '-')
        return false;

    std::istringstream iss{std::string(value)};

    switch(_type)
    {
        case Type::BOOL:
        {
            return value == "true"  ||
                   value == "false" ||
                   value == "1"     ||
                   value == "0";
        }

        case Type::INT:
        {
            int v;
            return (iss >> v) && iss.eof();
        }

        case Type::DOUBLE:
        {
            double v;
            return (iss >> v) && iss.eof();
        }

        case Type::CHAR:
        {
            return value.size() == 1;
        }

        case Type::STRING:
        {
            return true;
        }
    }

    return false;
}

void parameter_t::parse(std::string_view value)
{
    if(_type == Type::BOOL)
    {
        if(value == "1")
            _value = "true";
        else if(value == "0")
            _value = "false";
        else
            _value = std::string(value);
    }
    else
    {
        _value = std::string(value);
    }

    _provided = true;
}

} // namespace cli::command::option