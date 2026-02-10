#include <musical/Core/Arpeggio.h>
#include <musical/Core/note/Note.h> 
#include <musical/Core/note/NoteService.h> 

#include <sstream>

using namespace musical;

// Constructeur avec liste de notes
Arpeggio::Arpeggio(const std::vector<Note>& notes)
    : _notes(notes)
{
}
void Arpeggio::operator+=(const Note& note)
{
    _notes.push_back(note);
}

// Accès aux notes
const std::vector<Note>& Arpeggio::notes() const
{
    return _notes;
}

// Conversion en texte (ex: "c e g")
std::string Arpeggio::to_string() const
{
    std::ostringstream oss;
    for (const auto& note : _notes) {
        oss << musical::NoteService::to_string(note) << " ";
    }
    return oss.str();
}