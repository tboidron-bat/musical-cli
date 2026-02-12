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
    LexemeCategory  category;
};

// -----------------------------------------------------------------------------
// TABLEAU BRUT
// -----------------------------------------------------------------------------
constexpr std::array ALL_LEXEMES = {

    // TRIADES
    Lexeme{"major",      LexemeCategory::TRIAD},
    Lexeme{"majeur",     LexemeCategory::TRIAD},
    Lexeme{"maj",        LexemeCategory::TRIAD},
    Lexeme{"minor",      LexemeCategory::TRIAD},
    Lexeme{"mineur",     LexemeCategory::TRIAD},
    Lexeme{"min",        LexemeCategory::TRIAD},
    Lexeme{"m",          LexemeCategory::TRIAD},
    Lexeme{"-",          LexemeCategory::TRIAD},
    Lexeme{"dim",        LexemeCategory::TRIAD},
    Lexeme{"°",          LexemeCategory::TRIAD},
    Lexeme{"aug",        LexemeCategory::TRIAD},
    Lexeme{"+",          LexemeCategory::TRIAD},

    // SEVENTH
    Lexeme{"maj7",       LexemeCategory::SEVENTH},
    Lexeme{"M7",         LexemeCategory::SEVENTH},
    Lexeme{"Δ7",         LexemeCategory::SEVENTH},
    Lexeme{"Δ",          LexemeCategory::SEVENTH},
    Lexeme{"7",          LexemeCategory::SEVENTH},
    Lexeme{"dim7",       LexemeCategory::SEVENTH},

    // EXTENSIONS
    Lexeme{"9",          LexemeCategory::EXTENSION},
    Lexeme{"11",         LexemeCategory::EXTENSION},
    Lexeme{"13",         LexemeCategory::EXTENSION},
    Lexeme{"maj9",       LexemeCategory::EXTENSION},
    Lexeme{"maj11",      LexemeCategory::EXTENSION},
    Lexeme{"maj13",      LexemeCategory::EXTENSION},

    // ALTERATIONS
    Lexeme{"b5",         LexemeCategory::ALTERATION},
    Lexeme{"#5",         LexemeCategory::ALTERATION},
    Lexeme{"b9",         LexemeCategory::ALTERATION},
    Lexeme{"#9",         LexemeCategory::ALTERATION},
    Lexeme{"#11",        LexemeCategory::ALTERATION},
    Lexeme{"b13",        LexemeCategory::ALTERATION},

    // SUSPENSIONS
    Lexeme{"sus2",       LexemeCategory::SUSPENSION},
    Lexeme{"sus4",       LexemeCategory::SUSPENSION},

    // ADDITIONS
    Lexeme{"add9",       LexemeCategory::ADDITION},

    // SPECIAL
    Lexeme{"N.C",        LexemeCategory::SPECIAL}
};

// -----------------------------------------------------------------------------
// TRI INSERTION constexpr (par taille décroissante)
// -----------------------------------------------------------------------------
template <std::size_t N>
constexpr std::array<Lexeme, N> sort_by_length_desc(std::array<Lexeme, N> arr)
{
    for (std::size_t i = 1; i < N; ++i)
    {
        Lexeme key = arr[i];
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
// TABLEAU TRIÉ
// -----------------------------------------------------------------------------
constexpr auto SORTED_LEXEMES = sort_by_length_desc(ALL_LEXEMES);

} // namespace musical::io::chord
