#pragma once

#include <string>

namespace cli
{

struct option_t
{
    std::string _long_name;    // "--help"
    std::string _short_name;   // "-h"
    std::string _description;

    bool takes_value = false;
    bool value_optional = false;

    std::vector<std::string> value_suggestions;    
};


static const std::vector<option_t> opts =
{
    {
        "--diagram",
        "-d",
        "Show chord diagram [position 1–5 optional]",
        true,
        true,
        { "1","2","3","4","5" }
    },
    {
        "--difficulty",
        "",
        "Filter diagrams by difficulty level (1–3)",
        true,
        false,
        { "1","2","3" }
    },
    {
        "--tuning",
        "",
        "Guitar tuning",
        true,
        false,
        { "standard","dropd","dadgad","openG","openD" }
    },
    {
        "--help",
        "-h",
        "Show this help message",
        false,
        false,
        {}
    }
};

}
