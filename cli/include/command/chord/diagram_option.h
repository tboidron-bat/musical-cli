#pragma once

#include <vector>
#include <optional>

#include <Option.h>

#include <musical/chord_db/Diagram.h>

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

        std::vector<::chord::db::Diagram>
            fetch_diagrams(
                const musical::core::chord::Chord&,
                DiagramSource,
                std::optional<::chord::db::Diagram::CAGED> caged = std::nullopt) const;                                

        void render(
            const std::vector<::chord::db::Diagram>& diagrams,
            const musical::core::chord::Chord& chord,
            DiagramSource source) const;
    };

}