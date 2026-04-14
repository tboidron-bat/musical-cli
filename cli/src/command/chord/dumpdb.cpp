#include <command/chord/dumpdb.h>

#include <musical/core/Tone.h>
#include <musical/chord_db/Diagram.h>
#include <musical/chord_db/open/queries.h>
#include <musical/chord_db/movable/queries.h>

#include <command/chord/dumpdb_renderer.h>

namespace cli::command::chord
{
dumpdb::dumpdb(cli::Command&cmd)
:
cli::command::Option(
    cmd,
    "dump-db",
    "",
    "Dump all chord diagrams stored in the database")
{    
    //TODO
    // add_parameter({
    //     cli::command::option::parameter_t::Type::STRING,
    //     "source",
    //     "Limit diagrams to a specific source (open, movable)",
    //     command::option::parameter_t::Requirement::OPTIONAL,
    //     { "open", "movable" }
    // });    
}
void dumpdb::add_all_diagrams(cli::chord::ChordCommand& cmd) const
{
    auto open = ::chord::db::queries::open::find_all_diagrams();

    for (const auto& [mask, d] : open)
    {
        auto t = static_cast<musical::core::Tone>(d.root_note());

        cmd.entries().push_back(
            cli::chord::ChordCommand::ChordCommand::diagram_entry_t{ t, mask, d });
    }

    auto movable = ::chord::db::queries::movable::find_all_diagrams();

    for (const auto& [mask, d] : movable)
    {
        cmd.entries().push_back(
            cli::chord::ChordCommand::ChordCommand::diagram_entry_t{ std::nullopt, mask, d });
    }
}   
int dumpdb::execute() const
{
    if(!_enabled)
        return EXIT_FAILURE;

    auto& cmd = static_cast<cli::chord::ChordCommand&>(_command_ref);

    cmd.entries().clear();

    add_all_diagrams(cmd);

    cli::command::chord::render_dumpdb(cmd.entries());    

    return EXIT_SUCCESS;
}

}