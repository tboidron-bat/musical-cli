#include <musical/io/chord/in/ChordLexer.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <string>

using namespace musical::io::chord;

static void expect_types(const std::string& input,
                         const std::vector<token_t::TokenType>& expected)
{
    auto tokens = ChordLexer::tokenize(input);

    if (tokens.size() != expected.size())
    {
        std::cerr << "FAIL (size): " << input << "\n";
        std::exit(1);
    }

    for (size_t i = 0; i < expected.size(); ++i)
    {
        if (tokens[i].type != expected[i])
        {
            std::cerr << "FAIL (type mismatch): " << input << "\n";
            std::exit(1);
        }
    }

    std::cout << "OK: " << input << "\n";
}

int main()
{
    // ---------------------------------------------------------
    // ROOT
    // ---------------------------------------------------------
    expect_types("C",      {token_t::TokenType::ROOT});
    expect_types("c",      {token_t::TokenType::ROOT});
    expect_types("Ré",     {token_t::TokenType::ROOT});
    expect_types("ré",     {token_t::TokenType::ROOT});
    expect_types("Fa♯",    {token_t::TokenType::ROOT});
    expect_types("Sol𝄪",   {token_t::TokenType::ROOT});
    expect_types("Bb",     {token_t::TokenType::ROOT});
    expect_types("bb",     {token_t::TokenType::ROOT});

    // ---------------------------------------------------------
    // TRIADS
    // ---------------------------------------------------------
    expect_types("Cm",     {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cmin",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cmaj",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cdim",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Caug",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    // ---------------------------------------------------------
    // SEVENTH
    // ---------------------------------------------------------
    expect_types("C7",     {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("CM7",    {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cmaj7",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cdim7",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // EXTENSIONS
    // ---------------------------------------------------------
    expect_types("C9",     {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("C11",    {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("C13",    {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // ALTERATIONS
    // ---------------------------------------------------------
    expect_types("C7b9",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME});
    expect_types("C7#9",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME});
    expect_types("C7b9#11",{token_t::TokenType::ROOT, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // SUSPENSIONS
    // ---------------------------------------------------------
    expect_types("Csus2",      {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Csus4",      {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Csus2sus4",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // ADDITIONS
    // ---------------------------------------------------------
    expect_types("Cadd9",      {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Csus2add11", {token_t::TokenType::ROOT, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // SLASH CHORDS
    // ---------------------------------------------------------
    expect_types("C/G",
                 {token_t::TokenType::ROOT, token_t::TokenType::SLASH, token_t::TokenType::ROOT});

    expect_types("Cmaj7/G#",
                 {token_t::TokenType::ROOT, token_t::TokenType::LEXEME,
                  token_t::TokenType::SLASH, token_t::TokenType::ROOT});

    // ---------------------------------------------------------
    // CASE SENSITIVITY (musical correctness)
    // ---------------------------------------------------------
    expect_types("cm7",
                 {token_t::TokenType::ROOT, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME});

    expect_types("cM7",
                 {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    // ---------------------------------------------------------
    // INVALID / UNKNOWN
    // ---------------------------------------------------------
    auto invalid = ChordLexer::tokenize("Cmaj7M");
    assert(!invalid.empty());
    assert(invalid.back().type == token_t::TokenType::UNKNOWN);

    std::cout << "\nAll lexer tests passed.\n";
}