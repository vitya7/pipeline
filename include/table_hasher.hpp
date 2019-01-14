#pragma once

#include "table_key.hpp"

namespace pline
{
    struct table_hasher
    {
        size_t operator () (table_key const& key) const;
    };
}
