#include <command/chord/play_option.h>
#include <command/chord/ChordCommand.h>

#include <musical/audio/karplus_strong/chord_player.h>
#include <musical/io/chord/output/stream.h>

#include <iostream>


namespace cli::chord
{
play_option::play_option(cli::Command*cmd)
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

        //  "Examples:\n"
        //  "  --play\n"
        //  "  --play 15\n"
        //  "  --play 20 false\n",
        //     "--play",
        //     "",
        //     "Play the chord using Karplus-Strong guitar synthesis.\n"
        //     "Usage:\n"
        //     "  --play                 (simultaneous attack)\n"
        //     "  --play <delay_ms>\n"
        //     "  --play <delay_ms> <downstroke>\n"
        //     "\n"
}
int play_option::execute() const
{
    if(!_enabled)
        return 0;

    double strum_delay_ms = 0.0;
    bool downstroke = true;

    //DELAY
    if(get_parameter(0)._provided)
    {
        strum_delay_ms = std::stoi(get_parameter(0)._value);

    }
    //DOWNSTROKE
    if(get_parameter(1)._provided)
    {
        downstroke = get_parameter(1)._value == "true";
    }


    const ChordCommand* cmd =
        static_cast<const ChordCommand*>(_command);

    if(!cmd->chord())
    {
        std::cerr << "Chord required\n";
        return 1;
    }

    const auto& chord = *cmd->chord();

    musical::audio::karplus_strong::ChordPlayer::play(
        chord,
        strum_delay_ms,
        downstroke
    );

    return 1;
}
}

