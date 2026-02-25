#pragma once

#include <array>
#include <vector>
#include <string_view>

namespace musical::io::note
{
    enum class TokenKind
    {
        NAME,
        ACCIDENTAL
    };

    struct lexeme_t
    {
        std::string_view text;   // UTF-8
        TokenKind kind;
    };

    // ⚠️ Tous les littéraux sont en UTF-8 explicite
    // ⚠️ Ordre trié du plus long au plus court pour éviter ambiguïtés
    inline constexpr std::array<lexeme_t, 24> lexemes =
    {
        // =====================================================
        // ALTÉRATIONS (LONGUES AVANT COURTES)
        // =====================================================

        lexeme_t{ "##",  TokenKind::ACCIDENTAL },
        lexeme_t{ "bb",  TokenKind::ACCIDENTAL },

        // Unicode (multi-octets UTF-8)
        lexeme_t{ "𝄪",  TokenKind::ACCIDENTAL }, // U+1D12A (4 bytes UTF-8)
        lexeme_t{ "𝄫",  TokenKind::ACCIDENTAL }, // U+1D12B (4 bytes UTF-8)

        lexeme_t{ "#",   TokenKind::ACCIDENTAL },
        lexeme_t{ "b",   TokenKind::ACCIDENTAL },

        lexeme_t{ "♯",  TokenKind::ACCIDENTAL }, // U+266F (3 bytes UTF-8)
        lexeme_t{ "♭",  TokenKind::ACCIDENTAL }, // U+266D (3 bytes UTF-8)

        lexeme_t{ "n",   TokenKind::ACCIDENTAL },
        lexeme_t{ "♮",  TokenKind::ACCIDENTAL }, // U+266E (3 bytes UTF-8)

        // =====================================================
        // NOMS LATINS (LONG AVANT COURT)
        // =====================================================

        lexeme_t{ "sol", TokenKind::NAME },
        lexeme_t{ "do",  TokenKind::NAME },
        lexeme_t{ "re",  TokenKind::NAME },
        lexeme_t{ "mi",  TokenKind::NAME },
        lexeme_t{ "fa",  TokenKind::NAME },
        lexeme_t{ "la",  TokenKind::NAME },
        lexeme_t{ "si",  TokenKind::NAME },

        // =====================================================
        // NOMS SAXONS
        // =====================================================

        lexeme_t{ "c",   TokenKind::NAME },
        lexeme_t{ "d",   TokenKind::NAME },
        lexeme_t{ "e",   TokenKind::NAME },
        lexeme_t{ "f",   TokenKind::NAME },
        lexeme_t{ "g",   TokenKind::NAME },
        lexeme_t{ "a",   TokenKind::NAME },
        lexeme_t{ "b",   TokenKind::NAME }
    };

    struct token_t
    {
        TokenKind kind;
        std::string_view text;   // UTF-8 slice of input
    };

    class Lexer
    {
    public:
        // Tokenize note (UTF-8 aware, byte-level deterministic scan)
        static std::vector<token_t>
        tokenize(std::string_view input);

        // Returns number of UTF-8 bytes consumed for a valid note
        // (NAME + optional ACCIDENTAL)
        static size_t
        parse_note_length(std::string_view input);
    };
}