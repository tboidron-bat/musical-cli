
#include <chord/Usage.h>
#include <chord/ChordCommand.h>
#include <iostream>

namespace cli::chord
{

void print_usage()
{
    std::cout <<
    "Usage:\n"
    "  chord [options] <symbol>\n\n"

    "Description:\n"
    "  Analyse et affiche des informations sur un accord musical.\n\n"

    "Arguments:\n"
    "  <symbol>    Symbole de l'accord (ex: Cmaj7, F#m7b5, Ré, Bb7, C/G)\n\n"

    "Examples:\n"
    "  chord Cmaj7\n"
    "  chord F#m7b5\n"
    "  chord Ré\n"
    "  chord Bb7b9\n"
    "  chord Cmaj7/G\n\n"

    "Try:\n"
    "  chord --help   for detailed options\n";
}
void print_help()
{
    print_usage();

    std::cout <<
    "\nOptions:\n"

    "  -d, --diagram [position]\n"
    "      Show guitar chord diagram.\n"
    "      If <position> (1–5) is provided, show only that CAGED position.\n\n"

    "      --difficulty <n>\n"
    "      Filter diagrams by difficulty level (1–3).\n"
    "      Requires --diagram.\n\n"

    "      --tuning <name>\n"
    "      Guitar tuning to use for diagram rendering.\n"
    "      Supported tunings:\n"
    "          standard   (E A D G B E)\n"
    "          dropd      (D A D G B E)\n"
    "          dadgad     (D A D G A D)\n"
    "          openG      (D G D G B D)\n"
    "          openD      (D A D F# A D)\n"
    "      Default: standard.\n"
    "      Requires --diagram.\n\n"

    "  -h, --help\n"
    "      Show this help message.\n\n"

    "Examples:\n"
    "  chord Cmaj7\n"
    "  chord F#m7b5\n"
    "  chord Ré\n"
    "  chord Cmaj7/G\n\n"

    "  chord Cmaj7 --diagram\n"
    "  chord Cmaj7 --diagram 3\n"
    "  chord Cmaj7 --diagram 3 --difficulty 2\n"
    "  chord Cmaj7 --diagram --tuning dropd\n"
    "  chord Cmaj7 --diagram 2 --tuning dadgad\n\n";
}
}