#include <musical/Core/scale/ScaleKeyed.h>
//#include <musical/Core/note/NoteService.h>

#include <musical/Core/scale/ScalePattern.h>

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

namespace musical::core {

ScaleKeyed& ScaleKeyed::operator+=(Note& note)
{
    _notes.push_back(note);
   return *this;    
}
ScaleKeyed& ScaleKeyed::operator+=(const Note& note)
{
    _notes.push_back(note); 
    return *this;
}

std::string ScaleKeyed::to_string () const
{
    std::ostringstream oss;
    for (const auto& n : _notes) {
        oss << musical::io::note::formatter::to_string(n) << " ";
    }
    return oss.str();
}

// ScaleKeyed ScaleKeyed::rotate(IntervalType interval) const
// {
//     ScaleKeyed gamme=*this;

//     if (static_cast<size_t>(interval) >= gamme._notes.size()) 
//         throw std::invalid_argument(
//            "ScaleKeyed::rotate(..):\n\tinterval trop grand");

//     Note note=gamme._notes[static_cast<int>(interval)];

//     /*faire une rotation de ALLNOTE */
//     auto it = std::find(gamme._notes.begin(), 
//                         gamme._notes.end(), note);
//     // Calcule la position de rotation
//     size_t pos = std::distance(gamme._notes.begin(), it);
//     // Effectue la rotation (en place)
//     std::rotate(gamme._notes.begin(), 
//                 gamme._notes.begin() + pos,
//                 gamme._notes.end()); 

//     return gamme;

// }
}