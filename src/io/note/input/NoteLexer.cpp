#include <musical/io/note/input/NoteLexer.h>
#include <musical/io/utils/input/normalize_to_ascii.h>

#include <iostream>
#include <cctype>

//#define NOTE_LEXER_DEBUG

namespace musical::io::note
{

// ------------------------------------------------------------
// parse_note_length
// ------------------------------------------------------------
size_t
NoteLexer::parse_note_length(std::string_view input)
{
    std::string norm =
        musical::io::normalize_to_ascii(input);

    // lowercase local
    for (char& c : norm)
        c = static_cast<char>(
            std::tolower(static_cast<unsigned char>(c)));

    size_t pos = 0;

    // NAME
    for (const auto& lex : lexemes)
    {
        if (lex.kind != token_t::TokenKind::NAME)
            continue;

        if (norm.starts_with(lex.text))
        {
            pos = lex.text.size();
            break;
        }
    }

    if (pos == 0)
        return 0;

    // ACCIDENTAL
    std::string_view rest = norm.substr(pos);

    for (const auto& lex : lexemes)
    {
        if (lex.kind != token_t::TokenKind::ACCIDENTAL)
            continue;

        if (rest.starts_with(lex.text))
            return pos + lex.text.size();
    }

    return pos;
}

// ------------------------------------------------------------
// tokenize
// ------------------------------------------------------------
std::vector<token_t>
NoteLexer::tokenize(std::string_view input)
{
    std::vector<token_t> tokens;

    std::string norm =
        musical::io::normalize_to_ascii(input);

    // lowercase local
    for (char& c : norm)
        c = static_cast<char>(
            std::tolower(static_cast<unsigned char>(c)));

    size_t pos = 0;

    // NAME
    for (const auto& lex : lexemes)
    {
        if (lex.kind != token_t::TokenKind::NAME)
            continue;

        if (norm.starts_with(lex.text))
        {
            tokens.push_back({
                token_t::TokenKind::NAME,
                norm.substr(0, lex.text.size())
            });

            pos = lex.text.size();
            break;
        }
    }

    if (pos == 0)
    {
#ifdef NOTE_LEXER_DEBUG
        std::cout << "\n#DEBUG NoteLexer::tokenize(...) input=[" << input
                  << "] norm=[" << norm
                  << "] -> (no match)\n";
#endif
        return tokens;
    }

    // ACCIDENTAL
    std::string_view rest = norm.substr(pos);

    for (const auto& lex : lexemes)
    {
        if (lex.kind != token_t::TokenKind::ACCIDENTAL)
            continue;

        if (rest.starts_with(lex.text))
        {
            tokens.push_back({
                token_t::TokenKind::ACCIDENTAL,
                norm.substr(pos, lex.text.size())
            });
            break;
        }
    }

#ifdef NOTE_LEXER_DEBUG
    std::cout << "\n#DEBUG NoteLexer::tokenize(...) input=[" << input
              << "] norm=[" << norm << "]";

    for (const auto& t : tokens)
    {
        std::cout << "  ";
        if (t.kind == token_t::TokenKind::NAME)
            std::cout << "NAME";
        else
            std::cout << "ACCIDENTAL";

        std::cout << "=[" << t.text << "]";
    }

    std::cout << "\n";
#endif

    if(tokens.empty())
    {
        std::cerr << "Note lexing failed\n";
        return {};
    }


    return tokens;
}

} // namespace musical::io::note