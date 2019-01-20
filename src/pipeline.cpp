#include "pipeline.hpp"



namespace pline
{
    any_range
    pipeline::
    input ()
    {
        return m_layers.front().input();
    }

    any_range
    pipeline::
    input () const
    {
        return m_layers.front().input();
    }

    any_range
    pipeline::
    output ()
    {
        return m_layers.front().output();
    }

    any_range
    pipeline::
    output () const
    {
        return m_layers.front().output();
    }

    void
    pipeline::
    execute ()
    {
        auto first = m_layers.begin();

        auto second = std::next( m_layers.begin() );

        auto last = m_layers.end();

        first -> execute();

        for(; second != last; first++, second++)
        {
            if(second -> must_copy_input())
            {
                transfer_data( *first, *second );
            }
            second -> execute();
        }
    }

    void
    pipeline::
    compile ()
    {
        if(m_layers.empty())
        {
            throw std::logic_error( "pipeline can't have zero number of layers" );
        }

        auto first = m_layers.begin();

        auto second = std::next( m_layers.begin() );

        auto last = m_layers.end();

        for(; second != last; first++, second++)
        {
            if(second -> must_copy_input())
            {
                auto key = make_key( first->output().type(), second->output().type() );

                auto mapped = main_table::get().get_overload( key );

                m_copy_table.insert_overload ( std::move( key ), std::move( mapped ) );
            }
        }
    }

    pipeline::layers_t &
    pipeline::
    layers ()
    {
        return m_layers;
    }

    pipeline::layers_t const&
    pipeline::
    layers () const
    {
        return m_layers;
    }

    void
    pipeline::
    transfer_data (layer & first, layer & second)
    {
        m_copy_table.invoke( first.output(), second.input() );
    }
}
