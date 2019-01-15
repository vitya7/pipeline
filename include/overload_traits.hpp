#pragma once

#include <tuple>

namespace pline
{
    namespace traits
    {
        //////////////////////////////////////////////////////////////
        template <class> struct add_ptr {};

        template <class...T>
        struct add_ptr < std::tuple <T...> >
        {
            using type = std::tuple <T*... >;
        };

        template <class T>
        using add_ptr_t = typename add_ptr <T> :: type;

        //////////////////////////////////////////////////////////////
        template <class> struct add_const_ptr {};

        template <class...T>
        struct add_const_ptr < std::tuple <T...> >
        {
            using type = std::tuple <T const*... >;
        };

        template <class T>
        using add_const_ptr_t = typename add_const_ptr <T> :: type;

        //////////////////////////////////////////////////////////////
        template <class T, template <class> class ... C>
        struct get_containers_iterators
        {
            using type = std::tuple < typename C<T> :: iterator ... >;
        };

        template <class T, template <class> class ... C>
        using get_containers_iterators_t = typename get_containers_iterators <T, C...> :: type;

        template <template <class> class ... C, class ... T>
        struct get_containers_iterators < std::tuple <T...>, C... >
        {
            using type = decltype
                        (	std::tuple_cat
                            (
                                std::declval < get_containers_iterators_t <T, C...> > () ...
                            )
                        );
        };

        //////////////////////////////////////////////////////////////
        template <class T, template <class> class ... C>
        struct get_containers_const_iterators
        {
            using type = std::tuple < typename C<T> :: const_iterator ... >;
        };

        template <class T, template <class> class ... C>
        using get_containers_const_iterators_t = typename get_containers_const_iterators <T, C...> :: type;

        template <template <class> class ... C, class ... T>
        struct get_containers_const_iterators < std::tuple <T...>, C... >
        {
            using type = decltype
                        (	std::tuple_cat
                            (
                                std::declval < get_containers_const_iterators_t <T, C...> > () ...
                            )
                        );
        };

        //////////////////////////////////////////////////////////////
        template <class ... T>
        using tuple_cat_t = decltype ( std::tuple_cat ( std::declval <T> ()...) );

        //////////////////////////////////////////////////////////////
    }
}
