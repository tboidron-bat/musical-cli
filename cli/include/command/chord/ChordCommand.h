#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <Command.h>
#include <musical/core/chord/Chord.h>
#include <musical/chord_db/Diagram.h>

namespace cli::chord
{
class ChordCommand : public cli::Command
{
public:
    ChordCommand();
    int run(int argc, char** argv) override;

private:
    std::vector<std::string> _args;
private:
    //std::vector<musical::core::chord::Chord> _chords;    
    
    //utiliser par les differentes options 
    struct diagram_entry_t
    {
        musical::core::Tone _root;
        uint64_t _intervals_mask;
        ::chord::db::Diagram _diagram;
    };

    std::vector<diagram_entry_t> _entries;        

private:
    //nettoie la ligne de commande de tous ce qui ne st pas un accords
    //et renvoie la chainde de carartere correspondante
    std::string chords_names_from_input() const;
public:
    std::vector<musical::core::chord::Chord> 
        parse_chord();

    std::vector<diagram_entry_t>& entries()
    {
        return _entries;
    }

    const std::vector<diagram_entry_t>& entries() const
    {
        return _entries;
    }
public:    
    void render() const;
public:    
    void print_name() const override; 
    void print_usage() const override;
    void print_help() const override;
};
}
