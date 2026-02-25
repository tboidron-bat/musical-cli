
#include <chord/ChordCommand.h>
#include <chord/Usage.h>

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

    // const std::string symbol = "C#m7b5";

    return 0;
}
