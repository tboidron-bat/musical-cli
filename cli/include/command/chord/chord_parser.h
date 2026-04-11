#pragma once

#include <command/chord/ChordCommand.h>

namespace cli::command::chord
{
class chord_parser 
{
private:
    //nettoie la ligne de commande de tous ce qui ne st pas un accords
    //et renvoie la chainde de carartere correspondante
    static std::string from_input(const cli::chord::ChordCommand&);

public:
    static void add_entries(cli::chord::ChordCommand& cmd);

// private:
//     enum class DiagramSource
//     {
//         Open,
//         Movable
//     };
//     void add_diagrams(
//         ChordCommand&,
//         const musical::core::chord::Chord&,
//         DiagramSource,
//         std::optional<::chord::db::Diagram::CAGED>) const;
//     };

};

}