#include <musical/guitar_chord_database/MovableShapeDiagram.h>
#include <stdexcept>

namespace chord::database
{
std::size_t MovableShapeDiagram::first_fret() const
{
    uint8_t min_offset = 255;
    bool has_fretted = false;

    for (const auto& s : _strings)
    {
        if (s.state() == string_state::State::FRETTED_OFFSET)
        {
            has_fretted = true;
            min_offset = std::min(min_offset, s.offset());
        }
    }

    if (!has_fretted)
        return _base_fret;

    return static_cast<std::size_t>(_base_fret + min_offset);
}
std::size_t MovableShapeDiagram::nb_frets() const
{
    uint8_t max_offset = 0;

    for (const auto& s : _strings)
    {
        if (s.state() == string_state::State::FRETTED_OFFSET)
            max_offset = std::max(max_offset, s.offset());
    }

    return max_offset + 1;    
}

bool MovableShapeDiagram::has_barre() const
{
    for (std::size_t i = 0; i < STRING_COUNT; ++i)
    {
        const auto& a = _strings[i];

        if (a.state() != string_state::State::FRETTED_OFFSET)
            continue;

        int count = 1;

        for (std::size_t j = i + 1; j < STRING_COUNT; ++j)
        {
            const auto& b = _strings[j];

            if (b.state() == string_state::State::FRETTED_OFFSET &&
                b.offset() == a.offset() &&
                b.finger() == a.finger())
            {
                count++;
            }
        }

        if (count >= 2)
            return true;
    }

    return false;
}
void MovableShapeDiagram::place_root(
    const musical::core::pitch_t& root)
{
    using musical::core::pitch_t;

    pitch_t open_pitch;

    switch (root_string())
    {
        case GuitarString::LOW_E:
            open_pitch = pitch_t(musical::core::NoteName::E, musical::core::Accidental::NONE);
            break;

        case GuitarString::A:
            open_pitch = pitch_t(musical::core::NoteName::A, musical::core::Accidental::NONE);
            break;
        case GuitarString::D:
            open_pitch = pitch_t(musical::core::NoteName::D, musical::core::Accidental::NONE);
            break;
        case GuitarString::G:
            open_pitch = pitch_t(musical::core::NoteName::G, musical::core::Accidental::NONE);
            break;
        default:
            throw std::runtime_error("Unsupported root string");
    }

    int root_fret =
        chromatic_index(root)- chromatic_index(open_pitch);

    if (root_fret < 0)
        root_fret += 12;

    int root_offset =
        _strings[static_cast<int>(root_string())].offset();        

    int base = root_fret - root_offset;

    _base_fret = base < 0 ? base +12 : base;
}}