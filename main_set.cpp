#include <iostream>
#include "utils.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <stack>
#include <vector>
#include <map>
#include <set>
#include "map.hpp"
#include <unistd.h>
#include "set.hpp"

using namespace std;

template < typename T >
void printBT(const std::string& prefix, const ft::Node<T>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
		if (node->_color == 1)
        std::cout << node->_value.first << " b" << std::endl;
		else
        std::cout << node->_value.first << " r" << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->_left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->_right, false);
    }
}

int main(void)
{
	ft::set<int> i;
	i.insert(10);
	ft::set<int>::reverse_iterator it = i.rbegin();
	ft::set<int> j;
	j.insert(10);
	std::cout << (j != i);
	ft::swap(i, j);
}