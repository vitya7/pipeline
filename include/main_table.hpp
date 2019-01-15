#pragma once

#include "copy_overload_table.hpp"

#include "copy_range.hpp"

#include <tuple>

namespace pline
{


    class main_table : public copy_overload_table
    {
    public :

        using iterator_value_types = std::tuple < char, int, float, double, long double >;

        static main_table const& get ();

    private:

        main_table ();

        main_table (main_table const&) = default;
        main_table (main_table &&) = default;

        template <class ItTupleInput, class ItTupleOutput, size_t I1 = 0, size_t I2 = 0>
        void insert_overloads ();

    };

}
