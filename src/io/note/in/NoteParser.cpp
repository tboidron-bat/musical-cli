#include <musical/io/note/in/NoteParser.h>
#include <musical/Core/note/NoteFactory.h>

namespace musical::io::note
{

using musical::core::Accidental;
using musical::core::note::Factory;

// ------------------------------------------------------------
// Parse
// ------------------------------------------------------------
std::optional<musical::core::Note>
NoteParser::parse(const std::vector<token_t>& tokens)
{
    if (tokens.empty() || tokens.size() > 2)
        return std::nullopt;

    // -------------------------
    // NAME obligatoire
    // -------------------------
    if (tokens[0].kind != token_t::TokenKind::NAME)
        return std::nullopt;

    auto name_opt = to_name(tokens[0].text);
    if (!name_opt)
        return std::nullopt;

    char name = *name_opt;

    // -------------------------
    // ACCIDENTAL optionnel
    // -------------------------
    Accidental acc = Accidental::NONE;

    if (tokens.size() > 1)
    {
        if (tokens[1].kind != token_t::TokenKind::ACCIDENTAL)
            return std::nullopt;

        auto acc_opt = to_accidental(tokens[1].text);
        if (!acc_opt)
            return std::nullopt;

        acc = *acc_opt;
    }

    // 👉 octave par défaut
    constexpr int8_t octave = 4;

    // 👉 figure par défaut
    musical::core::Figure fig(musical::core::Figure::Type::QUARTER);

    return Factory::create(name, acc, octave, fig);
}

// ------------------------------------------------------------
// NAME
// ------------------------------------------------------------
std::optional<char>
NoteParser::to_name(std::string_view text)
{
    // Saxon
    if (text == "c") return 'c';
    if (text == "d") return 'd';
    if (text == "e") return 'e';
    if (text == "f") return 'f';
    if (text == "g") return 'g';
    if (text == "a") return 'a';
    if (text == "b") return 'b';

    // Français
    if (text == "do")  return 'c';
    if (text == "re")  return 'd';
    if (text == "mi")  return 'e';
    if (text == "fa")  return 'f';
    if (text == "sol") return 'g';
    if (text == "la")  return 'a';
    if (text == "si")  return 'b';

    return std::nullopt;
}


// ------------------------------------------------------------
// ACCIDENTAL
// ------------------------------------------------------------
std::optional<Accidental>
NoteParser::to_accidental(std::string_view text)
{
    if (text == "#")  return Accidental::SHARP;
    if (text == "b")  return Accidental::FLAT;
    if (text == "##") return Accidental::DOUBLE_SHARP;
    if (text == "bb") return Accidental::DOUBLE_FLAT;

    return std::nullopt;
}
}