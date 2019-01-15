#include "main_table.hpp"

#include "copy_range.hpp"

namespace pline
{
    main_table::
    main_table()
    {
        insert_overload( make_key <int*, int*> (), copy_range <int*, int*> :: copy );
    }

    main_table const&
    main_table::
    get ()
    {
        static main_table table;
        return table;
    }

}
