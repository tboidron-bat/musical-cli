#include <command/chord/diagram_renderer.h>
#include <command/chord/diagram_layout.h>

#include <musical/io/core/chord/ChordIO.h>
#include <musical/io/core/chord/out/naming.h>
#include <musical/io/chord_db/unicode/DiagramRenderer.h>

#include <sstream>
#include <iostream>
#include <algorithm>

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

void render_diagrams(
    const std::vector<cli::chord::ChordCommand::diagram_entry_t>& entries)
{
    if(entries.empty())
    {
        std::cerr << "No diagrams to display\n";
        return;
    }
    cli::chord::Layout layout(terminal::get_width());


    std::vector<const cli::chord::ChordCommand::diagram_entry_t*> sorted;

    for(const auto& d : entries)
        sorted.push_back(&d);


    //sort per frette order.
    std::sort(sorted.begin(), sorted.end(),
        [](const auto* a, const auto* b)
        {
            return a->_diagram.base_case() < b->_diagram.base_case();
        });


    for(const auto *d : sorted)
    {
        //std::string name = make_name(*d._root, d._intervals_mask);

        layout.add_block(
            io::chord::db::unicode::DiagramRenderer::render(d->_diagram /*, name*/)
            );
    }    
    std::cout << layout.render() << "\n";
}

} // namespace cli::command::chord