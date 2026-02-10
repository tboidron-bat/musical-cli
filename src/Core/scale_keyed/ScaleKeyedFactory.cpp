#include <musical/Core/ScaleKeyedFactory.h>
#include <musical/Core/note/NoteFactory.h>
#include <musical/Core/note/NoteService.h>

#include <algorithm>
#include <iostream>

using namespace musical;

 ScaleKeyed ScaleKeyedFactory::create(
 	const ScalePattern& scale, 
 	const Note& tonic, 
 	bool with_sharp)
 {
   ScaleKeyed gamme;

   using Acc = musical::Accidental;

   // Vérification de cohérence entre la tonique et la notation choisie
   if (tonic.GetPitch()._accid == Acc::FLAT && with_sharp)
        throw std::invalid_argument("[ScaleKeyedFactory::create] : Tonique bémol avec notation dièse");

   if (tonic.GetPitch()._accid == Acc::SHARP && !with_sharp)
        throw std::invalid_argument("[ScaleKeyedFactory::create] :Tonique dièse avec notation bémol");


    // Obtenir les 12 noms chromatiques selon la notation et avec tonique en premier  
    std::array<std::string,musical::CHROMATIC_NOTE_COUNT> chromatic_set = 
      get_chromatique_set(with_sharp,tonic);

   //size_t pos = NoteService::find(tonic);


  int j=0;
  for(int interval : scale.get_intervals()) 
  {
    gamme += NoteFactory::create(chromatic_set[j]);
    j = (j + interval) % CHROMATIC_NOTE_COUNT;
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

   int current_value = NoteService::chromatic_index(tonique);
   int start_value = current_value;   

    for (;;) {
      current_value = (current_value + static_cast<int>(interval)) % 12;

      if (current_value == start_value)
         break; // On revient à la tonique


      if(with_sharp){
         gamme += NoteFactory::create(current_value, tonique.GetPitch()._octave, 
          tonique.figure());         
      }
      else 
      {
        gamme += NoteFactory::create(current_value, tonique.GetPitch()._octave,
          tonique.figure(), false);
      }
   }

  //std::cout << "[ScaleKeyedFactory]\\" << gamme.to_string() << std::endl;
 	return gamme;
 }	 

std::array<std::string, CHROMATIC_NOTE_COUNT> ScaleKeyedFactory::get_chromatique_set(
  bool bsharp, 
  const Note& note_begin) 
{

  static std::array<std::string,musical::CHROMATIC_NOTE_COUNT> set_w_sharp =
    { "c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b" };

  static std::array<std::string,musical::CHROMATIC_NOTE_COUNT> set_w_flat =
    { "c", "db", "d", "eb", "e", "f", "gb", "g", "ab", "a", "bb", "b" };


  // Sélectionner l'ensemble de référence
  const auto& reference_set = bsharp ? set_w_sharp : set_w_flat;

  std::array<std::string, CHROMATIC_NOTE_COUNT> set = reference_set;

  auto it = std::find(set.begin(), set.end(), musical::NoteService::to_string(note_begin));

  if (it == set.end())
      throw std::runtime_error("[ScaleKeyedFactory::get_chromatique_set] Note not found in chromatic set: "
        + musical::NoteService::to_string(note_begin));

  size_t pos = std::distance(set.begin(), it);    

  std::rotate(set.begin(), set.begin() + pos, set.end());                
  return set;
} 
