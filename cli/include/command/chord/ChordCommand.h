#pragma once

#include <Command.h>
#include <vector>
#include <string>
#include <iostream>

#include <musical/core/chord/Chord.h>

namespace cli::chord
{
class ChordCommand : public cli::Command
{
public:
    ChordCommand();
    int run(int argc, char** argv) override;

private:
    std::vector<musical::core::chord::Chord> _chords;    

private:
    //nettoie la ligne de commande de tous ce qui ne st pas un accords
    //et renvoie la chainde de carartere correspondante
    std::string clean(int argc, char**argv);
public:
    int parse_chord(int, char**);

    std::vector<musical::core::chord::Chord>& chords()
    {
        return _chords;
    }
    const std::vector<musical::core::chord::Chord>& chords() const
    {
        return _chords;
    }

public:    
    void print_name() const override; 
    void print_usage() const override;
    void print_help() const override;
};
}
