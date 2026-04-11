#pragma once

#include <Option.h>

namespace cli::chord
{
    class random_option : public cli::command::Option
    {
    public:
        random_option(cli::Command&);

        int execute() const override;
    private:
        
        void add_open_diagram() const;
        void add_movable_diagram() const;

        void render();
    };

}