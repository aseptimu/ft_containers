#include "tree.hpp"
#include "tree_balance.hpp"
#include <iostream>

  template<typename _Tp>
    struct _Identity
    : public std::unary_function<_Tp, _Tp>
    {
      _Tp&
      operator()(_Tp& __x) const
      { return __x; }

      const _Tp&
      operator()(const _Tp& __x) const
      { return __x; }
    };

template < typename K >
class Key
{
	K& operator()(K& x) const
	{
		return x;
	}
};

int main(void)
{
	ft::Tree<int, int,  _Identity<int>, std::less<int> > i;
	ft::Tree<int, int,  _Identity<int>, std::less<int> >::iterator it = i.begin();
	ft::Tree<int, int,  _Identity<int>, std::less<int> >::iterator ien = i.end();
	i._insert_(it, 10);
	// it++;
	std::cout << *it << std::endl;
}