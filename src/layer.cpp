#include "layer.hpp"

namespace pline
{

    any_range
    layer::
    input ()
    {
        return m_self -> input();
    }

    any_range
    layer::
    input () const
    {
        return m_self -> const_input();
    }

    any_range
    layer::
    output ()
    {
        return m_self -> output();
    }

    any_range
    layer::
    output () const
    {
        return m_self -> const_output();
    }

    void
    layer::
    execute ()
    {
        m_self -> execute();
    }

    bool
    layer::
    must_copy_input ()
    {
        return m_must_copy_input;
    }

    void
    layer::
    must_copy_input (bool x)
    {
        m_must_copy_input = x;
    }
}
