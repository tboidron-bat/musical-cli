#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace io::guitar::diagram::unicode
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


class Grid
{
public:
    enum class DOIGT
    {
        POUCE = 0,
        INDEX = 1,
        MAJEUR = 2,
        ANNULAIRE = 3,
        AURICULAIRE = 4
    };    
    enum class STRING
    {
        MI_GRAVE = 0,
        LA,
        RE,
        SOL,
        SI,
        MI_AIGU
    };
private:        
    std::size_t _nb_strings = 0;
    std::size_t _nb_frets   = 0;
    //std::size_t _line_width = 0;   

    bool _has_nut = false;    
public:


private:
    std::vector<std::vector<const char*>> _grid;;    

    void add_strings(std::size_t);    
    void add_fret(std::size_t);    
    
    void add_nut();

public:    

    Grid(
        std::size_t nb_strings,
        std::size_t nb_frets,
        bool has_nut);

    void set_finger(
        STRING,
        std::size_t,
        DOIGT);

    std::string render();         

};

}