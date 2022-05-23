#include "stack.hpp"
#include "vector.hpp"
#include <stack>
#include <iostream>
#include <vector>
#include "iterator.hpp"

		class A
		{
			public:
				A() { std::cout << "constructor called" << std::endl; }
				~A() { std::cout << "destructor called" << std::endl;}
		};
int main()
{
	// {
	// 	std::string a;
	// 	ft::vector<int> vec(10);
	// 	std::vector<int> asdf(10);
	// std::vector<int>::iterator it;
	// std::cout << it.base() << std::endl;
	// std::cout << a << std::endl;
	// 	asdf.push_back(2);
	// 	std::cout << asdf.size() << " " << asdf.capacity() << std::endl;
	// 	vec.push_back(2);
	// 	std::cout << vec.size() << " " << vec.capacity() << std::endl;
	// 	std::cout << std::endl;
	// }

	{
		std::cout << std::endl;
		std::vector<int> c;
		std::vector<char> cc;
		c.push_back(22);
		std::cout << cc.max_size() << std::endl;
		std::cout << c.max_size() << std::endl;
		std::vector<int>::iterator it = c.begin();
		std::cout << it.operator->() << std::endl;
		std::cout << &c[0] << std::endl;
		// it.base()
		// std::cout << 18446744073709551615ULL / 4 << std::endl;
		// std::cout << std::numeric_limits<size_t>::max() << " " << std::numeric_limits<std::ptrdiff_t>::max() << " " << sizeof(int) << std::endl;
		std::cout << std::endl;

		std::cout << std::endl;
		ft::vector<int> d;
		ft::vector<char> dd;
		d.push_back(22);
		std::cout << dd.max_size() << std::endl;
		std::cout << d.max_size() << std::endl;
	}

	// {
	// 	std::vector<int> v;
	// 	v.push_back(22);
	// 	v.push_back(11);
	// 	v.push_back(11);
	// 	std::cout << v.size() << std::endl;
	// 	std::cout << v.capacity() << std::endl;
	// 	v.resize(1);
	// 	std::cout << v.size() << std::endl;
	// 	std::cout << v.capacity() << std::endl;
	// 	v.push_back(1);
	// 	std::cout << v[0] << std::endl;
	// 	std::cout << std::endl;
	// }

	// {
	// 	std::cout << std::endl;
	// 	ft::vector<int> j;
	// 	for (int i = 0; i < 20; i++)
	// 		j.push_back(i);
	// 	j.reserve(100);
	// 	std::cout << j.capacity() << std::endl;
	// 	std::cout << j.size() << std::endl;
	// 	std::cout << std::endl;
	// }

	// {
	// 	std::cout << std::endl;
	// 	ft::vector<int> v(1);
	// 	for (int i = 0; i < 10; i++)
	// 		v.push_back(i);
	// 	std::cout << v[9] << std::endl;
	// 	v.pop_back();
	// 	std::cout << v[9] << std::endl;
	// 	v.push_back(22);
	// 	std::cout << v[9] << std::endl;
	// 	std::cout << std::endl;
	// }

	{
		std::cout << std::endl;
		ft::vector<int> i;
		i.push_back(20);
		i.push_back(10);
		ft::vector<int>::iterator it = i.begin();
		ft::vector<int>::iterator ie = i.end();
		std::cout << *(ie - 1) << std::endl;

		std::vector<int> id;
		id.push_back(20);
		id.push_back(10);
		// std::vector<int>::iterator it1 = id.begin();
		std::vector<int>::iterator ie1 = id.end();
		std::cout << *(ie1 - 1) << std::endl;
		std::cout << std::endl;
	}

	{
		std::vector<int> d;
		for (int i = 0; i < 10; i++)
			d.push_back(i * 10);
		// std::cout << d[9] << std::endl;
		std::vector<int>::iterator beg = d.begin();
		std::vector<int>::iterator en = d.end();
		// std::cout << *(en - 1) << std::endl << std::endl;
		// 		std::cout << " begin iter: " << (*beg) << std::endl << std::endl;		
		// 		std::cout << " end iter: " << (*en) << std::endl << std::endl;
		std::vector<int>::reverse_iterator it(beg);
		std::vector<int>::reverse_iterator ie(en);
		// std::cout <<" begin rev iter: " <<  *(it.base()) << std::endl << std::endl;
		// std::cout << " end rev iter: " << *(ie.base()) << std::endl << std::endl;
		// std::cout << *(++it) << std::endl;
		// std::cout << it[0] << std::endl;
		std::cout << std::endl;
		std::cout << std::endl << *(it.base()) << std::endl << *(ie.base()) << std::endl << std::endl;
				std::cout << *(3 + it) << std::endl;
		// while (it != ie)
		// {
		// 	std::cout << *(it.base()) << std::endl;
		// 	it--;
		// }
	}
	
	{
		ft::vector<int> d;
		for (int i = 0; i < 10; i++)
			d.push_back(i * 10);
		ft::vector<int>::iterator	beg = d.begin();
		ft::vector<int>::iterator	en = d.end();
		ft::vector<int>::reverse_iterator it(beg);
		ft::vector<int>::reverse_iterator ie(en);

		// std::cout << it[0] << std::endl;

		std::cout << std::endl;
		std::cout << std::endl << *(it.base()) << std::endl << *(ie.base()) << std::endl << std::endl;
		std::cout << *(3 + it) << std::endl;
		// while (it != ie)
		// {
		// 	std::cout << *(it.base()) << std::endl;
		// 	it--;
		// }
	}

	{
		std::cout << std::endl;
		std::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);

		std::reverse_iterator<std::vector<int>::iterator> from,until;

		from = myvector.rbegin();
		until = myvector.rend();

		std::cout << *(from) << std::endl;
		std::cout << *(until - 1) << std::endl;
		std::cout << "myvector has " << (until-from) << " elements.\n";
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		ft::vector<int> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i);

		ft::reverse_iterator<ft::vector<int>::iterator> from,until;

		from = myvector.rbegin();
		until = myvector.rend();

		std::cout << *(from) << std::endl;
		std::cout << *(until - 1) << std::endl;
		std::cout << "myvector has " << (until-from) << " elements.\n"; //TODO: проверить!
		std::cout << std::endl;

	}

	// {
	// 	std::cout << std::endl;
	// 	ft::vector<int> myvector;
	// 	std::vector<int> n;
	// 	for (int i=0; i<10; i++) myvector.push_back(i);
	// 	for (int i=0; i<10; i++) n.push_back(i);
	// 	std::vector<int>::iterator from,until;
	// 	from = n.begin();
	// 	until = n.end();
	// 	std::cout << *(from.base()) << " " << *(until.base() - 1) << std::endl;
	// 	ft::vector<int>::iterator from1,until1;
	// 	from1 = myvector.begin();
	// 	until1 = myvector.end();
	// 	std::cout << *from1 << " " << *(until1.base() - 1) << std::endl;
	// 	std::cout << std::endl;

	// }

	{
		std::cout << std::endl;
		ft::vector<int> vec;
		for (int i = 0; i < 10; i++)
			vec.push_back(i * 2);
		ft::vector<int>::iterator it = vec.begin();
		ft::vector<int>::iterator en = vec.end();
		std::cout << en - it << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		std::vector<int> vec;
		for (int i = 0; i < 10; i++)
			vec.push_back(i * 2);
		std::vector<int>::iterator it = vec.begin();
		std::vector<int>::iterator en = vec.end();
		std::cout << en - it << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		std::vector<int> vec1;
		for (int i = 0; i < 10; i++)
			vec1.push_back(i * 2);
		std::vector<int> vec2;
		for (int i = 0; i < 10; i++)
			vec2.push_back(i * 2);
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		std::vector<int> vec1;
		for (int i = 0; i < 10; i++)
			vec1.push_back(i * 2);
		std::vector<int> vec2;
		for (int i = 0; i < 10; i++)
			vec2.push_back(i * 2);
		// vec2.push_back(10);
		bool lol = vec1 < vec2;
		std::cout << lol << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		std::vector<int> vec1;
		for (int i = 0; i < 10; i++)
			vec1.push_back(i * 2);
		std::vector<int> vec2;
		for (int i = 0; i < 10; i++)
			vec2.push_back(i * 2);
		// vec2.push_back(10);
		bool lol = vec1 < vec2;
		std::cout << lol << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		ft::vector<int> vec1;
		for (int i = 0; i < 10; i++)
			vec1.push_back(i * 2);
		ft::vector<int> vec2;
		for (int i = 0; i < 10; i++)
			vec2.push_back(i * 2);
		vec2.push_back(10);
		bool lol = vec1 < vec2;
		std::cout << lol << std::endl;
		std::cout << std::endl;
	}

	{
		ft::vector<int> tmp(1000 * 10000, 4), tmp2(1000 * 10000, 5);
	    ft::vector<int> tmp4(tmp.begin(), tmp.end());
	}

	{
		std::cout << std::boolalpha;
		std::cout << "is_integral:" << std::endl;
		std::cout << "char: " << ft::is_integral<char>::value << std::endl;
		std::cout << "int: " << ft::is_integral<const int>::value << std::endl;
		std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	}

	// {
	// 	std::cout << std::endl;
	// 	ft::vector<int>::iterator utl;
	// 	ft::vector<int>::reverse_iterator it;
	// 	std::cout << std::boolalpha;
	// 	std::cout << "is_iterator:" << std::endl;
	// 	std::cout << "char: " << ft::is_iterator<char>::value << std::endl;
	// 	std::cout << "int: " << ft::is_iterator<int>::value << std::endl;
	// 	std::cout << "float: " << ft::is_iterator<float>::value << std::endl;
	// 	std::cout << "iterator: " << ft::is_iterator<ft::vector<int>::iterator>::value << std::endl;
	// 	std::cout << "reverse_iterator: " << ft::is_iterator<ft::vector<int>::reverse_iterator>::value << std::endl;
	// }
	// {
	// 	std::cout << std::endl;
	// 	ft::vector<int> vec1;
	// 	for (int i = 0; i < 10; i++)
	// 		vec1.push_back(i * 2);
	// 	ft::vector<int>::iterator it = vec1.begin();
	// 	it += 1;

	// }

	// {
	// 	std::cout << std::endl;
	// 	std::vector<int> result, result_2;
	// 	std::vector<int> v_int1, v_int2, v_int3;
	// 	std::vector<std::string> v_str1, v_str2;
	// 	ft::vector<int> V_int1, V_int2, V_int3;
	// 	ft::vector<std::string> V_str1, V_str2;
	// 	v_int1.push_back(1);
	// 	v_int3.push_back(1);
	// 	v_str1.push_back("aa");
	// 	v_str2.push_back("ab");
	// 	result.push_back(v_int1 < v_int2);
	// 	v_int2.push_back(2);
	// 	result.push_back(v_int1 < v_int2);
	// 	result.push_back(v_int1 < v_int3);
	// 	result.push_back(v_str1 < v_str2);
	// 	V_int1.push_back(1);
	// 	V_int3.push_back(1);
	// 	V_str1.push_back("aa");
	// 	V_str2.push_back("ab");
	// 	result_2.push_back(V_int1 < V_int2);
	// 	V_int2.push_back(2);
	// 	result_2.push_back(V_int1 < V_int2);
	// 	result_2.push_back(V_int1 < V_int3);
	// 	result_2.push_back(V_str1 < V_str2);
	// }
	// {
	// 	std::cout << std::endl;
	// 	ft::vector<int> vec1;
	// 	for (int i = 0; i < 10; i++)
	// 		vec1.push_back(i * 3);
	// 	for (int i = 0; i < 12; i++)
	// 		std::cout << vec1[i] << " ";
	// 	std::cout << "size: " << vec1.size() << " capacity: " << vec1.capacity() << std::endl;
	// 	vec1.assign(18, 100);
	// 	for (int i = 0; i < 12; i++)
	// 		std::cout << vec1[i] << " ";
	// 	std::cout << "size: " << vec1.size() << " capacity: " << vec1.capacity() << std::endl;
	// }

	// {
	// 	ft::vector<int> vec1;
	// 	for (int i = 0; i < 10; i++)
	// 		vec1.push_back(i * 3);
	// 	ft::vector<int>::iterator it = vec1.begin();
	// 	ft::advance(it, 2);
	// 	std::cout << *it  << std::endl;
	// }

	{
		std::cout << std::endl;
		ft::vector<int> vec1;
		for (int i = 0; i < 10; i++)
			vec1.push_back(i);
		ft::vector<int>::iterator it = vec1.begin();
		ft::vector<int>::iterator it2 = it + 2;
		it += 5;
		it2 += 7;
		// std::vector<int> vec2;
		// for (int i = 0; i < 10; i++)
		// 	vec2.push_back(i + 100);
		vec1.assign(it, it2);
		for (int i = 0; i < 10; i++)
			std::cout << vec1[i] << " ";
		std::cout << std::endl << vec1.size() << " " << vec1.capacity() << std::endl;
	}

	// {
	// 	std::cout << std::endl;
	// 	std::vector<int> tmp;
	// 	ft::vector<int> vector;
	// 	vector.assign(3, 3);
	// 	tmp.assign(4000 * 10000, 1);
	// 	vector.assign(tmp.begin(), tmp.end());
	// }

	{
		std::cout << std::endl;
		std::vector<int> vec1;
		for (int i = 0; i < 8; i++)
			vec1.push_back(i);
		for (int i = 0; i < 8; i++)
			std::cout << vec1[i] << " ";
		std::cout << std::endl << vec1.capacity() << " " << vec1.size() << std::endl;
		std::cout << std::boolalpha;
		// bool b = vec1.end() == vec1.erase(vec1.begin() + 8);
		// std::cout << b << std::endl;
		for (int i = 0; i < 8; i++)
			std::cout << vec1[i] << " ";
		std::cout << std::endl << vec1.capacity() << " " << vec1.size() << std::endl;
	}

	{
		std::cout << std::endl;
		ft::vector<int> vec1;
		for (int i = 0; i < 8; i++)
			vec1.push_back(i);
		for (int i = 0; i < 8; i++)
			std::cout << vec1[i] << " ";
		std::cout << std::endl << vec1.capacity() << " " << vec1.size() << std::endl;
		std::cout << std::boolalpha;
		bool b = vec1.end() == vec1.erase(vec1.begin(), vec1.end());
		std::cout << b << std::endl;
		for (int i = 0; i < 8; i++)
			std::cout << vec1[i] << " ";
		std::cout << std::endl << vec1.capacity() << " " << vec1.size() << std::endl;
	}

	{
		std::cout << std::endl;
		ft::vector<int> vec1;
		vec1.reserve(20);
		for (int i = 0; i < 20; i++)
			vec1.push_back(i);
		std::cout << vec1.capacity() << std::endl;
		vec1.insert(vec1.begin(), 41, 100);
		std::cout << vec1.capacity() << std::endl;
	}

	{
		ft::vector<int> k;
		ft::vector<int> j;
		for (int i = 0; i < 8; i++)
			k.push_back(i);
		for (int i = 0; i < 8; i++)
			j.push_back(i);
		k.swap(j);
	}

	{
		std::cout << ft::is_integral<long>() << std::endl;
		std::cout << ft::is_integral<float>() << std::endl;
	}

	{
		std::cout << std::endl;
		std::vector<std::string> res;
		std::vector<std::string> res2;
		// g_start1 = g_end1 = timer();

		res.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
		res.push_back(typeid(std::vector<int>::iterator::value_type).name());
		res.push_back(typeid(std::vector<int>::iterator::difference_type).name());
		res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
		res.push_back(typeid(std::vector<int>::iterator::pointer).name());
		res.push_back(typeid(std::vector<int>::iterator::reference).name());
		res.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
		res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
		res.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
		res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
		res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());

		res2.push_back(typeid(ft::vector<int>::iterator::iterator_category).name());
		res2.push_back(typeid(ft::vector<int>::iterator::value_type).name());
		res2.push_back(typeid(ft::vector<int>::iterator::difference_type).name());
		res2.push_back(typeid(ft::vector<int>::iterator::iterator_type).name());
		res2.push_back(typeid(ft::vector<int>::iterator::pointer).name());
		res2.push_back(typeid(ft::vector<int>::iterator::reference).name());
		res2.push_back(typeid(ft::vector<int>::reverse_iterator::iterator_category).name());
		res2.push_back(typeid(ft::vector<int>::reverse_iterator::value_type).name());
		res2.push_back(typeid(ft::vector<int>::reverse_iterator::difference_type).name());
		res2.push_back(typeid(ft::vector<int>::reverse_iterator::pointer).name());
		res2.push_back(typeid(ft::vector<int>::reverse_iterator::reference).name());
		for (size_t i = 0; i < res.size(); i++)
		{
			std::cout << res[i] << std::endl;
			std::cout << res2[i] << std::endl;
		}
		std::cout << "\n";
		std::cout << (res == res2) << std::endl;
	}

	// }
	return 0;
}
