#include <musical/io/core/note/in/NoteLexer.h>
#include <musical/io/utils/in/normalize_to_ascii.h>

#include <iostream>
#include <cctype>

//#define DEBUG

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


// #ifdef DEBUG
//         std::cout << "\n#DEBUG NoteLexer::tokenize()\n input=[" << input
//                   << "] norm=[" << norm
//                   << "] -> (no match)\n";
// #endif


    if (pos == 0)
    {
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

#ifdef DEBUG
    std::cout << "\nDEBUG:\n#-class NoteLexer-#\ncalling: tokenize(" << input << ")" << "\n";
    for (const auto& t : tokens)
        std::cout << "Found token: " << t << "\n";
#endif

    if(tokens.empty())
    {
        std::cerr << "Note lexing failed\n";
        return {};
    }


    return tokens;
}


std::ostream& operator<<(std::ostream& os, const token_t& tok)
{
    const char* kind_str = nullptr;

    switch (tok.kind)
    {
        case token_t::TokenKind::NAME:
            kind_str = "NAME";
            break;

        case token_t::TokenKind::ACCIDENTAL:
            kind_str = "ACCIDENTAL";
            break;
    }

    return os << "[" << kind_str << " : \"" << tok.text << "\"]";
}



} // namespace musical::io::note