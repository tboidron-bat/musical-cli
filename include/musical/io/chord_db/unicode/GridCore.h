#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <limits>

#include <musical/io/chord_db/unicode/symbols.h>
#include <musical/core/guitar/Fingers.h>

//TODO: draw_barre :●═══● 

namespace io::chord::db::unicode
{
class GridCore
{
public:
    enum class STRING
    {
        MI_GRAVE = 0,
        LA,
        RE,
        SOL,
        SI,
        MI_AIGU
    };
    using row_t = std::vector<std::string>;    
protected:        
    std::size_t _nb_strings = 0;

protected:

    std::vector<row_t> _grid;
private:
    void add_strings_row();    
    void add_fret_row();   
    void add_case_row();    
public:    
    GridCore(
        std::size_t nb_strings,
        std::size_t nb_cases);

    virtual ~GridCore() = default;

    row_t& row(std::size_t r) { return _grid[r]; }

    const row_t& row(std::size_t r) const { return _grid[r]; }    

    void insert_row_top(row_t);
    void insert_row(std::size_t, row_t);

    void push_row(row_t r) { _grid.push_back(std::move(r)); }

    static constexpr std::size_t RIGHT_SPACING = 4;    

    bool _extended_right = false;

    void extend_right();
    void write_right(std::size_t, const std::string&);

// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ 1 2 3 │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ 4 │
// ├─┼─┼─┼─┼─┼
    using Finger = musical::core::guitar::Finger;

    virtual void set_finger(
        STRING,
        std::size_t,
        Finger=Finger::NONE);

    virtual std::size_t width() const
    {
        return _grid.empty() ? 0 : _grid[0].size();
    }    
    virtual std::size_t height() const
    {
        return _grid.size();
    }
    void add_title_row(
        const std::string&);

    void write_caged_row(const std::string&);

    virtual std::string render() const;  

    //hack pour ajouter des lignes vides en haut.
    void pad_top(std::size_t n);
};
}