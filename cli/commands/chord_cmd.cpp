#include <musical/io/note/input/Lexer.h>
#include <musical/io/note/input/Parser.h>

#include <iostream>
#include <string>

static const char* name_to_string(musical::core::Note::Name n)
{
    using N = musical::core::Note::Name;

    switch (n)
    {
        case N::C: return "C";
        case N::D: return "D";
        case N::E: return "E";
        case N::F: return "F";
        case N::G: return "G";
        case N::A: return "A";
        case N::B: return "B";
    }

    return "?";
}

static const char* accidental_to_string(musical::core::Note::Accidental a)
{
    using A = musical::core::Note::Accidental;

    switch (a)
    {
        case A::NONE:         return "NONE";
        case A::SHARP:        return "SHARP";
        case A::FLAT:         return "FLAT";
        case A::DOUBLE_SHARP: return "DOUBLE_SHARP";
        case A::DOUBLE_FLAT:  return "DOUBLE_FLAT";
    }

    return "?";
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "usage: note <symbol>\n";
        return 1;
    }

    const std::string symbol = argv[1];

    // 1️⃣ Lexing
    auto tokens_opt =
        musical::io::note::Lexer::tokenize(symbol);

    if (!tokens_opt)
    {
        std::cerr << "Lexing failed\n";
        return 2;
    }

    // 2️⃣ Parsing
    musical::io::note::Parser parser;

    auto pitch_opt = parser.parse(*tokens_opt);

    if (!pitch_opt)
    {
        std::cerr << "Parsing failed\n";
        return 3;
    }

    const auto& pitch = *pitch_opt;

    std::cout << "Parsed pitch:\n";
    std::cout << "  Name enum value: "
              << name_to_string(pitch.name) << "\n";
    std::cout << "  Accidental enum value: "
              << accidental_to_string(pitch.accidental) << "\n";

    return 0;
}
