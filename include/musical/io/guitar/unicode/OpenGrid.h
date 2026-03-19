#pragma once

#include <string>
#include <sstream>
#include <vector>

#include <musical/io/guitar/unicode/GridCore.h>

// 
// x 0 x 0 
// ╒═════════╕
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │

namespace io::guitar::unicode
{
class OpenGrid 
{
protected:
    GridCore _grid;
    
private:
    void add_open_strings_row();
    void add_nut_row();
public:    
    OpenGrid(std::size_t nb_strings, std::size_t nb_cases);

    void set_finger(GridCore::STRING,std::size_t,GridCore::DOIGT);
    void set_finger(GridCore::STRING,std::size_t);    

    void set_open_string(GridCore::STRING);
    void set_muted_string(GridCore::STRING);

    std::size_t height() const
    {
        return _grid.height() + 2;
    }

    std::string render() const;
};
}