#include <musical/Core/scale/ScaleKeyedFactory.h>
#include <musical/Core/note/Factory.h>

#include <algorithm>
#include <iostream>
#include <array>


namespace musical::core::scale {


ScaleKeyed ScaleKeyedFactory::create(
    const ScalePattern& scale, 
    const Note& tonic, 
    bool with_sharp)
{
    ScaleKeyed gamme;

    using Acc = musical::core::Note::Accidental;

    if (tonic.accidental() == Acc::FLAT && with_sharp)
        throw std::invalid_argument("Tonique bémol avec notation dièse");

    if (tonic.accidental() == Acc::SHARP && !with_sharp)
        throw std::invalid_argument("Tonique dièse avec notation bémol");

    auto pref = with_sharp
        ? note::Factory::AlterationPreference::SHARP
        : note::Factory::AlterationPreference::FLAT;

    int j = tonic.chromatic_index();

    for (int interval : scale.get_intervals())
    {
        gamme += note::Factory::create(
            j,
            tonic.octave(),
            tonic.figure(),
            pref
        );

        j = (j + interval) % 12;
    }

    return gamme;
}


ScaleKeyed ScaleKeyedFactory::create(
    IntervalType interval, 
    const Note& tonique, 
    bool with_sharp)
{
    ScaleKeyed gamme;

    gamme += tonique;

    auto pref = with_sharp
        ? note::Factory::AlterationPreference::SHARP
        : note::Factory::AlterationPreference::FLAT;

    int current_value = tonique.chromatic_index();
    int start_value   = current_value;

    for (;;)
    {
        current_value = (current_value + static_cast<int>(interval)) % 12;

        if (current_value == start_value)
            break;

        gamme += note::Factory::create(
            current_value,
            tonique.octave(),
            tonique.figure(),
            pref
        );
    }

    return gamme;
}
}


//  ScaleKeyed ScaleKeyedFactory::create(
//  	const ScalePattern& scale, 
//  	const Note& tonic, 
//  	bool with_sharp)
//  {
//    ScaleKeyed gamme;

//    using Acc = musical::core::Note::Accidental;

//    // Vérification de cohérence entre la tonique et la notation choisie
//    if (tonic.accidental() == Acc::FLAT && with_sharp)
//         throw std::invalid_argument("[ScaleKeyedFactory::create] : Tonique bémol avec notation dièse");

//    if (tonic.accidental() == Acc::SHARP && !with_sharp)
//         throw std::invalid_argument("[ScaleKeyedFactory::create] :Tonique dièse avec notation bémol");


//     // Obtenir les 12 noms chromatiques selon la notation et avec tonique en premier  
//     std::array<std::string,12> chromatic_set = 
//       get_chromatique_set(with_sharp,tonic);

//    //size_t pos = NoteService::find(tonic);


//   int j=0;
//   for(int interval : scale.get_intervals()) 
//   {
//     //gamme += musical::core::note::Factory::create(chromatic_set[j]);
//       gamme += note::Factory::create(
//           j,
//           tonic.octave(),
//           tonic.figure(),
//           with_sharp 
//               ? note::Factory::AlterationPreference::SHARP
//               : note::Factory::AlterationPreference::FLAT
//       );


//     j = (j + interval) % 12;
//   }    
//   return gamme;
// }

// ScaleKeyed ScaleKeyedFactory::create(
//  	IntervalType interval, 
//  	const Note& tonique, 
//  	bool with_sharp)
// {
//  	ScaleKeyed gamme;

//  	gamme += tonique;

//    int current_value = tonique.chromatic_index();
//    int start_value = current_value;   

//     for (;;) {
//       current_value = (current_value + static_cast<int>(interval)) % 12;

//       if (current_value == start_value)
//          break; // On revient à la tonique


//       if(with_sharp){
//          gamme += note::Factory::create(current_value, tonique.octave(), 
//           tonique.figure());         
//       }
//       else 
//       {
//         gamme += note::Factory::create(current_value, tonique.octave(),
//           tonique.figure(), false);
//       }
//    }

//   //std::cout << "[ScaleKeyedFactory]\\" << gamme.to_string() << std::endl;
//  	return gamme;
//  }	 

// std::array<std::string, 12> ScaleKeyedFactory::get_chromatique_set(
//   bool bsharp, 
//   const Note& note_begin) 
// {

//   static std::array<std::string, 12> set_w_sharp =
//     { "c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b" };

//   static std::array<std::string,12> set_w_flat =
//     { "c", "db", "d", "eb", "e", "f", "gb", "g", "ab", "a", "bb", "b" };


//   // Sélectionner l'ensemble de référence
//   const auto& reference_set = bsharp ? set_w_sharp : set_w_flat;

//   std::array<std::string, 12> set = reference_set;

//   auto it = std::find(set.begin(), set.end(), musical::io::note::formatter::to_string(note_begin));

//   if (it == set.end())
//       throw std::runtime_error("[ScaleKeyedFactory::get_chromatique_set] Note not found in chromatic set: "
//         + musical::musical::io::note::formatter::to_string(note_begin));

//   size_t pos = std::distance(set.begin(), it);    

//   std::rotate(set.begin(), set.begin() + pos, set.end());                
//   return set;
// } 
// }