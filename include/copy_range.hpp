#pragma once

#include "any_range.hpp"

#include <iostream>

#include <algorithm>
#include <exception>

namespace pline
{
    template <class T1, class T2>
    struct copy_range
    {
        static void copy (any_range input, any_range output);
    };

    template <class T1, class T2>
    void
    copy_range <T1, T2> :: copy (any_range input, any_range output)
    {
    try
    {
        auto i_begin = std::any_cast <T1> ( std::begin(input) );
        auto i_end   = std::any_cast <T1> ( std::end(input) );

        auto o_begin = std::any_cast <T2> ( std::begin(output) );

        std::copy(i_begin, i_end, o_begin);
    }
    catch (std::bad_any_cast const& ex)
    {
        std::cerr << "copy_range fail : " << ex.what() << std::endl;
    }
    };
}
