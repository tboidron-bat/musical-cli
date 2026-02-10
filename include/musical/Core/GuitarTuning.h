#pragma once

#include <vector>
#include <optional>

namespace musical
{
    class Note;
}

namespace musical {

class GuitarTuning {
public:
    /**
     * @brief Crée un accordage depuis une liste de notes (de la corde 6 à la corde 1)
     */
    GuitarTuning(const std::vector<Note>& strings)
        : _strings(strings) {}

    static GuitarTuning standard();

private:
    std::vector<Note> _strings; // corde 6 à 1
};

}
