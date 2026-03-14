#include <command/chord/dumpdb_option.h>
#include <command/chord/diagram_layout.h>
#include <terminal.h>

#include <musical/io/guitar/stream.h>

#include <musical/guitar_chord_database/db_open_queries.h>
#include <musical/guitar_chord_database/db_movable_queries.h>
#include <musical/io/guitar/unicode/OpenDiagram.h>
#include <musical/io/guitar/unicode/MovableDiagram.h>

#include <iostream>


namespace cli::chord
{
dumpdb_option::dumpdb_option(cli::Command&cmd)
:
Option(cmd,"dump-db","","Dump all chord diagrams stored in the database")
{    

}
int dumpdb_option::dump_open_diagrams(int width) const
{
    std::cout << "dump [Open chord database] \n\n";

    const auto open_diagrams =
        ::chord::database::queries::open::find_all_diagrams();

    Layout layout(cli::terminal::get_width());        
	
    for (const auto& diagram : open_diagrams)
    {
        layout.add_block(
            io::guitar::unicode::OpenDiagram(diagram).render());
    }

    std::cout << layout.render();

    return EXIT_SUCCESS;
}
int dumpdb_option::dump_movable_diagrams(int width) const
{
    std::cout << "\n dump [Movable shape database]\n\n";

    std::vector<std::string> blocks;

    for (int s = 0; s < 5; ++s)
    {
        auto shape =
            static_cast<::chord::database::OpenChordDiagram::CAGEDShape>(s);

        const auto movable_diagrams =
            ::chord::database::queries::movable::find_all_positions(shape);

        for (const auto& diagram : movable_diagrams)
        {
            blocks.push_back(
                io::guitar::unicode::MovableDiagram(diagram).render()
            );
        }
    }

    Layout layout(terminal::get_width());

    for(const auto& b : blocks)
        layout.add_block(b);

    std::cout << layout.render();



    return EXIT_SUCCESS;
}
int dumpdb_option::execute() const
{
    if(!_enabled)
        return 0;

    auto width = cli::terminal::get_width();    

    dump_open_diagrams(width);
    dump_movable_diagrams(width);    

    return EXIT_SUCCESS;
}

}