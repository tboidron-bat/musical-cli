#pragma once

#include <Command.h>
#include <vector>
#include <string>
#include <optional>

namespace musical::core::chord
{
    class Chord;
}

namespace cli::chord
{

enum class OptionId : uint8_t
{
    HELP       = 1 << 0,
    DIAGRAM    = 1 << 1,
    RANDOM     = 1 << 2,
    PLAY       = 1 << 3,
    DIFFICULTY = 1 << 4,
    TUNING     = 1 << 5,
    DUMP_DB    = 1 << 6
};

class ChordCommand : public cli::Command
{
public:
    ChordCommand();

    std::string get_name() const override;  
    std::string get_description() const override;
    std::string get_usage() const override;    
    std::string get_help() const override;

    int run(int argc, char** argv) override;

private:
    OptionId _options_bitmask = static_cast<OptionId>(0);

    cli::command::option* find_option(OptionId id)
    {
        for(auto& opt : _options)
            if(opt.id() == static_cast<uint8_t>(id))
                return &opt;

        return nullptr;
    }    

    void set_option(OptionId opt)
    {
        _options_bitmask =
            static_cast<OptionId>(
                static_cast<uint8_t>(_options_bitmask) |
                static_cast<uint8_t>(opt));
    }

    bool has_option(OptionId opt) const
    {
        return static_cast<uint8_t>(_options_bitmask) &
            static_cast<uint8_t>(opt);
    }    

    int handle_option_random() const;

    int handle_option_show_diagrams(
        const musical::core::chord::Chord& chord);

    int handle_option_dump_database() const;

    void handle_option_play(const musical::core::chord::Chord& chord);

    std::optional<musical::core::chord::Chord>
    parse_chord(const std::string& symbol) const;

};

inline OptionId operator|(OptionId a, OptionId b)
{
    return static_cast<OptionId>(
        static_cast<uint8_t>(a) |
        static_cast<uint8_t>(b)
    );
}

inline OptionId& operator|=(OptionId& a, OptionId b)
{
    a = a | b;
    return a;
}

inline bool operator&(OptionId a, OptionId b)
{
    return (static_cast<uint8_t>(a) &
            static_cast<uint8_t>(b)) != 0;
}
}