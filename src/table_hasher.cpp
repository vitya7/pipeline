#include "table_hasher.hpp"

#include <functional>

namespace pline
{
    size_t
    table_hasher::
    operator () (table_key const& key) const
    {
        uint64_t h1 = std::hash <std::type_index> {} ( key.first );
        uint64_t h2 = std::hash <std::type_index> {} ( key.second );
        return (h1 << 10) ^ h2;
    }
}
