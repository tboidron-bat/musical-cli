#include <musical/Core/Figure.h>
#include <string>
#include <stdexcept>

namespace musical::io::mei::figure
{

core::Figure 
parse(const std::string& dur_str,
      const std::string& dots_str)
{
    using Type = core::Figure::Type;
    using Dot  = core::Figure::Dot;

    Type figure_type = Type::QUARTER; // défaut

    try
    {
        int dur = std::stoi(dur_str);

        switch (dur)
        {
            case 1:  figure_type = Type::WHOLE;          break;
            case 2:  figure_type = Type::HALF;           break;
            case 4:  figure_type = Type::QUARTER;        break;
            case 8:  figure_type = Type::EIGHTH;         break;
            case 16: figure_type = Type::SIXTEENTH;      break;
            case 32: figure_type = Type::THIRTY_SECOND;  break;
            case 64: figure_type = Type::SIXTY_FOURTH;   break;
            default: break; // garde QUARTER
        }
    }
    catch (const std::invalid_argument&)
    {
        // dur_str is not a valid integer → fallback to QUARTER
    }
    catch (const std::out_of_range&)
    {
        // integer value too large/small for int → fallback to QUARTER
    }

    Dot dots = Dot::NONE;

    try
    {
        int d = std::stoi(dots_str);

        switch (d)
        {
            case 1: dots = Dot::ONE;    break;
            case 2: dots = Dot::TWO;    break;
            case 3: dots = Dot::THREE;  break;
            default: break;
        }
    }
    catch (const std::invalid_argument&)
    {
        // invalid MEI dots value → fallback to NONE             
    }
    catch (const std::out_of_range&)
    {
        // value outside int range → fallback to NONE
    }

    return core::Figure(figure_type, dots);
}

}
