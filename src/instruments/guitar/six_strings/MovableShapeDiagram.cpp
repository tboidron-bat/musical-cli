#include <musical/instruments/guitar/six_strings/MovableShapeDiagram.h>
#include <stdexcept>

namespace musical::instruments::guitar::six_strings
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

            if (s.offset() < min_offset)
                min_offset = s.offset();
        }
    }

    if (!has_fretted)
        return 0;

    return static_cast<std::size_t>(min_offset);
}

std::size_t MovableShapeDiagram::nb_frets() const
{
    uint8_t min_offset = 255;
    uint8_t max_offset = 0;
    bool has_fretted = false;

    for (const auto& s : _strings)
    {
        if (s.state() == string_state::State::FRETTED_OFFSET)
        {
            has_fretted = true;

            auto off = s.offset();

            if (off < min_offset) min_offset = off;
            if (off > max_offset) max_offset = off;
        }
    }

    if (!has_fretted)
        return 0;

    return static_cast<std::size_t>(max_offset - min_offset + 1);
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

}