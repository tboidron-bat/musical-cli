#include <musical/io/chord/input/ChordLexer.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <string>

using namespace musical::io::chord;

static void expect_types(const std::string& input,
                         const std::vector<TokenType>& expected)
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
    expect_types("C",      {TokenType::ROOT});
    expect_types("c",      {TokenType::ROOT});
    expect_types("Ré",     {TokenType::ROOT});
    expect_types("ré",     {TokenType::ROOT});
    expect_types("Fa♯",    {TokenType::ROOT});
    expect_types("Sol𝄪",   {TokenType::ROOT});
    expect_types("Bb",     {TokenType::ROOT});
    expect_types("bb",     {TokenType::ROOT});

    // ---------------------------------------------------------
    // TRIADS
    // ---------------------------------------------------------
    expect_types("Cm",     {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Cmin",   {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Cmaj",   {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Cdim",   {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Caug",   {TokenType::ROOT, TokenType::LEXEME});

    // ---------------------------------------------------------
    // SEVENTH
    // ---------------------------------------------------------
    expect_types("C7",     {TokenType::ROOT, TokenType::LEXEME});
    expect_types("CM7",    {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Cmaj7",  {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Cdim7",  {TokenType::ROOT, TokenType::LEXEME});

    // ---------------------------------------------------------
    // EXTENSIONS
    // ---------------------------------------------------------
    expect_types("C9",     {TokenType::ROOT, TokenType::LEXEME});
    expect_types("C11",    {TokenType::ROOT, TokenType::LEXEME});
    expect_types("C13",    {TokenType::ROOT, TokenType::LEXEME});

    // ---------------------------------------------------------
    // ALTERATIONS
    // ---------------------------------------------------------
    expect_types("C7b9",   {TokenType::ROOT, TokenType::LEXEME, TokenType::LEXEME});
    expect_types("C7#9",   {TokenType::ROOT, TokenType::LEXEME, TokenType::LEXEME});
    expect_types("C7b9#11",{TokenType::ROOT, TokenType::LEXEME, TokenType::LEXEME, TokenType::LEXEME});

    // ---------------------------------------------------------
    // SUSPENSIONS
    // ---------------------------------------------------------
    expect_types("Csus2",      {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Csus4",      {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Csus2sus4",  {TokenType::ROOT, TokenType::LEXEME, TokenType::LEXEME});

    // ---------------------------------------------------------
    // ADDITIONS
    // ---------------------------------------------------------
    expect_types("Cadd9",      {TokenType::ROOT, TokenType::LEXEME});
    expect_types("Csus2add11", {TokenType::ROOT, TokenType::LEXEME, TokenType::LEXEME});

    // ---------------------------------------------------------
    // SLASH CHORDS
    // ---------------------------------------------------------
    expect_types("C/G",
                 {TokenType::ROOT, TokenType::SLASH, TokenType::ROOT});

    expect_types("Cmaj7/G#",
                 {TokenType::ROOT, TokenType::LEXEME,
                  TokenType::SLASH, TokenType::ROOT});

    // ---------------------------------------------------------
    // CASE SENSITIVITY (musical correctness)
    // ---------------------------------------------------------
    expect_types("cm7",
                 {TokenType::ROOT, TokenType::LEXEME, TokenType::LEXEME});

    expect_types("cM7",
                 {TokenType::ROOT, TokenType::LEXEME});

    // ---------------------------------------------------------
    // INVALID / UNKNOWN
    // ---------------------------------------------------------
    auto invalid = ChordLexer::tokenize("Cmaj7M");
    assert(!invalid.empty());
    assert(invalid.back().type == TokenType::UNKNOWN);

    std::cout << "\nAll lexer tests passed.\n";
}