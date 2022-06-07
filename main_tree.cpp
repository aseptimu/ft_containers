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

template < typename T >
void printBT(const std::string& prefix, const ft::Node<T>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
		if (node->_color == 1)
        std::cout << node->_value << " b" << std::endl;
		else
        std::cout << node->_value << " r" << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->_left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->_right, false);
    }
}

template < typename T >
void printBT(const ft::Node<T>* node)
{
    printBT("", node, false);    
}

int main(void)
{

	ft::Tree<int, int,  _Identity<int>, std::less<int> > i;
	ft::Tree<int, int,  _Identity<int>, std::less<int> >::iterator it = i.begin(); // чёт не то
	ft::Tree<int, int,  _Identity<int>, std::less<int> >::iterator ien = i.end();
	i._insert_(it, 10);
	i._insert_(it, 20);
	i._insert_(it, 30);
	i._insert_(it, 40);
	i._insert_(it, 22);
	i._insert_(it, 3);
	i._insert_(it, 14);
	i._insert_(it, 55);
	i._insert_(it, 60);
	i._insert_(it, 70);
	i._insert_(it, 80);
	it = i.begin();
	it++;
	printBT(i._impl._header._parent);
	std::cout << *(i.find(80)) << std::endl;
	std::cout << *(i.end()) << std::endl << std::endl; 
	
  std::cout << *(i.begin()) << std::endl;
	std::cout << it.operator*() << std::endl;
}