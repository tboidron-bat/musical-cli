#pragma once

#include <vector>
#include <string>
#include <memory>

#include <Option.h>

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

    template<typename T>
    T* get_option()
    {
        for(auto& opt : _options)
        {
            if(auto p = dynamic_cast<T*>(opt.get()))
                return p;
        }

        return nullptr;
    }

    std::vector<std::unique_ptr<cli::command::Option>>& options() { return _options; }
    const std::vector<std::unique_ptr<cli::command::Option>>& options() const { return _options; }      

public:
    virtual void print_usage() const = 0;        
    virtual void print_help() const = 0;   
    virtual void print_name() const = 0;                 
};

}
