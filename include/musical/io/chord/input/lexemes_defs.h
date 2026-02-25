#pragma once

#include <string_view>
#include <array>
#include <cstddef>

namespace musical::io::chord
{

// -----------------------------------------------------------------------------
// Catégorie musicale
// -----------------------------------------------------------------------------
enum class LexemeCategory
{
    TRIAD,
    SEVENTH,
    EXTENSION,
    ALTERATION,
    SUSPENSION,
    ADDITION,
    SPECIAL
};

// -----------------------------------------------------------------------------
// Lexeme
// -----------------------------------------------------------------------------
struct Lexeme
{
    std::string_view text;
    LexemeCategory   category;
    bool             case_sensitive;
};

// -----------------------------------------------------------------------------
// TABLEAU BRUT
// -----------------------------------------------------------------------------
constexpr std::array ALL_LEXEMES = {

    // -----------------------------------------------------------------
    // TRIADES
    // -----------------------------------------------------------------
    Lexeme{"major",   LexemeCategory::TRIAD, false},
    Lexeme{"majeur",  LexemeCategory::TRIAD, false},
    Lexeme{"maj",     LexemeCategory::TRIAD, false},

    Lexeme{"minor",   LexemeCategory::TRIAD, false},
    Lexeme{"mineur",  LexemeCategory::TRIAD, false},
    Lexeme{"min",     LexemeCategory::TRIAD, false},

    Lexeme{"m",       LexemeCategory::TRIAD, true},   // IMPORTANT
    Lexeme{"-",       LexemeCategory::TRIAD, true},

    Lexeme{"dim",     LexemeCategory::TRIAD, false},
    Lexeme{"°",       LexemeCategory::TRIAD, true},

    Lexeme{"aug",     LexemeCategory::TRIAD, false},
    Lexeme{"+",       LexemeCategory::TRIAD, true},

    // -----------------------------------------------------------------
    // SEVENTH
    // -----------------------------------------------------------------
    Lexeme{"maj7",    LexemeCategory::SEVENTH, false},
    Lexeme{"M7",      LexemeCategory::SEVENTH, true},  // IMPORTANT
    Lexeme{"7M",      LexemeCategory::SEVENTH, true},
    Lexeme{"Δ7",      LexemeCategory::SEVENTH, true},
    Lexeme{"Δ",       LexemeCategory::SEVENTH, true},

    Lexeme{"7",       LexemeCategory::SEVENTH, true},
    Lexeme{"dim7",    LexemeCategory::SEVENTH, false},

    // -----------------------------------------------------------------
    // EXTENSIONS
    // -----------------------------------------------------------------
    Lexeme{"maj13",   LexemeCategory::EXTENSION, false},
    Lexeme{"maj11",   LexemeCategory::EXTENSION, false},
    Lexeme{"maj9",    LexemeCategory::EXTENSION, false},

    Lexeme{"13",      LexemeCategory::EXTENSION, true},
    Lexeme{"11",      LexemeCategory::EXTENSION, true},
    Lexeme{"9",       LexemeCategory::EXTENSION, true},

    // -----------------------------------------------------------------
    // ALTERATIONS
    // -----------------------------------------------------------------
    Lexeme{"alt",     LexemeCategory::ALTERATION, false},

    Lexeme{"#11",     LexemeCategory::ALTERATION, true},
    Lexeme{"b13",     LexemeCategory::ALTERATION, true},
    Lexeme{"b9",      LexemeCategory::ALTERATION, true},
    Lexeme{"#9",      LexemeCategory::ALTERATION, true},
    Lexeme{"b5",      LexemeCategory::ALTERATION, true},
    Lexeme{"#5",      LexemeCategory::ALTERATION, true},

    // -----------------------------------------------------------------
    // SUSPENSIONS
    // -----------------------------------------------------------------
    Lexeme{"sus2",    LexemeCategory::SUSPENSION, false},
    Lexeme{"sus4",    LexemeCategory::SUSPENSION, false},

    // -----------------------------------------------------------------
    // ADDITIONS
    // -----------------------------------------------------------------
    Lexeme{"add11",   LexemeCategory::ADDITION, false},
    Lexeme{"add9",    LexemeCategory::ADDITION, false},

    // -----------------------------------------------------------------
    // SPECIAL
    // -----------------------------------------------------------------
    Lexeme{"N.C",     LexemeCategory::SPECIAL, true}
};

// -----------------------------------------------------------------------------
// TRI constexpr par longueur décroissante
// -----------------------------------------------------------------------------
template <std::size_t N>
constexpr std::array<Lexeme, N>
sort_by_length_desc(std::array<Lexeme, N> arr)
{
    for (std::size_t i = 1; i < N; ++i)
    {
        Lexeme key = arr[i];
        std::size_t j = i;

        while (j > 0 &&
               arr[j - 1].text.size() < key.text.size())
        {
            arr[j] = arr[j - 1];
            --j;
        }

        arr[j] = key;
    }

    return arr;
}

// -----------------------------------------------------------------------------
// TABLEAU TRIÉ
// -----------------------------------------------------------------------------
constexpr auto SORTED_LEXEMES =
    sort_by_length_desc(ALL_LEXEMES);

} // namespace musical::io::chord