#pragma once

#include <iostream>

#include <any>
#include <iterator>

namespace pline
{
    class any_range
    {
    public:

        template <class It>
        any_range (It b, It e)
            : m_begin ( std::move(b) )
            , m_end   ( std::move(e) )
        { }

        std::any begin () const;
        std::any end () const;

    private:

        std::any m_begin;
        std::any m_end;
    };

    template <class T>
    any_range make_any_range (T && x)
    {
        return { std::begin(x), std::end(x) };
    }
}
