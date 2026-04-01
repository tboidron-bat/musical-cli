#pragma once

#include <vector>
#include <optional>

#include <Option.h>

#include <musical/guitar_chord_database/Diagram.h>

namespace musical::core
{
    enum class Tone : uint8_t;
}
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
        enum class DiagramSource
        {
            Open,
            Movable
        };

        std::vector<::chord::database::Diagram>
            fetch_diagrams(
                const musical::core::chord::Chord&,
                DiagramSource,
                std::optional<::chord::database::Diagram::CAGED> caged = std::nullopt) const;                                

        void render(
            const std::vector<::chord::database::Diagram>& diagrams,
            const musical::core::chord::Chord& chord,
            DiagramSource source) const;
    };

}