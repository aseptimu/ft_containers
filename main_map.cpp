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
	// {
	// 	ft::map<int, int> i;
	// 	ft::map<int, int> ll(i);
	// 	ft::pair<int, int> pi;
	// 	ft::map<int, int>::iterator itb;
	// 	ft::map<int, int>::iterator	ite;
	// 	cout << boolalpha << "empyt: " << i.empty() << endl;
	// 	cout << "size: " << i.size() << endl;
	// 	cout << "max_size: " << i.max_size() << endl;
	// 	cout << endl;
	// 	i.insert(ft::make_pair(10, 10));
	// 	itb = i.begin();
	// 	i.insert(itb, ft::make_pair(20, 70));
	// 	ite = i.end();
	// 	ft::map<int, int> mp;
	// 	for (int i = 0, j = 10; i < 30 * 10; ++i, ++j) {
    //     	mp.insert(ft::make_pair(i, j));
	// 	ft::map<int, int> mp2(mp.begin(), mp.end());
	// 	ft::map<int, int>::iterator it = mp2.begin();
	// 	std::vector<int> v;
	// for (int i = 0; i < 30 * 10; ++i, it++) {
    //     v.push_back(it->first);
    //     v.push_back(it->second);
    // }

    // }
	// 	// i.insert(itb, ite);


	// }

	// {
	// 	std::map<int, int> i;
	// 	std::map<int, int> ll(i);
	// 	std::pair<int, int> pi;
	// 	std::map<int, int>::iterator itb;
	// 	std::map<int, int>::iterator	ite;
	// 	cout << boolalpha << "empyt: " << i.empty() << endl;
	// 	cout << "size: " << i.size() << endl;
	// 	cout << "max_size: " << i.max_size() << endl;
	// 	cout << endl;
	// 	i.insert(std::make_pair(10, 10));
	// 	itb = i.begin();
	// 	i.insert(itb, std::make_pair(20, 70));
	// 	ite = i.end();
	// 	i.insert(itb, ite);
	// }

	// {
	// 	std::vector<int> v;
	// 	ft::map<int, int> mp;
	// 	for (int i = 0, j = 10; i < 20; ++i, ++j)
    //     	mp.insert(ft::make_pair(i, j));
	// 		ft::map<int, int> mp2;
    // 	for (int i = 20, j = 200010; i < 40; ++i, ++j)
    //     	mp2.insert(ft::make_pair(i, j));
	// 	mp2 = mp;
    // 	// ft::map<int, int>::iterator it = mp2.begin();
    // 	// ft::map<int, int>::iterator itb = mp2.begin();
    // 	// ft::map<int, int>::iterator ite = mp2.end();
	// 	// // ite--;
	// 	// // ite--;
	// 	// // printBT(" ", mp2.tree._impl._header._parent, false);
	// 	// for (; it != mp2.end(); it++) {
	// 	// 	std::cout << "begin: " << mp2.begin()._node->_value.first << std::endl;
	// 	// 	std::cout << it._node->_value.first << endl;
	// 	// 	std::cout << "end: " << ite._node->_value.first << std::endl;
    //     // v.push_back(it->first);
    //     // v.push_back(it->second);
	// 	// }
	// 	//     // v.push_back(mp2.size());
	// }

	// {
	// 	ft::map<int, int> j;
	// 	ft::map<int, int> i;
	// 	// i.insert(ft::make_pair(1, 10));
	// 	// i.insert(ft::make_pair(2, 20));
	// 	// i.insert(ft::make_pair(3, 30));
	
	// 	j.insert(ft::make_pair(1, 10));
	// 	j.insert(ft::make_pair(2, 20));
	// 	j.insert(ft::make_pair(3, 30));
	// 	i = j;
	// 	ft::map<int, int>::iterator ii = i.begin();
	// 	ft::map<int, int>::iterator it = i.begin();
	// 	ft::map<int, int>::iterator ite = i.end();

	// 	std::cout << it._node->_value.first << std::endl;
	// 	std::cout << i.end()._node->_value.first << std::endl;
	// 	for (; it != i.end(); it++)
	// 	{
	// 		std::cout << "hello" << std::endl;
	// 	}
	// 	std::cout << std::endl;
	// }

	// {
	// 	std::map<int, int> j;
	// 	std::map<int, int> i;
	// 	// i.insert(std::make_pair(1, 10));
	// 	// i.insert(std::make_pair(2, 20));
	// 	// i.insert(std::make_pair(3, 30));

	// 	j.insert(std::make_pair(1, 10));
	// 	j.insert(std::make_pair(2, 20));
	// 	j.insert(std::make_pair(3, 30));
	// 	i = j;
	// 	std::map<int, int>::iterator it = i.begin();
	// 	// std::cout << it._node->_value.first << std::endl;
	// 	// std::cout << i.end()._node->_value.first << std::endl;
	// 	for (; it != i.end(); it++)
	// 	{
	// 		std::cout << "hello" << std::endl;
	// 	}
	// 	std::cout << std::endl;
	// }

	// {
	// 	std::vector<int> v;
	// 	ft::map<int, int> m;
	// 	ft::map<int, int> mpp;
	// 	mpp.insert(ft::make_pair(16, 3));
	// 	mpp.insert(ft::make_pair(8, 3));
	// 	mpp.insert(ft::make_pair(23, 3));
	// 	ft::map<int,int>::iterator i = mpp.insert(ft::make_pair(7, 3)).first;
	// 	mpp.insert(ft::make_pair(19, 3));
	// 	mpp.insert(ft::make_pair(29, 3));
	// 	mpp.insert(ft::make_pair(41, 3));
	// 			printBT(" ", mpp.tree._impl._header._parent, false);
	// 	std::cout << std::endl;
	// 	mpp.insert(ft::make_pair(4, 3));
	// 			printBT(" ", mpp.tree._impl._header._parent, false);
	// 	std::cout << std::endl;
	// 	mpp.insert(ft::make_pair(11, 3));
	// 	printBT(" ", mpp.tree._impl._header._parent, false);
	// 	for (ft::map<int, int>::iterator it = mpp.begin(); it != mpp.end(); it++)
	// 	{ v.push_back(it->first); }
	// 	try
	// 	{
	// 	mpp.at(1000);
	// 		/* code */
	// 	}
	// 	catch(const std::exception& e)
	// 	{
	// 		std::cerr << e.what() << '\n';
	// 	}
	// 	std::cout << (mpp == m);
		
	// 	// for (ft::map<int, int>::iterator it = --mpp.end(); it != mpp.begin(); it--)
	// 	// { v.push_back(it->first); }
	// }

	{
		ft::map<int, int> mp;
		std::vector<int> v;
		for (int i = 0, j = 0; i < 25 * 10000; i++, j++)
			mp.insert(ft::make_pair(i, j));
		ft::map<int, int> ll;
		ll.swap(mp); // TODO: seg_fault
	}

	{
		std::map<int, int> mp;
		std::vector<int> v;
		for (int i = 0, j = 0; i < 25 * 10000; i++, j++)
			mp.insert(std::make_pair(i, j));
		std::map<int, int> ll;
		ll.swap(mp);	
	}

	{
		std::cout << std::endl;
		std::map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << std::endl;
	}

	{
		ft::map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	{
		ft::map<char,int> m,bar;

		m['x']=100;
		m['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;
        ft::map<char, int>::reverse_iterator it = m.rbegin();
        ft::map<char, int>::reverse_iterator it2 = m.rend();
        ft::map<char, int>::const_reverse_iterator cit = m.rbegin();
        ft::map<char, int>::const_reverse_iterator cit2 = m.rend();
		if (it == cit2)
			std::cout << "good";
		std::advance(it, 1);
		ft::iterator_traits<ft::map<char, int>::reverse_iterator>::difference_type i;
		std::iterator_traits<std::map<char, int>::reverse_iterator>::difference_type j;
		std::iterator_traits<ft::map<char, int>::reverse_iterator>::difference_type k;
		ft::map<char, int>::reverse_iterator::difference_type ll;
		ft::map<char, int>::reverse_iterator::iterator_category l;
	}

	{
		std::map<char,int> m,bar;

		m['x']=100;
		m['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;
        std::map<char, int>::reverse_iterator it = m.rbegin();
        std::map<char, int>::reverse_iterator it2 = m.rend();
        std::map<char, int>::const_reverse_iterator cit = m.rbegin();
        std::map<char, int>::const_reverse_iterator cit2 = m.rend();
		if (it == cit2)
			std::cout << "good";
		std::advance(it, 1);
	}

	{
		ft::vector<int> i;
		i[0] = 10;
		i[1] = 20;
		ft::vector<int>::reverse_iterator it = i.rbegin();
		ft::vector<int>::reverse_iterator ite = i.rend();
		std::advance(it, 1);
	}
	{
		std::vector<int> i;
		i[0] = 10;
		i[1] = 20;
		std::vector<int>::reverse_iterator it = i.rbegin();
		std::vector<int>::reverse_iterator ite = i.rend();
		std::advance(it, 1);
	}

	{
		std::map<char,int> m,bar;

		m['x']=100;
		m['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;
		std::map<char,int>::const_iterator cit = m.begin();
		std::advance(cit, 5);	
	}
}