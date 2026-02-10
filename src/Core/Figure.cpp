#include <musical/Core/Figure.h>

using namespace musical;


unsigned int Figure::duration() const
{
    unsigned int base = static_cast<uint16_t>(_value);
    unsigned int total = base;

    unsigned int dot_value = base / 2;

    for (uint8_t i = 0; i < _dots; ++i) {
        total += dot_value;
        dot_value /= 2;
    }

    return total;
}


std::string Figure::to_string() const {

    std::string result;

    switch (_value) {
        case FigureType::LONGA:         result = "longa"; break;
        case FigureType::BREVE:         result = "breve"; break;
        case FigureType::WHOLE:         result = "whole"; break;
        case FigureType::HALF:          result = "half"; break;
        case FigureType::QUARTER:       result = "quarter"; break;
        case FigureType::EIGHTH:        result = "eighth"; break;
        case FigureType::SIXTEENTH:     result = "sixteenth"; break;
        case FigureType::THIRTY_SECOND: result = "thirty-second"; break;
        case FigureType::SIXTY_FOURTH:  result = "sixty-fourth"; break;
        default:                        result = "unknown"; break;
    }

    for (uint8_t i = 0; i < _dots; ++i)
        result += ".";

    return result;
}

//STATIC
Figure Figure::from_mei(const std::string& dur_str, const std::string& dots_str)
{
    FigureType figure_type = FigureType::QUARTER; // valeur par défaut

    try {
        int dur = std::stoi(dur_str);
        switch (dur) {
            case 1:  figure_type = FigureType::WHOLE;       break;  // ronde
            case 2:  figure_type = FigureType::HALF;        break;  // blanche
            case 4:  figure_type = FigureType::QUARTER;     break;  // noire
            case 8:  figure_type = FigureType::EIGHTH;      break;  // croche
            case 16: figure_type = FigureType::SIXTEENTH;   break;  // double croche
            case 32: figure_type = FigureType::THIRTY_SECOND; break; // triple croche
            case 64: figure_type = FigureType::SIXTY_FOURTH; break;  // quadruple croche
            default: figure_type = FigureType::QUARTER;     break;
        }
    } catch (...) {
        figure_type = FigureType::QUARTER;
    }

    uint8_t dots = 0;
    try {
        dots = static_cast<uint8_t>(std::stoi(dots_str));
    } catch (...) {
        dots = 0;
    }

    return Figure(figure_type, dots);
}



