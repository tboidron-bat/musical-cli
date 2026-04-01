#include <musical/io/core/chord/parser/ChordLexer.h>

#include <cassert>
#include <iostream>
#include <vector>
#include <string>

using namespace musical::io::chord;

// ------------------------------------------------------------
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

// ------------------------------------------------------------
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
    // TRIADS / BASIC
    // ---------------------------------------------------------
    expect_types("Cmajor", {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cminor", {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cdim",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Caug",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // SUSPENSIONS
    // ---------------------------------------------------------
    expect_types("Csus2",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Csus4",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("C7sus4", {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    // ---------------------------------------------------------
    // SEVENTH / BASIC
    // ---------------------------------------------------------
    expect_types("C7",     {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cdim7",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Caug7",  {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME   // aug + 7
    });

    // ---------------------------------------------------------
    // SIXTH / ADD
    // ---------------------------------------------------------
    expect_types("C6",     {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("C69",    {
        token_t::TokenType::ROOT, 
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // ALTERED / DOMINANT
    // ---------------------------------------------------------
    expect_types("C7b5",   {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("C7#9",   {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("C7b9",   {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("C9",     {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    expect_types("C9b5",   {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Caug9",  {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME   // aug + 9
    });

    expect_types("C11",    {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    expect_types("C9#11",  {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("C13",    {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // MAJOR EXTENDED
    // ---------------------------------------------------------
    expect_types("Cmaj7",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    expect_types("Cmaj7b5",{
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Cmaj7#5",{
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Cmaj9",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cmaj11", {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cmaj13", {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // MINOR EXTENDED
    // ---------------------------------------------------------
    expect_types("Cm6", {
        token_t::TokenType::ROOT, 
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME});

    expect_types("Cm7",    {
        token_t::TokenType::ROOT, 
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME});

    expect_types("Cm7b5",  {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Cm9",    {
        token_t::TokenType::ROOT, 
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Cm69", {
        token_t::TokenType::ROOT, 
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Cm11",   {
        token_t::TokenType::ROOT, 
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    // ---------------------------------------------------------
    // MINOR MAJOR
    // ---------------------------------------------------------
    expect_types("Cmmaj7", {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME   // m + maj7
    });

    expect_types("Cmmaj7b5",{
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Cmmaj9", {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    expect_types("Cmmaj11",{
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME
    });

    // ---------------------------------------------------------
    // ADD
    // ---------------------------------------------------------
    expect_types("Cadd9",  {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});
    expect_types("Cmadd9", {
        token_t::TokenType::ROOT,
        token_t::TokenType::LEXEME,
        token_t::TokenType::LEXEME   // m + add9
    });

    // ---------------------------------------------------------
    // ALT
    // ---------------------------------------------------------
    expect_types("Calt",   {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // SLASH CHORDS
    // ---------------------------------------------------------
    expect_types("C/E",
        {token_t::TokenType::ROOT, token_t::TokenType::SLASH, token_t::TokenType::ROOT});

    expect_types("C/F",
        {token_t::TokenType::ROOT, token_t::TokenType::SLASH, token_t::TokenType::ROOT});

    expect_types("C/G",
        {token_t::TokenType::ROOT, token_t::TokenType::SLASH, token_t::TokenType::ROOT});

    // ---------------------------------------------------------
    // CASE SENSITIVITY
    // ---------------------------------------------------------
    expect_types("cm7",
        {token_t::TokenType::ROOT, token_t::TokenType::LEXEME, token_t::TokenType::LEXEME});

    expect_types("cM7",
        {token_t::TokenType::ROOT, token_t::TokenType::LEXEME});

    // ---------------------------------------------------------
    // INVALID
    // ---------------------------------------------------------
    auto invalid = ChordLexer::tokenize("Cmaj7M");
    assert(!invalid.empty());
    assert(invalid.back().type == token_t::TokenType::UNKNOWN);

    std::cout << "\nAll lexer tests passed.\n";
}