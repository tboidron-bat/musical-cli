#include <command/chord/random_option.h>
#include <command/chord/ChordCommand.h>

#include <musical/chord_db/open/queries.h>
#include <musical/chord_db/movable/queries.h>

#include <musical/core/Pitch.h>

#include <random>
#include <iostream>

namespace cli::chord
{

random_option::random_option(cli::Command& cmd)
:
command::Option(cmd,"random","r","Show a completely random chord")
{    
    add_parameter({
        cli::command::option::parameter_t::Type::INT,
        "value",
        "If provided, generate <value> random chords",
        command::option::parameter_t::Requirement::OPTIONAL
    });
}

// ============================================================
// OPEN
// ============================================================
void random_option::add_open_diagram() const
{
    auto& cmd = static_cast<ChordCommand&>(_command_ref);                          

    // ⚠️ ici tu récupères seulement le diagram → il faut aussi root + mask
    const auto& db = ::chord::db::data_open();

    static std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<size_t> chord_dist(0, db.size() - 1);
    auto chord_it = std::next(db.begin(), chord_dist(gen));

    const auto& key = chord_it->first;
    const auto& diagrams = chord_it->second;

    std::uniform_int_distribution<size_t> diag_dist(0, diagrams.size() - 1);
    const auto& diagram = diagrams[diag_dist(gen)];

    cmd.entries().push_back({
        key._root,   // Tone
        key._mask,  // IntervalMask
        diagram
    });
}

// ============================================================
// MOVABLE
// ============================================================
void random_option::add_movable_diagram() const
{
    auto& cmd = static_cast<ChordCommand&>(_command_ref);      

    auto [mask, diagram] =
        ::chord::db::queries::movable::get_random_diagram();

    static std::mt19937 gen(std::random_device{}());        
    std::uniform_int_distribution<int> pitch_dist(0, 11);

    musical::core::Pitch root(pitch_dist(gen));

    diagram.place_root(static_cast<uint8_t>(root.tone()));    

    cmd.entries().push_back({
        root.tone(),
        mask,
        diagram
    });
}

// ============================================================
// EXECUTE
// ============================================================
int random_option::execute() const
{
    if(!_enabled)
        return 0;

    auto& cmd = static_cast<ChordCommand&>(_command_ref);    
    
    cmd.entries().clear();                

    int count = 1;        

    if(parameter(0)._provided)
        count = std::stoi(parameter(0)._value);

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);
    
    while(count)
    {
        const bool choose_open = dist(gen) == 0;

        if(choose_open)
            add_open_diagram();
        else
            add_movable_diagram();

        --count;
    }      

    return EXIT_SUCCESS;
}

} // namespace cli::chord