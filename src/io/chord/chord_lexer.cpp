#include <musical/io/chord/chord_lexer.h>
#include <algorithm>

namespace musical::chord
{

// --- Définition interne (pas un token final)
struct TokenDef
{
    std::string_view lexeme;
    std::string_view canonical;
    TokenKind kind;
};

static const std::vector<TokenDef> TOKEN_DEFS =
{
    // --- QUALITIES ---
    {"major", "major", TokenKind::QUALITY},
    {"maj",   "major", TokenKind::QUALITY},
    {"minor", "minor", TokenKind::QUALITY},
    {"min",   "minor", TokenKind::QUALITY},
    {"m",     "minor", TokenKind::QUALITY},
    {"dim",   "diminished", TokenKind::QUALITY},
    {"°",     "diminished", TokenKind::QUALITY},
    {"aug",   "augmented",  TokenKind::QUALITY},
    {"+",     "augmented",  TokenKind::QUALITY},

    // --- EXTENSIONS ---
    {"maj13", "maj13", TokenKind::EXTENSION},
    {"13",    "13",    TokenKind::EXTENSION},    
    {"maj11", "maj11", TokenKind::EXTENSION},
    {"11",    "11",    TokenKind::EXTENSION},    
    {"maj9",  "maj9",  TokenKind::EXTENSION},
    {"9",     "9",     TokenKind::EXTENSION},    
    {"maj7",  "maj7",  TokenKind::EXTENSION},
    {"7M",    "maj7",  TokenKind::EXTENSION},    
    {"M7",    "maj7",  TokenKind::EXTENSION},        
    {"Δ",     "maj7",  TokenKind::EXTENSION},                        
    {"Δ7",    "maj7",  TokenKind::EXTENSION},                
    {"△7",    "maj7",  TokenKind::EXTENSION},                    
    {"△",     "maj7",  TokenKind::EXTENSION},                        
    {"7",     "7",     TokenKind::EXTENSION},
    {"6",     "6",     TokenKind::EXTENSION},
    // --- ALTERATIONS ---
    {"#11", "#11", TokenKind::ALTERATION},
    {"b13", "b13", TokenKind::ALTERATION},
    {"#9",  "#9",  TokenKind::ALTERATION},
    {"b9",  "b9",  TokenKind::ALTERATION},
    {"#5",  "#5",  TokenKind::ALTERATION},
    {"b5",  "b5",  TokenKind::ALTERATION},

    // --- SUSPENSIONS ---
    {"sus4", "sus4", TokenKind::SUSPENSION},
    {"sus2", "sus2", TokenKind::SUSPENSION},

    // --- ADD ---
    {"add13", "add13", TokenKind::ADD},
    {"add11", "add11", TokenKind::ADD},
    {"add9",  "add9",  TokenKind::ADD}
};

// 🔥 Tri par longueur décroissante (anti conflit m / maj7)
static std::vector<TokenDef> sorted_defs()
{
    auto defs = TOKEN_DEFS;

    std::sort(defs.begin(), defs.end(),
        [](const TokenDef& a, const TokenDef& b)
        {
            return a.lexeme.size() > b.lexeme.size();
        });

    return defs;
}

std::optional<token_t> Lexer::match_token(std::string_view input)
{
    static const auto defs = sorted_defs();

    for (const auto& def : defs)
    {
        if (input.starts_with(def.lexeme))
        {
            return token_t{
                std::string(def.lexeme),
                std::string(def.canonical),
                def.kind
            };
        }
    }

    return std::nullopt;
}

std::vector<token_t> Lexer::tokenize(const std::string& input)
{
    std::vector<token_t> result;
    std::string_view remaining = input;

    while (!remaining.empty())
    {
        if (auto tok = match_token(remaining))
        {
            result.push_back(*tok);
            remaining.remove_prefix(tok->_lexeme.size());
        }
        else
        {
            result.push_back(token_t{
                std::string(1, remaining.front()),
                "",
                TokenKind::UNKNOWN
            });

            remaining.remove_prefix(1);
        }
    }

    return result;
}

}
