#include <command/chord/random_option.h>

#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/guitar/stream_diagram.h>
//#include <musical/io/guitar/stream_diagram2.h>
#include <musical/io/guitar/diagram/unicode/Movable.h>

#include <random>
#include <iostream>

namespace cli::chord
{
random_option::random_option(cli::Command*cmd)
:
command::Option(cmd,"random","r","Show a completely random chord")
{    
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "value",
        "If provided, generate <value> random chords",
        command::option::parameter_t::Requirement::OPTIONAL
        });
}
int random_option::execute() const
{
    if(!_enabled)
        return 0;

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
            //<< io::guitar::six_strings::movable_shape_diagram_to_ascii(diagram)
            << io::guitar::diagram::unicode::Movable(diagram).render()
            << "\n";
    }

    return 1;
}

}