#pragma once

#include <string_view>
#include <array>
#include <cstddef>
#include <ostream>
#include <cstdint>

namespace musical::io::chord
{

// -----------------------------------------------------------------------------
// Lexeme
// -----------------------------------------------------------------------------
struct lexeme_t
{
    enum class Category : uint8_t
    {
        TRIAD,
        SEVENTH,
        EXTENSION,
        ALTERATION,
        SUSPENSION,
        ADDITION,
        SPECIAL,
        COUNT // 🔥 utile pour LUT
    };

    std::string_view text;
    Category category;
};

// -----------------------------------------------------------------------------
// TABLEAU BRUT
// -----------------------------------------------------------------------------
constexpr std::array<lexeme_t, 38> ALL_LEXEMES = {
    // TRIADES
    lexeme_t{"major",   lexeme_t::Category::TRIAD},
    lexeme_t{"majeur",  lexeme_t::Category::TRIAD},
    lexeme_t{"maj",     lexeme_t::Category::TRIAD},
    lexeme_t{"minor",   lexeme_t::Category::TRIAD},
    lexeme_t{"mineur",  lexeme_t::Category::TRIAD},
    lexeme_t{"min",     lexeme_t::Category::TRIAD},
    lexeme_t{"m",       lexeme_t::Category::TRIAD},
    lexeme_t{"-",       lexeme_t::Category::TRIAD},
    lexeme_t{"dim",     lexeme_t::Category::TRIAD},
    lexeme_t{"°",       lexeme_t::Category::TRIAD},
    lexeme_t{"aug",     lexeme_t::Category::TRIAD},
    lexeme_t{"+",       lexeme_t::Category::TRIAD},

    // SEVENTH
    lexeme_t{"maj7",    lexeme_t::Category::SEVENTH},
    lexeme_t{"M7",      lexeme_t::Category::SEVENTH},
    lexeme_t{"7M",      lexeme_t::Category::SEVENTH},
    lexeme_t{"Δ7",      lexeme_t::Category::SEVENTH},
    lexeme_t{"Δ",       lexeme_t::Category::SEVENTH},
    lexeme_t{"7",       lexeme_t::Category::SEVENTH},
    lexeme_t{"dim7",    lexeme_t::Category::SEVENTH},

    // EXTENSIONS
    lexeme_t{"maj13",   lexeme_t::Category::EXTENSION},
    lexeme_t{"maj11",   lexeme_t::Category::EXTENSION},
    lexeme_t{"maj9",    lexeme_t::Category::EXTENSION},
    lexeme_t{"13",      lexeme_t::Category::EXTENSION},
    lexeme_t{"11",      lexeme_t::Category::EXTENSION},
    lexeme_t{"9",       lexeme_t::Category::EXTENSION},
    lexeme_t{"6",       lexeme_t::Category::EXTENSION},    

    // ALTERATIONS
    lexeme_t{"alt",     lexeme_t::Category::ALTERATION},
    lexeme_t{"#11",     lexeme_t::Category::ALTERATION},
    lexeme_t{"b13",     lexeme_t::Category::ALTERATION},
    lexeme_t{"b9",      lexeme_t::Category::ALTERATION},
    lexeme_t{"#9",      lexeme_t::Category::ALTERATION},
    lexeme_t{"b5",      lexeme_t::Category::ALTERATION},
    lexeme_t{"#5",      lexeme_t::Category::ALTERATION},

    // SUSPENSIONS
    lexeme_t{"sus2",    lexeme_t::Category::SUSPENSION},
    lexeme_t{"sus4",    lexeme_t::Category::SUSPENSION},

    // ADDITIONS
    lexeme_t{"add11",   lexeme_t::Category::ADDITION},
    lexeme_t{"add9",    lexeme_t::Category::ADDITION},

    // SPECIAL
    lexeme_t{"N.C",     lexeme_t::Category::SPECIAL}
};

// -----------------------------------------------------------------------------
// TRI constexpr
// -----------------------------------------------------------------------------
template <std::size_t N>
constexpr std::array<lexeme_t, N>
sort_by_length_desc(std::array<lexeme_t, N> arr)
{
    for (std::size_t i = 1; i < N; ++i)
    {
        auto key = arr[i];
        std::size_t j = i;

        while (j > 0 && arr[j - 1].text.size() < key.text.size())
        {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = key;
    }

    return arr;
}

// -----------------------------------------------------------------------------
// TABLE TRIÉE
// -----------------------------------------------------------------------------
constexpr auto SORTED_LEXEMES =
    sort_by_length_desc(ALL_LEXEMES);

// -----------------------------------------------------------------------------
// CATEGORY → STRING (table-driven)
// -----------------------------------------------------------------------------
inline constexpr std::array<std::string_view,
    static_cast<size_t>(lexeme_t::Category::COUNT)> CATEGORY_NAMES = {
    "TRIAD",
    "SEVENTH",
    "EXTENSION",
    "ALTERATION",
    "SUSPENSION",
    "ADDITION",
    "SPECIAL"
};

// -----------------------------------------------------------------------------
// STREAM
// -----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, lexeme_t::Category cat)
{
    auto idx = static_cast<size_t>(cat);

    if (idx < CATEGORY_NAMES.size())
        return os << CATEGORY_NAMES[idx];

    return os << "UNKNOWN";
}

} // namespace musical::io::chord