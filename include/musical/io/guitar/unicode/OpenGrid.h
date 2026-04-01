#pragma once

#include <string>
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

    GridCore& core() { return _grid; }
    const GridCore& core() const { return _grid; }    

    void set_finger(GridCore::STRING,std::size_t,GridCore::DOIGT);
    void set_finger(GridCore::STRING,std::size_t);    

    void set_open_string(GridCore::STRING);
    void set_muted_string(GridCore::STRING);

    // hauteur finale avec open strings + nut
    std::size_t height() const;
    std::size_t width() const;

    void write_right(std::size_t,const std::string&);

    std::string render() const;
};
}