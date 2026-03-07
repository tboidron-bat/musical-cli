#include <chord/play_option.h>
#include <chord/ChordCommand.h>

#include <musical/audio/karplus_strong/chord_player.h>
#include <musical/io/chord/output/stream.h>

#include <iostream>


namespace cli::chord
{
play_option::play_option(cli::Command*cmd)
:
option(
    cmd,
    "play",
    "",
    "Play the chord using Karplus-Strong guitar synthesis")
{    
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "delay",
        "<delay_ms>"
        });

    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "downstroke",
        "<downstroke>"
        });

        //  "Usage:\n"
        //  "  --play                 (simultaneous attack)\n"
        //  "  --play <delay_ms> <downstroke>\n"
        //  "\n"
        //  "Examples:\n"
        //  "  --play\n"
        //  "  --play 15\n"
        //  "  --play 20 false\n",


}
int play_option::execute() const
{
    double strum_delay_ms = 0.0;
    bool downstroke = true;

    if(has_parameter("delay"))
        strum_delay_ms = parameter_value_int("delay");

    if(has_parameter("downstroke"))
        downstroke = parameter_value_string("downstroke") == "true";
        
    const ChordCommand* cmd =
        static_cast<const ChordCommand*>(_command);

    if(!cmd->chord())
    {
        std::cerr << "Chord required\n";
        return 1;
    }

    const auto& chord = *cmd->chord();

    std::cout << "Playing chord: " << chord << "\n";

    musical::audio::karplus_strong::ChordPlayer::play(
        chord,
        strum_delay_ms,
        downstroke
    );

    return 0;
}
}

        //     "--play",
        //     "",
        //     "Play the chord using Karplus-Strong guitar synthesis.\n"
        //     "Usage:\n"
        //     "  --play                 (simultaneous attack)\n"
        //     "  --play <delay_ms>\n"
        //     "  --play <delay_ms> <downstroke>\n"
        //     "\n"
        //     "Examples:\n"
        //     "  --play\n"
        //     "  --play 15\n"
        //     "  --play 20 false\n",
        //     true,   // accepte des valeurs (0 à 2)
        //     true,   // valeurs optionnelles
        //     2,
        //     {}
