#include "include/any_range.hpp"

#include "include/copy_overload_table.hpp"
#include "include/main_table.hpp"

#include "include/copy_range.hpp"

#include "include/layer.hpp"



#include <iostream>

#include <algorithm>
#include <numeric>

#include <valarray>
#include <vector>
#include <set>


struct KEK
{
    std::vector<int> m_in, m_out;

    KEK (size_t n_in, size_t n_out)
        : m_in  (n_in)
        , m_out (n_out)
    {}

    auto &      input ()       { return m_in; }
    auto const& input () const { return m_in; }

    auto &      output ()       { return m_out; }
    auto const& output () const { return m_out; }

    void execute ()
    {
        auto sum = std::accumulate( m_in.begin(), m_in.end(), 0 );

        std::fill( m_out.begin(), m_out.end(), sum );
    }
};

std::ostream& operator << (std::ostream& os, KEK const& kek)
{
    os << "KEK : \n";
    os << "   input  : ";
    for(auto const& x : kek.input()) { os << x << " "; } os << "\n";
    os << "   output : ";
    for(auto const& x : kek.output()) { os << x << " "; }
    return os << "\n";
}


using namespace pline;

void table_copy ();
void table_test ();
void main_table_test ();

void layer_test ();

int main ()
{
//    table_copy ();
//    table_test ();
//    main_table_test ();

    layer_test ();
}


template <class T>
void www (T &&) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

void layer_test ()
{
    KEK kek {3, 3};
    kek.input() = {1, 2, 3};

    layer lay (kek);
    lay.get <KEK> ().input() = {3, 4, 1};

    kek.execute();
    lay.execute();

    std::cout << kek;
    std::cout << lay.get <KEK> ();
try
{
    main_table::get().invoke ( lay.output() , lay.input() );
}
catch (std::exception const& ex)
{
    std::cerr << ex.what() << "\n";
}

    std::cout << "\n";
    std::cout << lay.get <KEK> ();
    lay.execute();
    std::cout << lay.get <KEK> ();

}

void table_copy ()
{
    std::valarray vi = {1, 2, 3, 4, 5};
    std::valarray vo = {0, 0, 0, 0, 0, 0};

    any_range irg = make_any_range( std::as_const(vi) );
    any_range org = make_any_range( vo );

    copy_range <int*, int*> :: copy ( debug_copy_tag{}, irg, org );    // throws

    for(auto x : vi){ std::cout << x << " "; } std::cout << "\n";
    for(auto x : vo){ std::cout << x << " "; } std::cout << "\n";
}

void main_table_test ()
{
    std::valarray <double> const vi = {1, 2, 4, 6, 8};
    std::vector <int>       vo = {0, 0, 0, 0, 0, 0};

    any_range irg = make_any_range( vi );
    any_range org = make_any_range( vo );

    auto & mt = main_table::get();

try
{
    mt.invoke( irg, org );
}
catch (std::out_of_range const& ex)
{
    std::cerr << "invocation fail : " << ex.what() << std::endl;
}

    for(auto x : vi){ std::cout << x << " "; } std::cout << "\n";
    for(auto x : vo){ std::cout << x << " "; } std::cout << "\n";
}

void table_test()
{
    std::vector vi = {1, 2, 3, 4, 5};
    std::vector vo = {0, 0, 0, 0, 0, 0};

    any_range irg = make_any_range( std::as_const(vi) );
    any_range org = make_any_range( vo );

    using T1 = std::vector<int>::const_iterator;
    using T2 = std::vector<int>::iterator;

    copy_overload_table tb{};

    tb.insert_overload ( make_key<T1, T2>(), copy_range <T1, T2>::copy );
//    tb.erase_overload ( make_key<T1, T2>() );

try
{
    tb.invoke( irg, org );
}
catch (std::out_of_range const& ex)
{
    std::cerr << "invocation fail : " << ex.what() << std::endl;
}


    for(auto x : vi){ std::cout << x << " "; } std::cout << "\n";
    for(auto x : vo){ std::cout << x << " "; } std::cout << "\n";
}

