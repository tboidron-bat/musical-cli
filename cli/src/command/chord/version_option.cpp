#include <command/chord/version_option.h>
#include <command/chord/ChordCommand.h>

#include <iostream>

namespace cli::chord
{
version_option::version_option(cli::Command&cmd)
: 
command::Option(cmd, "version", "v", "Show program version")
{
}    
int version_option::execute() const
{
    if(!_enabled)
        return EXIT_FAILURE;


std::cout << R"(
╔════════════════════════════════════════════════════════════╗
║                                                            ║
║ ██        ██████╗██╗  ██╗ ██████╗ ██████╗ ██████╗          ║
║   ██     ██╔════╝██║  ██║██╔═══██╗██╔══██╗██╔══██╗         ║
║     ██   ██║     ███████║██║   ██║██████╔╝██║  ██║         ║
║   ██     ██║     ██╔══██║██║   ██║██╔══██╗██║  ██║         ║
║ ██       ╚██████╗██║  ██║╚██████╔╝██║  ██║██████╔╝         ║
║           ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝          ║
║                                                            ║
║                    Guitar Chord CLI                        ║
║                      version 0.4.1                         ║
║                   github.com/tboidron                      ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝)";

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
}