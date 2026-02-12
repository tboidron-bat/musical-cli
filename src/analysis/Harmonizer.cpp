#include <musical/analysis/Harmonizer.h>

#include <iostream>

using namespace musical;		
using namespace musical::analysis;

Harmonizer::Harmonizer(
	HarmoIntervalType h,
	core::ChordClassType c)
	:
		_harm_intvl(h),
		_chord_class(c)
{}

std::vector<core::Chord> 
Harmonizer::harmonize(const core::scale::ScaleKeyed&gamme_ref)
{
	std::vector<core::Chord> chords;

	//std::cout << "[Harmonizer]\\harmonizing: " << gamme_ref.to_string() << std::endl;	

	core::scale::ScaleKeyed gamme=gamme_ref;

	for(auto note : gamme_ref)
	{
		core::Chord chord=core::chord::Factory::create(
			note,
			gamme_ref,
			_chord_class);		

		chords.push_back(chord);
	}
	return chords;
}