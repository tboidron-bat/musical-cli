#pragma once

#include <vector>
#include <string>
#include <option_t.h>

namespace cli
{

class Command
{
public:
    virtual ~Command() = default;

    // Options disponibles pour la commande    
    virtual const std::vector<option_t>& options() const = 0;

    // Exécute la commande    
    virtual int run(int argc, char** argv) = 0;
};

}
