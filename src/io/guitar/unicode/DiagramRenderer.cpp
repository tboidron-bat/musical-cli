#include <musical/io/guitar/unicode/DiagramRenderer.h>

#include <musical/io/guitar/unicode/OpenGrid.h>
#include <musical/io/guitar/unicode/DottedGrid.h>

#include <iostream> //DEBUG
#include <memory>

//#define DEBUG

namespace io::guitar::unicode
{
static std::string to_roman(uint8_t value)
{
    static const std::pair<uint8_t, const char*> romans[] = {
        {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"}
    };

    std::string result;
    for (auto& [v, s] : romans)
    {
        while (value >= v)
        {
            result += s;
            value -= v;
        }
    }
    return result;
}
static std::size_t compute_total_cases(
    const chord::database::Diagram& diagram)
{
    constexpr std::size_t DEFAULT_DIAGRAM_HEIGHT = 4;

    std::size_t first = diagram.first_case();

    std::size_t missing_before =
        (first > 1) ? first - 1 : 0;

    std::size_t visible =
        diagram.nb_case();

    std::size_t padding_after =
        (missing_before + visible < DEFAULT_DIAGRAM_HEIGHT)
        ? DEFAULT_DIAGRAM_HEIGHT - (missing_before + visible)
        : 0;

    return missing_before + visible + padding_after;
}
std::string DiagramRenderer::render(
    const chord::database::Diagram& diagram,
    const std::string&name)
{
    //Diagram d'accord ouvert?
    if(diagram.is_open())
    {
        std::size_t first = diagram.first_case();

        std::unique_ptr<OpenGrid> grid;

        if(first < 5)
            grid = std::make_unique<OpenGrid>(
                chord::database::Diagram::STRING_COUNT,
                compute_total_cases(diagram));    
        else
            grid = std::make_unique<DottedGrid>(
                chord::database::Diagram::STRING_COUNT,
                compute_total_cases(diagram));

        fill_grid(*grid, diagram);
        write_name(grid->core(), name);

        return grid->render();
    }
    else
    {
        GridCore grid(
            chord::database::Diagram::STRING_COUNT,
            compute_total_cases(diagram));    
            
        fill_grid(grid,diagram);   
        write_name(grid,name); 
        return grid.render();
    }
}
void DiagramRenderer::fill_grid(
    OpenGrid& grid,
    const chord::database::Diagram& diagram)
{
    using Diagram = chord::database::Diagram;

    const auto& strings = diagram.strings();

    const std::size_t first = diagram.first_case();
    const std::size_t missing = (first > 1) ? first - 1 : 0;

    for (std::size_t s = 0; s < Diagram::STRING_COUNT; ++s)
    {
        uint8_t value = strings[s];

        auto string = static_cast<GridCore::STRING>(s);

        if (value == Diagram::MUTE)
        {
            grid.set_muted_string(string);
            continue;
        }
        if (value == Diagram::UNUSED)
        {
            continue;
        }
        // corde à vide
        if (value == 0)
        {
            grid.set_open_string(string);
            continue;
        }
        // corde frettée
        std::size_t fret = value;

        if (fret < first)
            continue;

        std::size_t case_number =
            (fret - first) + missing;

        grid.set_finger(
            string,
            case_number);
            //,GridCore::DOIGT::INDEX // ⚠️ temporaire (pas d’info doigt)
     
    }
}
void DiagramRenderer::fill_grid(
    DottedGrid& grid,
    const chord::database::Diagram& diagram)
{
}
void DiagramRenderer::fill_grid(
    GridCore& grid,
    const chord::database::Diagram& diagram)
{
#ifdef DEBUG
std::cout << __func__ << " called, is_open=" 
          << diagram.is_open() << "\n";
#endif

#ifdef DEBUG    
    std::cout << "base case pour ce diagram:" << static_cast<int>(diagram.base_case()) << "\n";
#endif


    using Diagram = chord::database::Diagram;

    //const std::size_t first = diagram.first_case();

    const auto& strings = diagram.strings();

    for (std::size_t s = 0; s < Diagram::STRING_COUNT; ++s)
    {
        uint8_t value = strings[s];

        // ignore cordes muettes / inutilisées
        if (value == Diagram::MUTE || value == Diagram::UNUSED)
            continue;

        // ⚠️ IMPORTANT : en movable, 0 = base_fret
        if (value == 0)
        {
            auto string = static_cast<GridCore::STRING>(s);

            //std::size_t case_number = 0; // 👉 première case affichée

            grid.set_finger(string, 0);
            continue;
        }

        auto string = static_cast<GridCore::STRING>(s);

        grid.set_finger(
            string,
            value);
    }


    write_fret(grid, diagram);    
}
void DiagramRenderer::write_fret(
    GridCore& grid,
    const chord::database::Diagram& diagram)
{
    if (diagram.base_case() > 0)
    {
        std::size_t pos = diagram.base_case();
        std::size_t row = 1; // première ligne utile

        grid.write_right(row, to_roman(pos));
    }       
}
void DiagramRenderer::write_name(GridCore& grid, const std::string& name)
{
    grid.add_title_row(name);
}
} // namespace