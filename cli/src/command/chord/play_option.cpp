#include <command/chord/play_option.h>
#include <command/chord/ChordCommand.h>

#include <musical/audio/karplus_strong/chord_player.h>
#include <musical/audio/alsa_test.h>
#include <musical/core/chord/Chord.h>
#include <musical/core/chord/ChordFactory.h>

#include <iostream>

namespace cli::chord
{

play_option::play_option(cli::Command& cmd)
:
command::Option(
    cmd,
    "play",
    "",
    "Play the chord using Karplus-Strong guitar synthesis")
{    
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "delay",
        "<delay_ms>",
        command::option::parameter_t::Requirement::OPTIONAL
    });

    add_parameter({
        cli::command::option::parameter_t::Type::BOOL,
        "downstroke",
        "<downstroke>",
        command::option::parameter_t::Requirement::OPTIONAL
    });
}

// ============================================================
// EXECUTE
// ============================================================
int play_option::execute() const
{
    if(!_enabled)
        return EXIT_FAILURE;

    std::cout << "Playing chord...\n";

    musical::audio::alsa_test();
    return EXIT_SUCCESS;        

    double strum_delay_ms = 0.0;
    bool downstroke = true;

    // delay
    if(parameter(0)._provided)
        strum_delay_ms = std::stod(parameter(0)._value);

    // direction
    if(parameter(1)._provided)
        downstroke = (parameter(1)._value == "true");

    auto& cmd = static_cast<ChordCommand&>(_command_ref);

    if(cmd.entries().empty())
    {
        std::cerr << "No chord to play\n";
        return EXIT_FAILURE;
    }

    using musical::core::chord::Chord;
    using musical::core::chord::ChordType;
    using musical::audio::karplus_strong::ChordPlayer;

    for(const auto& e : cmd.entries())
    {
        // reconstruction propre
        using musical::core::Pitch;
        using musical::core::chord::ChordFactory;

        if(!e._root)
        {
            std::cerr << "Cannot play diagram without root note\n";
            continue;
        }

        auto tone = *e._root;

        auto chord = ChordFactory::create(
            Pitch(static_cast<uint8_t>(tone)),
            e._intervals_mask
        );
                
        ChordPlayer::play(
            chord,
            strum_delay_ms,
            downstroke
        );
    }

    return EXIT_SUCCESS;
}

} // namespace cli::chord