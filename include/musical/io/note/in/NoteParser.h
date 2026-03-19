#pragma once

#include <optional>
#include <vector>

#include <musical/Core/pitch_t.h>
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
        static std::optional<musical::core::pitch_t> 
        parse(const std::vector<token_t>& tokens);

    private:

        static std::optional<musical::core::NoteName>
        to_name(std::string_view text);

        static std::optional<musical::core::Accidental>
        to_accidental(std::string_view text);
    };

} // namespace musical::io::note