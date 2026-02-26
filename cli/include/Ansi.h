#pragma once
#include <string>

namespace cli::ansi
{
    inline bool enabled = true;

    inline std::string bold(const std::string& s)
    {
        if (!enabled) return s;
        return "\033[1m" + s + "\033[0m";
    }

    inline std::string cyan(const std::string& s)
    {
        if (!enabled) return s;
        return "\033[36m" + s + "\033[0m";
    }
}