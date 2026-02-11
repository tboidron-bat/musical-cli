//#include <musical/Core/note/NoteService.h>

//#include <musical/Core/note/Factory.h>

namespace musical::core {


// size_t musical::NoteService::find(const musical::core::Note& note)
// {
//     using Acc = musical::core::Note::Accidental;

//     const auto& chromatic_set = 
//         (note.accidental() == Acc::NONE || note.accidental() == Acc::SHARP)
//         ? all_with_sharp()
//         : all_with_flat();

//     auto it = std::find(chromatic_set.begin(), chromatic_set.end(), musical::io::note::foramtter::to_string(note));

//     if (it == chromatic_set.end())
//         throw std::runtime_error("[find] Note not found in chromatic set: " + musical::io::note::foramtter::to_string(note));

//     return std::distance(chromatic_set.begin(), it);
// }


    //std::cout << "[musical::NoteService]\\(to_latin)" << "s=" << s  << std::endl;    

    //return s;
//}
// core::Note musical::NoteService::sharp_to_flat(const core::Note&note)
// {
//    constexpr std::array<char, 7> NOTE_NAMES_SAXON =  
//         { 'c', 'd', 'e', 'f', 'g', 'a', 'b' };


//     if(note.accidental() != musical::core::Note::Accidental::SHARP)
//         return note;

//     // Trouver l’index de la note dans la liste NAMES
//     auto it = NOTE_NAMES_SAXON.begin();
//     while (it != NOTE_NAMES_SAXON.end() && *it != note.name())
//         ++it;

//     if(it==NOTE_NAMES_SAXON.end())
//         throw std::runtime_error("[musical::NoteService::sharp_to_flate] Invalid note name");    

//     size_t index = std::distance(NOTE_NAMES_SAXON.begin(), it);        

//     // Avancer d’un demi-ton (note suivante)
//     size_t new_index = (index + 1) % NOTE_NAMES_SAXON.size(); // boucle cyclique


//     char new_name = NOTE_NAMES_SAXON[new_index];        

//     return NoteFactory::create(
//         new_name,musical::core::Note::Accidental::FLAT,note.octave(),note.figure());
// }

}