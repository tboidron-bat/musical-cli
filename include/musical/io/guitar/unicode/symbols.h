#pragma once

namespace io::guitar::unicode
{

    // ------------------------------------------------------------
    // Symboles de base
    // ------------------------------------------------------------
    static inline constexpr const char* STRING_CHAR = "│";
    static inline constexpr const char* MUTED_CHAR  = "×";
    static inline constexpr const char* OPEN_CHAR   = "o";
    static inline constexpr const char* EMPTY_CELL  = " ";

    // ------------------------------------------------------------
    // Sillet
    // ------------------------------------------------------------
    static inline constexpr const char* NUT_LEFT  = "╒";
    static inline constexpr const char* NUT_RIGHT = "╕";
    static inline constexpr const char* NUT_BAR   = "═";

    // ------------------------------------------------------------
    // Frettes
    // ------------------------------------------------------------
    static inline constexpr const char* FRET_BAR   = "─";
    static inline constexpr const char* FRET_LEFT  = "├";
    static inline constexpr const char* FRET_RIGHT = "┤";
    static inline constexpr const char* FRET_CROSS = "┼";

    // ------------------------------------------------------------
    // Doigts
    // ------------------------------------------------------------
    static inline constexpr const char* DOT = "•";    

    static inline constexpr const char* CIRCLED_DIGITS[10] =
    {
        "",
        "①","②","③","④","⑤","⑥","⑦","⑧","⑨"
    };

    static inline constexpr const char* CIRCLED_DIGITS_FILLED[10] =
    {
        "",
        "❶","❷","❸","❹","❺","❻","❼","❽","❾"
    };

}