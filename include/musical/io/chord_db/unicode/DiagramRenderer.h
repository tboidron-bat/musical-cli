#pragma once

#include <string>

#include <musical/chord_db/Diagram.h>

namespace io::chord::db::unicode
{
    
class OpenGrid;
class DottedGrid;
class GridCore;

class DiagramRenderer 
{
public:

    static std::string render(
        const ::chord::db::Diagram&,
        const std::string&name="");

private:
    static void fill_grid(
        OpenGrid& grid,
        const ::chord::db::Diagram& diagram
    );
    static void fill_grid(
        DottedGrid& grid,
        const ::chord::db::Diagram& diagram);

    static void fill_grid(
        GridCore& grid,
        const ::chord::db::Diagram& diagram);

    static void write_fret(
        GridCore& grid,
        const ::chord::db::Diagram& diagram);

    static void write_name(
         GridCore& grid,
         const std::string&);

};

}
