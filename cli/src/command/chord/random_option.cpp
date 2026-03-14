#include <command/chord/random_option.h>
#include <command/chord/ChordCommand.h>
#include <command/chord/diagram_layout.h>
#include <terminal.h>

#include <musical/guitar_chord_database/db_open_queries.h>
#include <musical/guitar_chord_database/db_movable_queries.h>
//#include <musical/io/guitar/ascii/stream_diagram.h>
//#include <musical/io/guitar/stream_diagram2.h>
#include <musical/io/guitar/unicode/MovableDiagram.h>
#include <musical/io/guitar/unicode/OpenDiagram.h>

#include <random>
#include <iostream>

#include <musical/io/chord/output/stream.h> //DEBUG

namespace cli::chord
{
random_option::random_option(cli::Command&cmd)
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

    int count = 1;        

    if(parameter(0)._provided)
        count = std::stoi(parameter(0)._value);

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    auto& cmd = static_cast<ChordCommand&>(_command_ref);      
    
    std::vector<std::string> blocks;       
    
    while(count)
    {
        const bool choose_open = dist(gen) == 0;

        if(choose_open)
        {
            auto [type, diagram] =            
                ::chord::database::queries::open::get_random_diagram();

            cmd.chords().emplace_back(diagram.root_pitch(),
                                        type);    
                                        
            blocks.push_back(io::guitar::unicode::OpenDiagram(diagram).render());
                                        
        }
        else
        {
            auto [type, diagram] =            
                ::chord::database::queries::movable::get_random_diagram();

            std::uniform_int_distribution<int> pitch_dist(0, 11);

            musical::core::pitch_t root =
                musical::core::pitch_from_chromatic_index(pitch_dist(gen));

            cmd.chords().emplace_back(root,type);

            blocks.push_back(
                io::guitar::unicode::MovableDiagram(diagram).render());

        }        
        count--;
    }      

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();    

    return EXIT_SUCCESS;
}

}