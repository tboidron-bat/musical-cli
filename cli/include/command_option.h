#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <cstdint>
#include <functional>

namespace cli::command
{
class option
{
public:
    struct argument_t
    {
        enum class Type
        {
            INT,
            CHAR,
            STRING

        };
        Type _type;
        std::string _name;
        std::string _description; 
        std::string _value;             
        
        argument_t(Type type,
                std::string name,
                std::string description)
            :
            _type(type),
            _name(std::move(name)),
            _description(std::move(description))
        {}                
    };

private:
    uint8_t _id;
    std::string _name;
    std::string _short_name;
    std::string _description;    

    std::vector<argument_t> _arguments;

    std::function<int()> _handler;       
    //ou std::function<int(int argc, char** argv)> _handler;    

public:    
    option(
        uint8_t _id,
        std::string name, 
        std::string short_name,
        std::string description,
        std::function<int()> handler)
        : 
        _id(_id),
        _name(std::move(name)),
        _short_name(std::move(short_name)),
        _description(std::move(description)),
        _handler(handler)
    {}

    uint8_t id() const {return _id;}    

    int execute()
    {
        if(_handler)
            return _handler();

        return 0;
    }    

    void add_argument(argument_t arg)
    {
        _arguments.push_back(std::move(arg));
    }
    size_t argument_count() const
    {
        return _arguments.size();
    }
    const std::string& value(size_t i) const
    {
        return _arguments[i]._value;
    }    

    bool parse(int argc, char** argv);    

    bool takes_value() const
    {
        return !_arguments.empty();
    }

    std::string print_usage() const;
};

inline std::ostream& operator<<(std::ostream& os, const option& opt)
{
    os << opt.print_usage();
    return os;
}
}




