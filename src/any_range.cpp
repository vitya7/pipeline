#include "any_range.hpp"

namespace pline
{

    std::any
    any_range::
    begin () const
    {
        return m_begin;
    }

    std::any
    any_range::
    end () const
    {
        return m_end;
    }

    std::type_info const&
    any_range::
    type () const
    {
        return m_begin.type();
    }

}
