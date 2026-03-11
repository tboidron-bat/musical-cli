#pragma once

#include <string>

namespace cli::command::option
{
struct parameter_t
{
public:
    enum class Type
    {
        BOOL,
        INT,
        DOUBLE,
        CHAR,
        STRING
    };
    enum class Requirement
    {
        REQUIRED,
        OPTIONAL
    }; 

    Type _type;
    Requirement _requirement;
    std::string _name;
    std::string _description;
    std::string _value;
    bool _provided = false;

    parameter_t(
        Type type,
        std::string name,
        std::string description,
        Requirement requirement)
    :
        _type(type),
        _name(std::move(name)),
        _description(std::move(description)),
        _requirement(requirement)
    {}

    void parse(std::string_view);

    bool match_parameter(std::string_view);
};
};
