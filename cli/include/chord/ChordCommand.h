#pragma once

#include <Command.h>
#include <vector>

namespace cli::chord
{

class ChordCommand : public cli::Command
{
public:
    const std::vector<cli::option_t>& options() const override;

    int run(int argc, char** argv) override;
};

}
