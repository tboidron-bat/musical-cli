#include <musical/Core/Figure.h>

#include <string>

namespace musical::io::formatter
{

std::string to_string(const core::Figure& figure) {

    using Type = core::Figure::Type;

    std::string result;

    switch (figure.type()) {

        case Type::LONGA:         result = "longa"; break;
        case Type::BREVE:         result = "breve"; break;
        case Type::WHOLE:         result = "whole"; break;
        case Type::HALF:          result = "half"; break;
        case Type::QUARTER:       result = "quarter"; break;
        case Type::EIGHTH:        result = "eighth"; break;
        case Type::SIXTEENTH:     result = "sixteenth"; break;
        case Type::THIRTY_SECOND: result = "thirty-second"; break;
        case Type::SIXTY_FOURTH:  result = "sixty-fourth"; break;
        default:                        result = "unknown"; break;
    }

    for (uint8_t i = 0; i < static_cast<uint8_t>(figure.dot_count()); ++i)
        result += ".";


    return result;
}
}