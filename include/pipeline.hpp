#pragma once

#include "layer.hpp"

#include <vector>

namespace pline
{
    class pipeline
    {
    public:

        using layers_t = std::vector <layer>;


        pipeline () = default;

        any_range input ();
        any_range input () const ;

        any_range output ();
        any_range output () const ;

        void execute ();

        void compile ();

        layers_t &      layers ();
        layers_t const& layers ();

    private:

        transfer_data (layer &, layer &);

        layers_t m_layers;

        copy_overload_table m_copy_table;

    };
}
