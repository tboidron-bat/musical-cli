#include <musical/Core/chord/Chord.h>
#include <musical/Core/Figure.h>

#include <stdexcept>

using namespace musical;

const Figure& Chord::figure() const
{
    return _tonic.figure();
}

void Chord::set_figure(const Figure& f)
{
    _tonic.set_figure(f);
}
std::size_t Chord::size() const 
{ 
    return 1 + _intervals.size(); 
}
