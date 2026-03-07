#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <cstdint>
#include <utility>
#include <string_view>
#include <stdexcept>

namespace cli
{
    class Command;
}

namespace cli::command
{

class option
{
protected:

    cli::Command* _command = nullptr;
    bool _enabled = false;

public:

    struct parameter_t
    {
        enum class Type
        {
            INT,
            DOUBLE,
            CHAR,
            STRING
        };

        Type _type;

        std::string _name;
        std::string _description;

        std::string _value;

        bool _provided = false;

        parameter_t(
            Type type,
            std::string name,
            std::string description)
        :
            _type(type),
            _name(std::move(name)),
            _description(std::move(description))
        {}
    };

private:

    std::string _name;
    std::string _short_name;
    std::string _description;

    std::vector<parameter_t> _parameters;

public:

    option(
        cli::Command* command,
        std::string name,
        std::string short_name,
        std::string description)
    :
        _command(command),
        _name(std::move(name)),
        _short_name(std::move(short_name)),
        _description(std::move(description))
    {}

    virtual ~option() = default;

public:

    cli::Command* command() const
    {
        return _command;
    }

    bool enabled() const
    {
        return _enabled;
    }

    virtual int execute() const = 0;

public:

    void add_parameter(parameter_t p)
    {
        _parameters.push_back(std::move(p));
    }

    size_t parameters_count() const
    {
        return _parameters.size();
    }

public:

    size_t find_parameter(std::string_view name) const
    {
        for(size_t i = 0; i < _parameters.size(); ++i)
        {
            if(_parameters[i]._name == name)
                return i;
        }

        throw std::runtime_error(
            "Unknown parameter: " + std::string(name));
    }

    const parameter_t& parameter(std::string_view name) const
    {
        return _parameters[find_parameter(name)];
    }

public:

    bool has_parameter(std::string_view name) const
    {
        return parameter(name)._provided;
    }

    int parameter_value_int(std::string_view name) const
    {
        const auto& p = parameter(name);

        if(!p._provided)
            throw std::runtime_error("Parameter not provided");

        return std::stoi(p._value);
    }

    double parameter_value_double(std::string_view name) const
    {
        const auto& p = parameter(name);

        if(!p._provided)
            throw std::runtime_error("Parameter not provided");

        return std::stod(p._value);
    }

    std::string parameter_value_string(std::string_view name) const
    {
        const auto& p = parameter(name);

        if(!p._provided)
            throw std::runtime_error("Parameter not provided");

        return p._value;
    }

public:

    bool match_parameter(
        const parameter_t& param,
        std::string_view value);

    size_t parse_parameters(
        int argc,
        char** argv,
        int start_index);

    bool parse(
        int argc,
        char** argv);

public:

    bool takes_value() const
    {
        return !_parameters.empty();
    }

    std::string print_usage() const;

    friend std::ostream& operator<<(std::ostream& os, const option& opt);        
};
inline std::ostream& operator<<(std::ostream& os, const option& opt)
{
    os << "  ";

    if (!opt._short_name.empty())
        os << "-" << opt._short_name << ", ";

    os << "--" << opt._name;

    for (const auto& p : opt._parameters)
        os << " <" << p._name << ">";

    os << "\n";

    os << "      " << opt._description << "\n";

    for (const auto& p : opt._parameters)
    {
        os << "      "
           << p._name << ": "
           << p._description << "\n";
    }

    os << "\n";

    return os;
}
}