#pragma once

#include <cstdint>

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
    void enlarge();

public:
    static constexpr std::size_t DEFAULT_RIGHT_SPACING = 4;

    DottedGrid(std::size_t nb_strings,
               std::size_t nb_cases);

    void set_case_annotation(
        std::size_t case_number,
        const std::string& txt);
};
}