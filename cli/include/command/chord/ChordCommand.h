#pragma once

#include <Command.h>
#include <vector>
#include <string>
#include <optional>
#include <iostream>

#include <musical/Core/chord/Chord.h>

namespace cli::chord
{
class ChordCommand : public cli::Command
{
    enum OptionId
    {
        VERSION=0,
        HELP,
        DUMPDB,        
        RANDOM,
        DIAGRAM,
        PLAY,
        DIFFICULTY,
        TUNING
    };
public:
    ChordCommand();
    int run(int argc, char** argv) override;

private:
    std::optional<musical::core::chord::Chord> _chord;

public:
    std::optional<musical::core::chord::Chord>
    parse_chord(const std::string& symbol);

    const std::optional<musical::core::chord::Chord>& chord() const
    {
        return _chord;
    }    

public:    
    void print_name() const override; 
    void print_usage() const override;
    void print_help() const override;
};
}
