#pragma once

#pragma once

#include <string>

namespace io::guitar::unicode
{

// ------------------------------------------------------------
// Symboles de base
// ------------------------------------------------------------
inline const std::string STRING_CHAR = "│";
inline const std::string MUTED_CHAR  = "×";
inline const std::string OPEN_CHAR   = "o";
inline const std::string EMPTY_CELL  = " ";

// ------------------------------------------------------------
// Sillet
// ------------------------------------------------------------
inline const std::string NUT_LEFT  = "╒";
inline const std::string NUT_RIGHT = "╕";
inline const std::string NUT_BAR   = "═";

// ------------------------------------------------------------
// Frettes
// ------------------------------------------------------------
inline const std::string FRET_BAR   = "─";
inline const std::string FRET_LEFT  = "├";
inline const std::string FRET_RIGHT = "┤";
inline const std::string FRET_CROSS = "┼";

// ------------------------------------------------------------
// Doigts
// ------------------------------------------------------------
inline const std::string BIG_DOT = "●";

// ⚠️ tableau de std::string (plus sûr que const char*)
inline const std::string CIRCLED_DIGITS[10] =
{
    "",
    "①","②","③","④","⑤","⑥","⑦","⑧","⑨"
};

inline const std::string CIRCLED_DIGITS_FILLED[10] =
{
    "",
    "❶","❷","❸","❹","❺","❻","❼","❽","❾"
};
} // namespace
