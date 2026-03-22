#include <musical/Core/pitch_t.h>

namespace musical::core
{

static int normalize(int v)
{
    return ((v % 12) + 12) % 12;
}
static int base_index(NoteName n)
{
    switch (n)
    {
        case NoteName::C: return 0;
        case NoteName::D: return 2;
        case NoteName::E: return 4;
        case NoteName::F: return 5;
        case NoteName::G: return 7;
        case NoteName::A: return 9;
        case NoteName::B: return 11;
    }
    return 0;
}

static int accidental_offset(Accidental a)
{
    switch (a)
    {
        case Accidental::NONE:         return 0;
        case Accidental::SHARP:        return 1;
        case Accidental::FLAT:         return -1;
        case Accidental::DOUBLE_SHARP: return 2;
        case Accidental::DOUBLE_FLAT:  return -2;
    }
    return 0;
}

std::size_t chromatic_index(const pitch_t& p) noexcept
{
    return (base_index(p._name) + accidental_offset(p._accidental)) % 12;
}

bool pitch_t::operator<(const pitch_t& other) const noexcept
{
    if (_octave != other._octave)
        return _octave < other._octave;

    return chromatic_index(*this) < chromatic_index(other);
}
bool pitch_t::operator==(const pitch_t& other) const noexcept
{
    return _octave == other._octave
        && chromatic_index(*this) == chromatic_index(other);
}

pitch_t& pitch_t::operator+=(uint8_t semitones)
{
    int chroma = static_cast<int>(chromatic_index(*this));

    // index absolu incluant octave
    int absolute = _octave * 12 + chroma + semitones;

    int new_octave = absolute / 12;
    int mod = absolute % 12;

    pitch_t rebuilt = pitch_from_chromatic_index(mod, true);

    _name = rebuilt._name;
    _accidental = rebuilt._accidental;
    _octave = new_octave;

    return *this;
}

// ------------------------------------------------------------
// Chromatic index → pitch_t
// ------------------------------------------------------------
pitch_t pitch_from_chromatic_index(
    int index,
    bool with_sharp
    )
{
    index = normalize(index);

    using NN = NoteName;
    using AC = Accidental;

    if (with_sharp)
    {
        switch (index)
        {
            case 0:  return { NN::C, AC::NONE, 0 };
            case 1:  return { NN::C, AC::SHARP, 0 };
            case 2:  return { NN::D, AC::NONE, 0 };
            case 3:  return { NN::D, AC::SHARP, 0 };
            case 4:  return { NN::E, AC::NONE, 0 };
            case 5:  return { NN::F, AC::NONE, 0 };
            case 6:  return { NN::F, AC::SHARP, 0 };
            case 7:  return { NN::G, AC::NONE, 0 };
            case 8:  return { NN::G, AC::SHARP, 0 };
            case 9:  return { NN::A, AC::NONE, 0 };
            case 10: return { NN::A, AC::SHARP, 0 };
            case 11: return { NN::B, AC::NONE, 0 };
        }
    }
    else
    {
        switch (index)
        {
            case 0:  return { NN::C, AC::NONE, 0 };
            case 1:  return { NN::D, AC::FLAT, 0 };
            case 2:  return { NN::D, AC::NONE, 0 };
            case 3:  return { NN::E, AC::FLAT, 0 };
            case 4:  return { NN::E, AC::NONE, 0 };
            case 5:  return { NN::F, AC::NONE, 0 };
            case 6:  return { NN::G, AC::FLAT, 0 };
            case 7:  return { NN::G, AC::NONE, 0 };
            case 8:  return { NN::A, AC::FLAT, 0 };
            case 9:  return { NN::A, AC::NONE, 0 };
            case 10: return { NN::B, AC::FLAT, 0 };
            case 11: return { NN::B, AC::NONE, 0 };
        }
    }

    // impossible normalement
    return { NN::C, AC::NONE, 0 };
}

} // namespace musical::core