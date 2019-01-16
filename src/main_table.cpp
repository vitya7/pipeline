#include "main_table.hpp"

#include "copy_range.hpp"

#include "overload_traits.hpp"

#include <iostream>
#include <vector>

namespace pline
{

//    template <class ... T>
//    void w ()
//    {
//        std::cerr << __PRETTY_FUNCTION__ << "\n";
//    }

    template <class ItTupleInput, class ItTupleOutput, size_t I1, size_t I2>
    void
    main_table::
    insert_overloads ()
    {
        if constexpr ( I1 == std::tuple_size_v < ItTupleInput > ||
                       I2 == std::tuple_size_v < ItTupleOutput > )
        {
            return;
        }
        else
        {
            using It1 = std::tuple_element_t <I1, ItTupleInput>;
            using It2 = std::tuple_element_t <I2, ItTupleOutput>;

//            w < It1, It2 > ();

            insert_overload ( make_key <It1, It2> (), copy_range <It1, It2> :: copy );

            insert_overloads < ItTupleInput, ItTupleOutput, I1, I2+1 > ();

            if constexpr (I2 == 0)
            {
                insert_overloads < ItTupleInput, ItTupleOutput, I1+1, I2 > ();
            }
        }
    }

    main_table::
    main_table()
    {
        using in_t = traits::tuple_cat_t
                    <	traits::add_ptr_t                           < iterator_value_types >
                    ,	traits::add_const_ptr_t                     < iterator_value_types >
                    ,	traits::get_containers_iterators_t 		    < iterator_value_types, std::vector >
                    ,	traits::get_containers_const_iterators_t    < iterator_value_types, std::vector >
                    >;

        using out_t = traits::tuple_cat_t
                    <	traits::add_ptr_t                           < iterator_value_types >
                    ,	traits::get_containers_iterators_t 		    < iterator_value_types, std::vector >
                    >;

        insert_overloads < in_t, out_t > ();
    }

    main_table const&
    main_table::
    get ()
    {
        static main_table table;
        return table;
    }
}
