#include "table_key.hpp"

namespace pline
{
    table_key make_key (std::type_info const& x, std::type_info const& y)
    {
        return {std::type_index{ x }, std::type_index{ y }};
    }
}
