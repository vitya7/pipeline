#pragma once

#include "layer_concept.hpp"
#include "layer_model.hpp"

#include <memory>

namespace pline
{
    class layer
    {
    public :

        template <class T>
        layer (T x);

        template <class Self>
        Self& get ();

        template <class Self>
        Self const& get () const;

        any_range input  ();
        any_range input  () const;

        any_range output ();
        any_range output () const;

        void execute ();

        bool must_copy_input ();
        void must_copy_input (bool);

    private :

        std::shared_ptr <layer_concept> m_self;

        bool m_must_copy_input;
    };

    template <class T>
    layer::
    layer (T x)
        : m_self ( std::make_shared <layer_model <T>> ( std::move(x) ) )
        , m_must_copy_input ( true )
    {}

    template <class Self>
    Self&
    layer::
    get ()
    {
        static_assert ( std::is_same_v < std::decay_t <Self>, Self >
                      , "Self have to be non reference or/and cv-qualified" );

        return dynamic_cast <layer_model <Self> *> (m_self.get()) -> data();
    }

    template <class Self>
    Self const&
    layer::
    get () const
    {
        static_assert ( std::is_same_v < std::decay_t <Self>, Self >
                      , "Self have to be non reference or/and cv-qualified" );

        return dynamic_cast <layer_model <Self> *> (m_self.get()) -> const_data();
    }
}
