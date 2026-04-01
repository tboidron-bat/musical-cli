#pragma once

#include <string>

#include <musical/guitar_chord_database/Diagram.h>


namespace io::guitar::unicode
{
    
class OpenGrid;
class DottedGrid;
class GridCore;

class DiagramRenderer 
{
public:

    static std::string render(
        const chord::database::Diagram&,
        const std::string&name="");

private:
    static void fill_grid(
        OpenGrid& grid,
        const chord::database::Diagram& diagram
    );
    static void fill_grid(
        DottedGrid& grid,
        const chord::database::Diagram& diagram);

    static void fill_grid(
        GridCore& grid,
        const chord::database::Diagram& diagram);

    static void write_fret(
        GridCore& grid,
        const chord::database::Diagram& diagram);

    static void write_name(
         GridCore& grid,
         const std::string&);

};

}
