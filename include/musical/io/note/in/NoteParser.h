#pragma once

#include <optional>
#include <vector>
#include <string_view>

#include <musical/Core/note/Note.h>
#include <musical/Core/note/NoteFactory.h>
#include <musical/io/note/in/NoteLexer.h>

namespace musical::io::note
{

class NoteParser
{
public:
    /**
     * @brief Parse une séquence de tokens représentant une note.
     *
     * Grammaire supportée :
     *
     *     NOTE := NAME ACCIDENTAL?
     *
     * Retourne std::nullopt si la séquence est invalide.
     */
    static std::optional<musical::core::Note> 
    parse(const std::vector<token_t>& tokens);

private:

    static std::optional<char>
    to_name(std::string_view text);

    static std::optional<musical::core::Accidental>
    to_accidental(std::string_view text);
};

} // namespace musical::io::note