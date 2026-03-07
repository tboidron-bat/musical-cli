
#include <chord/ChordCommand.h>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    try
    {
        cli::chord::ChordCommand cmd;
        return cmd.run(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
