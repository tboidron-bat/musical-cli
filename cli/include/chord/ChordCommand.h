#pragma once

#include <Command.h>
#include <vector>
#include <string>
#include <optional>

namespace musical::core::chord
{
    class Chord;
}

namespace cli
{
    struct globalconfig_t;
}

namespace cli::chord
{

class ChordCommand : public cli::Command
{
public:
    const std::vector<cli::option_t>& options() const override;

    int run(int argc, char** argv) override;

private:
    int handle_random() const;

    int handle_symbol(const std::string& symbol,
                      const cli::globalconfig_t& global) const;

    std::optional<musical::core::chord::Chord>
    parse_chord(const std::string& symbol) const;

    int show_diagrams(const musical::core::chord::Chord& chord) const;

    void play_chord(const musical::core::chord::Chord& chord,
                    double strum_delay_ms,
                    bool downstroke) const;
};

}