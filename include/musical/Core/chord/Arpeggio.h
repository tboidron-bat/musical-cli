
#include <vector>
#include <cstdint>
#include <string>

#include <musical/Core/chord/Chord.h>

namespace musical::core::chord {

class Note; // Forward declaration si tu as une classe Note

class Arpeggio {
public:
    // Constructeurs
    Arpeggio() = default;

    explicit Arpeggio(const Chord& chord);    
    //explicit Arpeggio(const std::vector<Note>& notes);


	//void operator+=(const Note&);


    //const std::vector<Note>& notes() const noexcept;



    //std::string to_string() const;

private:
    //std::vector<Note> _notes; // les notes qui forment l’arpège
};

}



