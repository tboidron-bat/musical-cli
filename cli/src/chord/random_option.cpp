#include <chord/random_option.h>

#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/instruments/guitar/six_strings/stream_diagram.h>
#include <musical/io/instruments/guitar/six_strings/movable_shape_diagram_to_ascii.h>

#include <random>
#include <iostream>

namespace cli::chord
{
random_option::random_option(cli::Command*cmd)
:
option(cmd,"random","r","Show a completely random chord")
{    
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "count",
        "number of chord to generate"
        });
}
int random_option::execute() const
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    const bool choose_open = dist(gen) == 0;

    if (choose_open)
    {
        std::cout 
            << musical::instruments::guitar::six_strings::db_open_queries::get_random_diagram() 
            << "\n";
    }
    else
    {
        const auto diagram =
            musical::instruments::guitar::six_strings::db_movable_queries::get_random_diagram();

        std::cout
            << io::guitar::six_strings::movable_shape_diagram_to_ascii(diagram)
            << "\n";
    }

    return 0;
}

}

        //     "--random",
        //     "-r",
        //     "Show a completely random chord.",
        //     false,
        //     false,
        //     0,
        //     {}
