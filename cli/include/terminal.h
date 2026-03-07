#pragma once

#include <string>

#include <sys/ioctl.h>
#include <unistd.h>

namespace cli
{
    class terminal
    {
    public:
    static bool is_interactive()
    {
        return isatty(STDOUT_FILENO);
    }        

    static std::size_t get_width()
    {
        struct winsize w{};
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
            return w.ws_col;
        return 120;
    }
    };
}

