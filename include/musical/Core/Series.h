#ifndef __SERIES_H__
#define __SERIES_H__

#include <vector>
#include <functional>

#include <musical/Core/note/Note.h>

namespace musical
{
class Series {

public:
    using GeneratorFunc = std::function<Note(std::size_t)>;

    Series() = default;    

    Series(GeneratorFunc generator, std::size_t length) {
        generate(generator, length);
    }    

    void generate(GeneratorFunc generator, std::size_t length) {
        _notes.clear();
        _notes.reserve(length);        
        for (std::size_t i = 0; i < length; ++i) {
            _notes.push_back(generator(i));
        }
    }


    const Note& operator[](std::size_t index) const { return _notes.at(index); }
    std::size_t size() const { return _notes.size(); }

    void operator += (const Note& note) {
        _notes.push_back(note);
    }    

    const std::vector<Note>& notes() const { return _notes; }
        
private:
    std::vector<Note> _notes;
};

}

#endif