#include <command/chord/ChordCommand.h>
#include <Option.h>
#include <stream_option.h>

#include <command/chord/version_option.h>
#include <command/chord/help_option.h>
#include <command/chord/diagram.h>
#include <command/chord/random_option.h>
#include <command/chord/dumpdb.h>
#include <command/chord/play_option.h>
#include <command/chord/difficulty_option.h>
#include <command/chord/tuning_option.h>

#include <command/chord/chord_parser.h>

//#define DEBUG

namespace cli::chord
{
ChordCommand::ChordCommand()
{
    _options.emplace_back(std::make_unique<version_option>(*this));
    _options.emplace_back(std::make_unique<help_option>(*this));
    _options.emplace_back(std::make_unique<command::chord::dumpdb>(*this));
    _options.emplace_back(std::make_unique<random_option>(*this));
    _options.emplace_back(std::make_unique<command::chord::diagram>(*this));
    _options.emplace_back(std::make_unique<play_option>(*this));
    _options.emplace_back(std::make_unique<difficulty_option>(*this));
    _options.emplace_back(std::make_unique<tuning_option>(*this));
}
int ChordCommand::run(int argc, char** argv)
{
    if(argc < 2)
    {
        print_usage();
        return 1;
    }

    _args.clear();

    for(int i = 0; i < argc; ++i)
        _args.emplace_back(argv[i]);

    for (auto& opt : _options)
        opt->parse(argc, argv);

    if(get_option<version_option>()->execute() == EXIT_SUCCESS)
        return EXIT_SUCCESS;

    if(get_option<help_option>()->execute() == EXIT_SUCCESS)
        return EXIT_SUCCESS;

    if(get_option<command::chord::dumpdb>()->execute() == EXIT_SUCCESS)
        return EXIT_SUCCESS;

    bool b = get_option<random_option>()->execute() == EXIT_SUCCESS;

     if(!b)
    {
        cli::command::chord::chord_parser::add_entries(*this);    
    }

    if(entries().empty())    
    {
        std::cerr << "Chord symbol required\n";        
        return EXIT_FAILURE;
    }            


    get_option<command::chord::diagram>()->execute();

    //cli::command::chord::render(_entries);

    get_option<play_option>()->execute();

    return EXIT_SUCCESS;
}
std::string ChordCommand::input_string() const
{
    std::string cmd_line;

    for(int i = 1; i < _args.size(); ++i)
    {
        cmd_line += _args[i];
        cmd_line += ' ';
    }

    if(!cmd_line.empty())
        cmd_line.pop_back();

#ifdef DEBUG
    std::cout << "command line : <" << cmd_line << ">\n";    
#endif

    return cmd_line;
}
void ChordCommand::print_name() const
{
    std::cout << "Chord CLI — version 0.5.0";
}
void ChordCommand::print_usage() const 
{
    std::cout << "Usage:\n";
    std::cout << "\tchord [options] <symbol>\n";
    std::cout << "Try:\n";
    std::cout << "\tchord --help\n";
}        

void ChordCommand::print_help() const
{
    std::cout << "Options:\n";

    for (const auto& opt : _options)
        std::cout << *opt;
}
} // namespace cli::chord