#pragma once

#include "any_range.hpp"

namespace pline
{
    class layer_concept
    {
    public :

        virtual ~layer_concept () = default;

        virtual any_range       input  ()       = 0;
        virtual any_range const_input  () const = 0;

        virtual any_range       output ()       = 0;
        virtual any_range const_output () const = 0;

        virtual void execute () = 0;
    };
}
