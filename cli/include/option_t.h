#pragma once

#include <string>

namespace cli
{

struct option_t
{
    std::string _long_name;
    std::string _short_name;
    std::string _description;

    bool takes_value = false;
    bool value_optional = false;

    size_t max_values = 1;   // 🔥 nouveau

    std::vector<std::string> value_suggestions;
};
}

