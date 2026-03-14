#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <musical/io/guitar/unicode/symbols.h>

namespace io::guitar::unicode
{

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
    bool _has_nut = false;    
public:


private:
    std::vector<std::vector<const char*>> _grid;

    void add_open_strings_row();
    void add_nut_row();
    void add_strings_row();    
    void add_fret_row();    

    inline std::size_t width() const
    {
        return 2 * _nb_strings - 1;
    }    


public:    

    Grid(
        std::size_t nb_strings,
        std::size_t nb_frets,
        bool has_nut);

    void set_finger(
        STRING,
        std::size_t,
        DOIGT);

    void set_open_string(
        STRING
        );

    void set_muted_string(
        STRING
        );

    std::string render();         

};

}