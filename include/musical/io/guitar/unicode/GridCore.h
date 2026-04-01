#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <limits>

#include <musical/io/guitar/unicode/symbols.h>

//TODO: draw_barre :●═══● 

// 
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
class GridCore
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

    void insert_row_top(row_t row)
    {
        _grid.insert(_grid.begin(), std::move(row));
    }    
    void insert_row(std::size_t index, row_t row)
    {
        if (index > _grid.size())
            index = _grid.size();

        _grid.insert(_grid.begin() + index, std::move(row));
    }    

    void push_row(row_t r) { _grid.push_back(std::move(r)); }

    bool _extended_right = false;

    void extend_right();
    void write_right(std::size_t, const std::string&);


// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ - - - │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ │ │
    virtual void set_finger(
        STRING string,
        std::size_t case_number);    

// │ │ │ │ │ │
// ├─┼─┼─┼─┼─┼
// │ 1 2 3 │ │
// ├─┼─┼─┼─┼─┼
// │ │ │ │ 4 │
// ├─┼─┼─┼─┼─┼
    virtual void set_finger(
        STRING,
        std::size_t,
        DOIGT);

    virtual std::size_t width() const
    {
        return _grid.empty() ? 0 : _grid[0].size();
    }    
    virtual std::size_t height() const
    {
        return _grid.size();
    }
    virtual std::string render() const;  
    
    
    static GridCore::row_t make_centered_row(
        const std::string& text,
        std::size_t width)
    {
        GridCore::row_t row(width, " ");

        std::size_t start =
            (text.size() < width)
            ? (width - text.size()) / 2
            : 0;

        for (std::size_t i = 0;
            i < text.size() && (start + i) < width;
            ++i)
        {
            row[start + i] = std::string(1, text[i]);
        }

        return row;
    }

};
}