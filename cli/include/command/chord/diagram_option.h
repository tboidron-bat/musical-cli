#pragma once

#include <vector>

#include <Option.h>

#include <musical/guitar_chord_database/OpenChordDiagram.h>
#include <musical/guitar_chord_database/MovableShapeDiagram.h>
#include <musical/guitar_chord_database/SixStringsDiagram.h>
#include <musical/Core/chord/Chord.h>

namespace cli::chord
{
    class diagram_option : public command::Option
    {
    public:
        diagram_option(cli::Command&);

        int execute() const override;

    private:
        void find_caged(
            const musical::core::chord::Chord&,
            ::chord::database::SixStringDiagram::CAGEDShape) const;

        void find_all(
            const musical::core::chord::Chord&) const;

        void render(const std::vector<::chord::database::OpenChordDiagram>&) const;
        void render(
            const musical::core::chord::Chord& chord,
            const std::vector<::chord::database::MovableShapeDiagram>&) const;         
    };

}