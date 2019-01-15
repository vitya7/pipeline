#pragma once

#include "any_range.hpp"

#include <iostream>

#include <algorithm>
#include <exception>

namespace pline
{
    struct debug_copy_tag {};

    template <class It1, class It2>
    struct copy_range
    {
        static void copy (any_range const&, any_range const&);
        static void copy (debug_copy_tag, any_range const&, any_range const&);
    };

    template <class It1, class It2>
    void
    copy_range <It1, It2> :: copy (any_range const& input, any_range const& output)
    {
        auto [i_begin, i_end] = input.unpack <It1> ();
        auto [o_begin, o_end] = output.unpack <It2> ();

        std::copy( i_begin, i_end, o_begin );
    }

    template <class It1, class It2>
    void
    copy_range <It1, It2> :: copy (debug_copy_tag, any_range const& input, any_range const& output)
    {
    try
    {
        copy( input, output );
    }
    catch (std::bad_any_cast const& ex)
    {
        std::cerr << "copy_range fail : " << ex.what() << "\n"
        << "expected : " << input.begin().type().name() << "  got : " << typeid(It1).name() << "\n"
        << "expected : " << output.begin().type().name() << "  got : " << typeid(It2).name() << "\n";

        throw ex;
    }
    }


}
