#include <musical/Core/note/Note.h>
#include <musical/Core/note/NoteFactory.h>


int main()
{
    auto c4 = musical::core::note::Factory::create(
        'C', musical::core::Accidental::NONE);

    // chromatic index doit être stable
    if (static_cast<int>(c4.tone()) != 0)
        return 1;

    return 0;
}
