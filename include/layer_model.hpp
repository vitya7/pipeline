#pragma once

#include "layer_concept.hpp"

namespace pline
{
    template <class T>
    class layer_model : public layer_concept
    {
    public :

        layer_model (T x);

        any_range       input ()       override;
        any_range const_input () const override;

        any_range       output ()       override;
        any_range const_output () const override;

        void execute () override;

        T &            data ();
        T const& const_data () const;

    private :

        T m_data;
    };

    template <class T>
    layer_model <T>::
    layer_model (T x)
        : m_data ( std::move(x) )
    {}

    template <class T>
    any_range
    layer_model <T>::
    input ()
    {
        return make_any_range( m_data.input() );
    }

    template <class T>
    any_range
    layer_model <T>::
    const_input () const
    {
        return make_any_range( m_data.input() );
    }

    template <class T>
    any_range
    layer_model <T>::
    output ()
    {
        return make_any_range( m_data.output() );
    }

    template <class T>
    any_range
    layer_model <T>::
    const_output () const
    {
        return make_any_range( m_data.output() );
    }

    template <class T>
    void
    layer_model <T>::
    execute ()
    {
        return m_data.execute();
    }

    template <class T>
    T &
    layer_model <T>::
    data ()
    {
        return m_data;
    }

    template <class T>
    T const&
    layer_model <T>::
    const_data () const
    {
        return m_data;
    }
}
