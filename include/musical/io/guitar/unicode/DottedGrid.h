#pragma once

#include <cstdint>
#include <string>

#include <musical/io/guitar/unicode/OpenGrid.h>

//     o o × × 
// ╒═════════╕
//      .
//      .      <---- dots
//     ...    
// │ │ │ │ │ │      
// ├─┼─┼─┼─┼─┤      
// │ │ │ │ │ │ IX  <----
// ├─┼─┼─┼─┼─┤      
// │ │ │ │ │ │      
// ├─┼─┼─┼─┼─┤      
// │ │ │ │ │ │      
namespace io::guitar::unicode
{
class DottedGrid : public OpenGrid
{
private:
    void add_dots();

public:

    DottedGrid(std::size_t nb_strings,
               std::size_t nb_cases);

};
}