#include <musical/guitar_chord_database/Diagram.h>

#include <stdexcept>

namespace chord::database
{
uint8_t Diagram::root_note() const
{
    static constexpr uint8_t tuning[6] =
    {
        4, 9, 2, 7, 11, 4
    };

    auto idx = static_cast<uint8_t>(_root_string);

    uint8_t state = _strings[idx];

    if (state == MUTE || state == UNUSED)
    {
        throw std::logic_error(
            "Diagram::root_note(): root string is muted or unused"
        );
    }

    return (tuning[idx] + state + _base_case) % 12;
}
std::size_t Diagram::first_case() const 
{ 
    uint8_t min=0xff;

    for(const auto& s : _strings)   
    {
        if (s == MUTE || s == UNUSED || s == 0)
            continue;
        min = ( s < min ) ? s : min;    
    }

    return (min == 0xFF) ? 0 : min;
};   
std::size_t Diagram::last_case() const 
{ 
    uint8_t max=0;

    for(const auto& s : _strings)   
    {
        if (s == MUTE || s == UNUSED || s == 0)
            continue;
        max = ( s > max ) ? s : max;    
    }

    return max;
};   

std::size_t Diagram::nb_case() const 
{ 
    auto first = first_case();
    auto last  = last_case();

    if (last == 0)
        return 1;

    return last - first + 1;
}

void Diagram::place_root(uint8_t target)
{
    if (target >= 24)
        throw std::invalid_argument("Invalid case for guitar diagram");

    uint8_t current = root_note();

    uint8_t delta = (target + 12 - current) % 12;

    _base_case += delta;
}
bool Diagram::is_open() const 
{
    if(_base_case != 0)
        return false;

    for(auto v : _strings)
    {
        if(v == 0)
            return true;
    }

    return false;
}

}