#pragma once

#include <vector>
#include <cstdint>

#include <musical/core/Pitch.h>

namespace musical::core::scale {

class ScaleKeyed {

    friend class ScaleKeyedFactory;

public:

    // ------------------------------------------------------------
    // Types d'itérateurs
    // ------------------------------------------------------------
    using iterator = std::vector<Pitch>::iterator;
    using const_iterator = std::vector<Pitch>::const_iterator;

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
    Pitch& operator[](std::size_t index) { return _pitches[index]; }

    const Pitch& operator[](std::size_t index) const { return _pitches[index]; }

    // ------------------------------------------------------------
    // Ajout d’un pitch
    // ------------------------------------------------------------
    ScaleKeyed& operator+=(const Pitch& pitch)
    {
        _pitches.push_back(pitch);
        return *this;
    }

    void add(const Pitch& pitch)
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
        if (_pitches.size() > n)
            _pitches.resize(n);
    }

private:
    std::vector<Pitch> _pitches;
};

} // namespace musical::core::scale