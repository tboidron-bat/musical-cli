#pragma once

#include <array>
#include <vector>
#include <string_view>
#include <optional>

namespace musical::io::note
{
    enum class TokenKind
    {
        NAME,
        ACCIDENTAL
    };

    struct lexeme_t
    {
        std::string_view _text;
        TokenKind _kind;
    };

    inline constexpr std::array<lexeme_t, 24> lexemes =
    {
        // =========================
        // 1️⃣ NOMS SAXONS (7)
        // =========================
        lexeme_t{ "c",   TokenKind::NAME },
        lexeme_t{ "d",   TokenKind::NAME },
        lexeme_t{ "e",   TokenKind::NAME },
        lexeme_t{ "f",   TokenKind::NAME },
        lexeme_t{ "g",   TokenKind::NAME },
        lexeme_t{ "a",   TokenKind::NAME },
        lexeme_t{ "b",   TokenKind::NAME },

        // =========================
        // 2️⃣ NOMS LATINS (8)
        // =========================
        lexeme_t{ "do",  TokenKind::NAME },
        lexeme_t{ "re",  TokenKind::NAME },
        lexeme_t{ "mi",  TokenKind::NAME },
        lexeme_t{ "fa",  TokenKind::NAME },
        lexeme_t{ "sol", TokenKind::NAME },
        lexeme_t{ "la",  TokenKind::NAME },
        lexeme_t{ "si",  TokenKind::NAME },

        // =========================
        // 3️⃣ ALTÉRATIONS ASCII (5)
        // =========================
        lexeme_t{ "#",   TokenKind::ACCIDENTAL },
        lexeme_t{ "##",  TokenKind::ACCIDENTAL },
        lexeme_t{ "b",   TokenKind::ACCIDENTAL },
        lexeme_t{ "bb",  TokenKind::ACCIDENTAL },
        lexeme_t{ "n",   TokenKind::ACCIDENTAL },

        // =========================
        // 4️⃣ ALTÉRATIONS UNICODE (5)
        // =========================
        lexeme_t{ "♯",   TokenKind::ACCIDENTAL },
        lexeme_t{ "𝄪",   TokenKind::ACCIDENTAL },
        lexeme_t{ "♭",   TokenKind::ACCIDENTAL },
        lexeme_t{ "𝄫",   TokenKind::ACCIDENTAL },
        lexeme_t{ "♮",   TokenKind::ACCIDENTAL }
    };


    struct token_t
    {
        TokenKind kind;
        std::string_view text;
    };
    

    class Lexer
    {

    public:
        static std::optional<std::vector<token_t>>
        tokenize(std::string_view input);
    };
}
