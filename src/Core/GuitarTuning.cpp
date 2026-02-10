#include <musical/Core/GuitarTuning.h>
#include <musical/Core/note/NoteFactory.h>
#include <musical/Core/note/NoteService.h>
#include <stdexcept>

namespace musical {

GuitarTuning GuitarTuning::standard() {
    
    return GuitarTuning({
        NoteFactory::create('e', musical::Accidental::NONE, 2), // corde 6 - E2
        NoteFactory::create('a', musical::Accidental::NONE, 2), // corde 5 - A2
        NoteFactory::create('d', musical::Accidental::NONE, 3), // corde 4 - D3
        NoteFactory::create('g', musical::Accidental::NONE, 3), // corde 3 - G3
        NoteFactory::create('b', musical::Accidental::NONE, 3), // corde 2 - B3
        NoteFactory::create('e', musical::Accidental::NONE, 4)  // corde 1 - E4
    });
}
}
