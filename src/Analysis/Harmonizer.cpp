#include <musical/Analysis/Harmonizer.h>

#include <iostream>

using namespace musical;		
using namespace musical::Analysis;

Harmonizer::Harmonizer(HarmoIntervalType h,ChordClassType c)
:_harm_intvl(h),_chord_class(c)
{}

std::vector<Chord> Harmonizer::harmonize(const ScaleKeyed&gamme_ref)
{
	std::vector<Chord> chords;

	//std::cout << "[Harmonizer]\\harmonizing: " << gamme_ref.to_string() << std::endl;	

	ScaleKeyed gamme=gamme_ref;

	for(auto note : gamme_ref)
	{
		Chord chord=ChordFactory::create(
			note,
			gamme_ref,
			_chord_class);		

		chords.push_back(chord);
	}
	return chords;
}