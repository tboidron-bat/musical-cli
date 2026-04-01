#ifndef __CADENCE_H__
#define __CADENCE_H__

#include <string>
#include <vector>

/*Satriani dans Circle: i -> vi dim */

namespace musical
{
    enum class CadenceType {
        Perfect,    // V - I
        Plagal,     // IV - I
        Deceptive,  // V - vi
        Half,       // I - V
        Custom
    };


class Cadence {
public:

    Cadence(CadenceType type = CadenceType::Perfect);
    Cadence(CadenceType type, const std::vector<std::string>& progression);

    const std::vector<std::string>& getProgression() const;
    std::string toString() const;
    CadenceType getType() const;

private:
    CadenceType _type;
    std::vector<std::string> _chords;
};

}

#endif // __CADENCE_H__
