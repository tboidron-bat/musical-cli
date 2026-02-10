#include <musical/Core/note/Note.h>
#include <musical/Core/note/NoteService.h>
#include <musical/Core/note/NoteFactory.h>


int main()
{
    auto c4 = musical::NoteFactory::create("C", 4);

    // chromatic index doit être stable
    if (musical::NoteService::chromatic_index(c4) != 0)
        return 1;

    return 0;
}
