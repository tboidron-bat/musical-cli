#include <command/chord/dumpdb_renderer.h>
#include <command/chord/diagram_layout.h>

#include <musical/io/core/chord/ChordIO.h>
#include <musical/io/core/chord/out/naming.h>
#include <musical/io/chord_db/unicode/DiagramRenderer.h>

#include <sstream>

namespace cli::command::chord
{
static std::string make_name(
    musical::core::Tone tone,
    uint64_t mask)
{
    std::ostringstream oss;

    oss << tone;

    musical::core::chord::ChordType type(mask);

    return oss.str() + musical::io::chord::to_string(type);
}
void render_dumpdb(const std::vector<cli::chord::ChordCommand::diagram_entry_t>& entries)
{
    if(entries.empty())
    {
        std::cerr << "No diagrams to display\n";
        return;
    }

    std::vector<const cli::chord::ChordCommand::diagram_entry_t*> open;
    std::vector<const cli::chord::ChordCommand::diagram_entry_t*> movable;

    for(const auto& d : entries)
    {
        if(d._root)
            open.push_back(&d);
        else
            movable.push_back(&d);
    }

    // =========================
    // OPEN
    // =========================
    if(!open.empty())
    {
        std::cout << "\n=== Open diagrams ===\n\n";

        cli::chord::Layout layout(terminal::get_width());

        for(const auto* d : open)
        {
            std::string name = make_name(*d->_root, d->_intervals_mask);

            layout.add_block(
                io::chord::db::unicode::DiagramRenderer::render(d->_diagram, name)
            );
        }

        std::cout << layout.render() << "\n";
    }

    // =========================
    // MOVABLE
    // =========================
    if(!movable.empty())
    {
        std::cout << "\n=== Movable diagrams ===\n\n";

        cli::chord::Layout layout(terminal::get_width());

        for(const auto* d : movable)
        {
            std::string name =
                musical::io::chord::to_string(
                    musical::core::chord::ChordType(d->_intervals_mask)
                );

            layout.add_block(
                io::chord::db::unicode::DiagramRenderer::render(d->_diagram, name)
            );
        }

        std::cout << layout.render();
    }
}
}