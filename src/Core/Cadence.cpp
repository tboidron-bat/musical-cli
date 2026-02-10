#include <musical/Core/Cadence.h>

using namespace musical;

Cadence::Cadence(CadenceType type)
    : _type(type)
{
    switch (type) {
        case CadenceType::Perfect:
            _chords = {"V", "I"};
            break;
        case CadenceType::Plagal:
            _chords = {"IV", "I"};
            break;
        case CadenceType::Deceptive:
            _chords = {"V", "vi"};
            break;
        case CadenceType::Half:
            _chords = {"I", "V"};
            break;
        default:
            _chords = {};
            break;
    }
}

Cadence::Cadence(CadenceType type, const std::vector<std::string>& progression)
    : _type(type), _chords(progression)
{
}

const std::vector<std::string>& Cadence::getProgression() const {
    return _chords;
}

std::string Cadence::toString() const {
    std::string result;
    for (size_t i = 0; i < _chords.size(); ++i) {
        result += _chords[i];
        if (i != _chords.size() - 1)
            result += " - ";
    }
    return result;
}

CadenceType Cadence::getType() const {
    return _type;
}
