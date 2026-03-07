#include <chord/dumpdb_option.h>
#include <chord/diagram_layout.h>
#include <terminal.h>

#include <musical/instruments/guitar/six_strings/db_open_queries.h>
#include <musical/io/instruments/guitar/six_strings/stream.h>
#include <musical/instruments/guitar/six_strings/db_movable_queries.h>
#include <musical/io/instruments/guitar/six_strings/stream_diagram.h>
#include <musical/io/instruments/guitar/six_strings/movable_shape_diagram_to_ascii.h>

#include <iostream>


namespace cli::chord
{
dumpdb_option::dumpdb_option(cli::Command*cmd)
:
option(cmd,"dump-db","","Dump all chord diagrams stored in the database")
{    

}
int dumpdb_option::execute() const
{
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

        std::cout
            << cli::chord::layout_ascii_blocks(blocks, width);
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
                io::guitar::six_strings::movable_shape_diagram_to_ascii(diagram)
            );
        }
    }
    std::cout
        << cli::chord::layout_ascii_blocks(blocks, width);


    return 0;

}

}