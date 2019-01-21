#include "copy_overload_table.hpp"

namespace pline
{
    void
    copy_overload_table::
    insert_overload (key_type key, mapped_type value)
    {
        m_table.emplace( std::move(key), std::move(value) );
    }

    void
    copy_overload_table::
    erase_overload (key_type const& key)
    {
        m_table.erase( key );
    }

    copy_overload_table::mapped_type const&
    copy_overload_table::
    get_overload (key_type const& key) const
    {
        return m_table.at( key );
    }

    void
    copy_overload_table::
    invoke (any_range const& i, any_range const& o) const
    {
        key_type key = make_key( std::begin(i).type(), std::begin(o).type() );

        (*get_overload( key )) ( i, o );
    }

    void
    copy_overload_table::
    clear ()
    {
        m_table.clear();
    }
}
