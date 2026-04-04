#include <command/chord/dumpdb_option.h>
#include <command/chord/diagram_layout.h>
#include <terminal.h>

#include <musical/chord_db/open/queries.h>
#include <musical/chord_db/movable/queries.h>
#include <musical/io/chord_db/unicode/DiagramRenderer.h>

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
    std::cout << "dump-db [Open chord database] \n\n";

    const auto open_diagrams =
        ::chord::db::queries::open::find_all_diagrams();

    Layout layout(cli::terminal::get_width());        
	
    for (const auto& diagram : open_diagrams)
    {
        layout.add_block(
            io::chord::db::unicode::DiagramRenderer::render(diagram));
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
            static_cast<::chord::db::Diagram::CAGED>(s);

        const auto movable_diagrams =
            ::chord::db::queries::movable::find_all_diagrams(shape);

        for (const auto& diagram : movable_diagrams)
        {
            blocks.push_back(
                io::chord::db::unicode::DiagramRenderer::render(diagram)
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