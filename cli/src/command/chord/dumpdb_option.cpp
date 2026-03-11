#include <command/chord/dumpdb_option.h>
#include <command/chord/diagram_layout.h>
#include <terminal.h>

#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/io/guitar/stream.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/guitar/stream_diagram.h>
//#include <musical/io/guitar/stream_diagram2.h>
#include <musical/io/guitar/diagram/unicode/Movable.h>

#include <iostream>


namespace cli::chord
{
dumpdb_option::dumpdb_option(cli::Command*cmd)
:
Option(cmd,"dump-db","","Dump all chord diagrams stored in the database")
{    

}
int dumpdb_option::execute() const
{
    if(!_enabled)
        return 0;

    using namespace musical::instruments::guitar::six_strings;

    auto width = cli::terminal::get_width();    

    std::cout
        << "[Open chord database]\n\n";

    std::vector<std::string> blocks;

    for (int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<OpenChordDiagram::CAGEDShape>(s);

        const auto open_diagrams =
            db_open_queries::find_all_positions(shape);

	
        std::cout << ">> Shape " << shape << ": " << std::endl;
        //std::cout << std::string(width, '_') << std::endl;        

        for (const auto& diagram : open_diagrams)
        {
            std::ostringstream oss;
            oss << diagram;
            blocks.push_back(oss.str());
        }

        std::cout << layout_blocks(blocks, width);
        std::cout << std::string(width, '_') << std::endl;        
        std::cout << std::endl;

        blocks.clear();
    }


    std::cout
        << "\nMovable shape database\n\n";


    blocks.clear();
    for (int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<OpenChordDiagram::CAGEDShape>(s);

        const auto movable_diagrams =
            db_movable_queries::find_all_positions(shape);

        for (const auto& diagram : movable_diagrams)
        {
            blocks.push_back(
                //io::guitar::six_strings::movable_shape_diagram_to_ascii(diagram)
                io::guitar::diagram::unicode::Movable(diagram).render()
            );
        }
    }
    std::cout
        << layout_blocks(blocks, width);


    return 1;

}

}