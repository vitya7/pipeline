#pragma once

#include "any_range.hpp"

#include <iostream>

#include <algorithm>
#include <exception>

namespace pline
{
    template <class It1, class It2>
    struct copy_range
    {
        static void copy (any_range input, any_range output);
    };

    template <class It1, class It2>
    void
    copy_range <It1, It2> :: copy (any_range input, any_range output)
    {
    try
    {
        auto [i_begin, i_end] = input.unpack <It1> ();
        auto [o_begin, o_end] = output.unpack <It2> ();

        std::copy(i_begin, i_end, o_begin);
    }
    catch (std::bad_any_cast const& ex)
    {
        std::cerr << "copy_range fail : " << ex.what() << std::endl;
    }
    };

}
