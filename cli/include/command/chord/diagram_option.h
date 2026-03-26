#pragma once

#include <vector>

#include <Option.h>

#include <musical/guitar_chord_database/Diagram.h>

namespace musical::core::chord
{
    class Chord;
}
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
            ::chord::database::Diagram::CAGED) const;

        void find_all(
            const musical::core::chord::Chord&) const;

        void render(const std::vector<::chord::database::Diagram>&) const;
        void render(
            const musical::core::chord::Chord& chord,
            const std::vector<::chord::database::Diagram>&) const;         
    };

}