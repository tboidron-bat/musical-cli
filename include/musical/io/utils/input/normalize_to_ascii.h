#pragma once

#include <string>
#include <string_view>

namespace musical::io
{

// UTF-8 → ASCII simplifié (sans modification de casse)
// - accents latins supprimés
// - ♯ → #
// - ♭ → b
// - 𝄪 → ##
// - 𝄫 → bb
// - ♮ ignoré
std::string
normalize_to_ascii(std::string_view input);

}