#include <musical/io/guitar/unicode/DiagramRenderer.h>

#include <musical/io/guitar/unicode/OpenGrid.h>
#include <musical/io/guitar/unicode/DottedGrid.h>

#include <iostream> //DEBUG

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
    const chord::database::Diagram& diagram)
{
    //Diagram d'accord ouvert?
    if(diagram.is_open())
    {
        std::size_t first = diagram.first_case();

        if(first < 5)
        {
            OpenGrid grid(
                chord::database::Diagram::STRING_COUNT,
                compute_total_cases(diagram));    

            fill_grid(grid,diagram);    
            return grid.render();

        }            
        else
        {
            DottedGrid grid(
                chord::database::Diagram::STRING_COUNT,
                compute_total_cases(diagram));    

            fill_grid(grid,diagram);    
            return grid.render();

        }        
    }
    else
    {
            GridCore grid(
                chord::database::Diagram::STRING_COUNT,
                compute_total_cases(diagram));    

            fill_grid(grid,diagram);    
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
    using Diagram = chord::database::Diagram;

    const std::size_t first = diagram.first_case();

    //if (first > 1)
        grid.extend_right();

    const auto& strings = diagram.strings();
    const std::size_t missing = (first > 1) ? first - 1 : 0;

    for (std::size_t s = 0; s < Diagram::STRING_COUNT; ++s)
    {
        uint8_t value = strings[s];

        // ignore cordes muettes / inutilisées
        if (value == Diagram::MUTE || value == Diagram::UNUSED)
            continue;

        // ⚠️ IMPORTANT : en movable, pas de "open string"
        if (value == 0)
            continue;

        auto string = static_cast<GridCore::STRING>(s);

        std::size_t fret = value;

        if (fret < first)
            continue;

        std::size_t case_number =
            (fret - first) + missing;

        grid.set_finger(
            string,
            case_number);
            //,GridCore::DOIGT::INDEX // temporaire
        
    }

    // if (first > 1)
    // {
    // 🔥 AJOUT : annotation position
        std::size_t pos = diagram.first_case() + diagram.base_case();
        std::size_t row = 1; // première ligne utile

        grid.write_right(row, to_roman(pos));
    //}       
    
#ifdef DEBUG    
    std::cout << "base case pour ce diagram:" << static_cast<int>(diagram.base_case()) << "\n";
#endif

}
} // namespace