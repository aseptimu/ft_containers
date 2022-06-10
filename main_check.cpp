#include <iostream>
#include "vector.hpp"
#include <vector>
#include "stack.hpp"
#include <stack>
#include "map.hpp"
#include <map>
#include "set.hpp"
#include <set>

int main(void)
{
	/*	VECTOR	*/

	//CONSTRUCTOR
	{
		/*

		explicit vector (const allocator_type& alloc = allocator_type());
		
		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());
		
		template <class InputIterator>
				vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type());
		
		vector (const vector& x);
		*/
		std::cout << std::endl;
		// constructors used in the same order as described above:
		ft::vector<int> first;                                // empty vector of ints
		ft::vector<int> second (4,100);                       // four ints with value 100
		ft::vector<int> third (second.begin(),second.end());  // iterating through second
		ft::vector<int> fourth (third);

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "The contents of fifth are:";
		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// OPERATOR=
	{
		std::cout << std::endl;
		ft::vector<int> foo (3,0);
		ft::vector<int> bar (5,0);

		bar = foo;
		foo = ft::vector<int>();

		std::cout << "Size of foo: " << int(foo.size()) << '\n';
		std::cout << "Size of bar: " << int(bar.size()) << '\n';
	}

	// BEGIN && END
	{
		std::cout << std::endl;
		ft::vector<int> myvector;
		for (int i=1; i<=5; i++) myvector.push_back(i);

		std::cout << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// RBEGIN && REND
	{
		std::cout << std::endl;
		ft::vector<int> myvector (5);  // 5 default-constructed ints

		int i=0;

		ft::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
			*rit = ++i;

		std::cout << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// REND
	{
		std::cout << std::endl;
	}

	// SIZE
	{
		std::cout << std::endl;
	}

	// MAX_SIZE
	{
		std::cout << std::endl;
	}

	// RESIZE
	{
		std::cout << std::endl;
	}

	// CAPACITY
	{
		std::cout << std::endl;
	}

	// EMPTY
	{
		std::cout << std::endl;
	}

	// RESERVE
	{
		std::cout << std::endl;
	}

	//OPERATOR[]
	{
		std::cout << std::endl;
	}

	// AT
	{
				std::cout << std::endl;
	}

	// FRONT
	{
		std::cout << std::endl;
	}

	// BACK
	{
		std::cout << std::endl;
	}

	// ASSIGN
	{
		std::cout << std::endl;
	}

	// PUSH_BACK
	{
		std::cout << std::endl;
	}

	// POP_BACK
	{
		std::cout << std::endl;
	}

	// INSERT
	{
		std::cout << std::endl;
	}

	// ERASE
	{
		std::cout << std::endl;
	}

	// SWAP
	{
		std::cout << std::endl;
	}

	// CLEAR
	{
		std::cout << std::endl;
	}

	// GET_ALLOCATOR
	{
		std::cout << std::endl;
	}

	// OPERATORS
	{
		std::cout << std::endl;
	}

	// SWAP
	{
		std::cout << std::endl;
	}

}