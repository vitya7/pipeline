#pragma once

#include <utility>
#include <typeindex>

namespace pline
{
    using table_key = std::pair <std::type_index, std::type_index>;

    table_key make_key (std::type_info const& x, std::type_info const& y);

    template <class T1, class T2>
    inline
    table_key make_key ()
    {
        return make_key( typeid(T1), typeid(T2) );
    }
}
