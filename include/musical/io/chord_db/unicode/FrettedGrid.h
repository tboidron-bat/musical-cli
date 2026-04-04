#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <limits>

#include <musical/io/chord_db/unicode/GridCore.h>

namespace io::chord::db::unicode
{

class FrettedGrid : public GridCore
{

protected:    
    std::string _fret_annotation;  
    std::size_t _annotation_row = 0;
public:    

    FrettedGrid(
        std::size_t nb_strings,
        std::size_t nb_cases);

    std::size_t width() const
    {
        return 2 * _nb_strings - 1 + _fret_annotation.size();
    }    
};

}