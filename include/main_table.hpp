#pragma once

#include "copy_overload_table.hpp"

namespace pline
{
    class main_table : public copy_overload_table
    {
    private:

            main_table ();

            main_table (main_table const&) = default;
            main_table (main_table &&) = default;

    public:

        static main_table const& get ();

    };

}
