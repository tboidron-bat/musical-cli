#include <musical/io/note/input/NoteParser.h>

#include <algorithm>
#include <cctype>

namespace musical::io::note {


// ============================
// Conversion NAME
// ============================

std::optional<musical::core::NoteName>
NoteParser::to_name(std::string_view text)
{
    using Name = musical::core::NoteName;

    // Saxon
    if (text == "c")  return Name::C;
    if (text == "d")  return Name::D;
    if (text == "e")  return Name::E;
    if (text == "f")  return Name::F;
    if (text == "g")  return Name::G;
    if (text == "a")  return Name::A;
    if (text == "b")  return Name::B;

    // Latin
    if (text == "do")  return Name::C;
    if (text == "re")  return Name::D;
    if (text == "mi")  return Name::E;
    if (text == "fa")  return Name::F;
    if (text == "sol") return Name::G;
    if (text == "la")  return Name::A;
    if (text == "si")  return Name::B;

    return std::nullopt;
}


// ============================
// Conversion ACCIDENTAL
// ============================

std::optional<musical::core::Accidental>
NoteParser::to_accidental(std::string_view text)
{
    using Acc = musical::core::Accidental;

    if (text == "#"  || text == "♯")
        return Acc::SHARP;

    if (text == "##" || text == "𝄪")
        return Acc::DOUBLE_SHARP;

    if (text == "b"  || text == "♭")
        return Acc::FLAT;

    if (text == "bb" || text == "𝄫")
        return Acc::DOUBLE_FLAT;

    if (text == "n"  || text == "♮")
        return Acc::NONE;

    return std::nullopt;
}


// ============================
// Parse principal
// ============================

std::optional<musical::core::pitch_t>
NoteParser::parse(const std::vector<token_t>& tokens)
{
    using musical::core::pitch_t;
    using musical::core::Accidental;

    if (tokens.empty())
        return std::nullopt;

    // 1️⃣ Le premier token doit être un NAME
    if (tokens[0].kind != TokenKind::NAME)
        return std::nullopt;

    auto name = to_name(tokens[0].text);
    if (!name)
        return std::nullopt;

    pitch_t result{};
    result._name = *name;
    result._accidental = Accidental::NONE;
    result._octave = 4; // octave par défaut

    // 2️⃣ Si un second token existe → ACCIDENTAL
    if (tokens.size() == 2)
    {
        if (tokens[1].kind != TokenKind::ACCIDENTAL)
            return std::nullopt;

        auto acc = to_accidental(tokens[1].text);
        if (!acc)
            return std::nullopt;

        result._accidental = *acc;
    }
    else if (tokens.size() > 2)
    {
        return std::nullopt; // trop de tokens
    }

    return result;
}

} // namespace musical::io::note