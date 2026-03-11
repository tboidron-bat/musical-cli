#pragma once

#include <CommandOption.h>

#include <sstream>
#include <ostream>
#include <iomanip>

namespace cli::command
{
inline std::ostream& operator<<(std::ostream& os, const Option& opt)
{
    constexpr int col1_width = 28;

    std::ostringstream name;

    if (!opt._short_name.empty())
        name << "-" << opt._short_name << ", ";

    name << "--" << opt._name;

    for (const auto& p : opt._parameters)
    {
        if(p._requirement == option::parameter_t::Requirement::REQUIRED)
            name << " <" << p._name << ">";
        else
            name << " [" << p._name << "]";
    }
    os << "  "
       << std::left << std::setw(col1_width)
       << name.str()
       << opt._description << '.' << "\n";

    for (const auto& p : opt._parameters)
    {
        os << std::setw(col1_width + 2) << " "
           << p._name << ": "
           << p._description << '.' << "\n";
    }

    os << "\n";

    return os;
}

}