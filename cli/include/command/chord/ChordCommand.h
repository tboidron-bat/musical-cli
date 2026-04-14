#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <optional>

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

    struct diagram_entry_t
    {
        //la commande dump_db ne va placer _root pour les diagrames movables?
        std::optional<musical::core::Tone>  _root;
        uint64_t _intervals_mask;
        ::chord::db::Diagram _diagram;
    };


private:
    std::vector<std::string> _args;
private:

    std::vector<diagram_entry_t> _entries;        

public:
    std::vector<diagram_entry_t>& entries() { return _entries;}

    const std::vector<diagram_entry_t>& entries() const { return _entries; }
public:
    std::string input_string() const;
public:    
    void print_name() const override; 
    void print_usage() const override;
    void print_help() const override;
};
}
