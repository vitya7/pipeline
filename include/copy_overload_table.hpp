#pragma once

#include "any_range.hpp"

#include "table_key.hpp"
#include "table_mapped.hpp"
#include "table_hasher.hpp"

#include <unordered_map>

namespace pline
{

    class copy_overload_table
    {
    public :

        using key_type = table_key;

        using mapped_type = table_mapped;

        using hasher = table_hasher;

        using table_type = std::unordered_map <key_type, mapped_type, hasher>;


        void insert_overload (key_type, mapped_type);

        void erase_overload (key_type const&);

        mapped_type const& get_overload (key_type const&) const;

        void invoke (any_range const&, any_range const&) const;

        void clear ();

    private :

        table_type m_table;
    };

}
