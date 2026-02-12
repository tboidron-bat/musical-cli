#include <musical/Core/note/Note.h>
#include <musical/Core/note/Factory.h>


int main()
{
    auto c4 = musical::core::note::Factory::create('C', 4);

    // chromatic index doit être stable
    if (c4.chromatic_index() != 0)
        return 1;

    return 0;
}
