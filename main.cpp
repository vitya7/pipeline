#include "include/any_range.hpp"
#include "include/copy_overload_table.hpp"
#include "include/copy_range.hpp"


#include <iostream>
#include <valarray>
#include <iterator>
#include <memory>
#include <exception>
#include <utility>


namespace pline
{

class layer_concept
{
public :

	virtual ~layer_concept () = default;

	virtual any_range input  () = 0;
	virtual any_range input  () const = 0;

	virtual any_range output () = 0;
	virtual any_range output () const = 0;

	virtual void execute () = 0;
};

template <class T>
class model : public layer_concept
{
public :

	model (T x) : m_data (move(x)) {}

	any_range input ()       override;
	any_range input () const override;

	any_range output ()       override;
	any_range output () const override; // { return make_any_range( m_data.output() ); }

    void execute () override; // { m_data.execute(); }

    T &      data ();
    T const& data () const;

private :

	T m_data;
};

class layer
{
public :

    template <class T>
    layer (T x)
        : m_self ( std::move(x) )
    {
        // empty
    }

    template <class Self>
    Self& get ()
    {
        return dynamic_cast <model <Self> *> (m_self.get()) -> data();
    }

    template <class Self>
    Self const& get () const
    {
        return dynamic_cast <model <Self> const *> (m_self.get()) -> data();
    }

    any_range input ();
    any_range input () const;

    any_range output ();
    any_range output () const;

    void execute ();

	bool must_copy_input ();
	void must_copy_input (bool);

private :

	bool m_must_copy_input;

    std::shared_ptr <layer_concept> m_self;
};



}

#include <vector>

using namespace pline;

int main()
{
    std::vector vi = {1, 2, 3, 4, 5};
    std::vector vo = {0, 0, 0, 0, 0, 0};

    any_range irg = make_any_range( std::as_const(vi) );
    any_range org = make_any_range( vo );

    using T1 = std::vector<int>::const_iterator;
    using T2 = std::vector<int>::iterator;

//    copy_range_impl::copy_range < T1, T2 > :: copy (irg, org);
//
//    for(auto x : vi) std::cout << x << " "; std::cout << "\n";
//    for(auto x : vo) std::cout << x << " "; std::cout << "\n";


    copy_overload_table tb{};

    tb.insert_overload ( make_key<T1, T2>(), copy_range <T1, T2>::copy );
//    tb.erase_overload ( make_key<T1, T2>() );

try
{
    tb.invoke( irg, org );
    (*tb.get_overload( make_key<T1, T2>() )) (irg, org);
}
catch (std::out_of_range const& ex)
{
    std::cerr << "invocation fail : " << ex.what() << std::endl;
}
    for(auto x : vi){ std::cout << x << " "; } std::cout << "\n";
    for(auto x : vo){ std::cout << x << " "; } std::cout << "\n";

	return 0;
}

