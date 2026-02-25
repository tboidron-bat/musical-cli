#pragma once

#include <vector>
#include <cstdint>
#include <musical/Core/pitch_t.h>

namespace musical::core::scale {

class ScaleKeyed {

    friend class ScaleKeyedFactory;

public:

    // ------------------------------------------------------------
    // Types d'itérateurs
    // ------------------------------------------------------------
    using iterator = std::vector<pitch_t>::iterator;
    using const_iterator = std::vector<pitch_t>::const_iterator;

    // ------------------------------------------------------------
    // Itérateurs
    // ------------------------------------------------------------
    iterator begin() { return _pitches.begin(); }
    iterator end()   { return _pitches.end(); }

    const_iterator begin() const { return _pitches.begin(); }
    const_iterator end()   const { return _pitches.end(); }

    // ------------------------------------------------------------
    // Accès par index
    // ------------------------------------------------------------
    pitch_t& operator[](std::size_t index) { return _pitches[index]; }

    const pitch_t& operator[](std::size_t index) const { return _pitches[index]; }

    // ------------------------------------------------------------
    // Ajout d’un pitch
    // ------------------------------------------------------------
    ScaleKeyed& operator+=(const pitch_t& pitch);

    void add(const pitch_t& pitch)
    {
        _pitches.push_back(pitch);
    }

    // ------------------------------------------------------------
    // Suppression du dernier élément
    // ------------------------------------------------------------
    void pop_back()
    {
        if (!_pitches.empty())
            _pitches.pop_back();
    }

    // ------------------------------------------------------------
    // Taille
    // ------------------------------------------------------------
    std::size_t size() const noexcept
    {
        return _pitches.size();
    }

    void truncate(std::size_t n)
    {
        while (_pitches.size() > n)
            _pitches.pop_back();
    }

private:
    std::vector<pitch_t> _pitches;
};

} // namespace musical::core::scale