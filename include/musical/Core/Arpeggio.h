#ifndef __ARPEGGIO_H__
#define __ARPEGGIO_H__

#include <vector>
#include <cstdint>
#include <string>

namespace musical {

class Note; // Forward declaration si tu as une classe Note

class Arpeggio {
public:
    // Constructeurs
    Arpeggio() = default;
    explicit Arpeggio(const std::vector<Note>& notes);


	void operator+=(const Note&);

    // Obtenir toutes les notes
    const std::vector<Note>& notes() const;


    std::string to_string() const;

private:
    std::vector<Note> _notes; // les notes qui forment l’arpège
};

} // namespace musical

#endif // __ARPEGGIO_H__

