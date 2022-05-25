#include <iostream>
#include "utils.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <stack>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main(void)
{
	{
		map<int, string> i;
		i.insert(pair<int, string>(10, "lol"));
		i.insert(pair<int, string>(10, "kek"));
		map<int, string>::iterator g = i.find(20);

		if (g != i.end())
			cout << i.find(10)->second << endl;
		else
			cout << "lol" << endl;
	}

	{
		cout << endl;
		ft::pair<int, string> test;
		ft::pair<const int, const string> test2 (23, "lol");
		ft::pair<const int, const string> test3 (test2);
		test.first = 0;
		test.second = "kek";

		cout << test.first << " string: " << test.second << endl;
		cout << test2.first << " stirng: " << test2.second << endl;
		cout << test3.first << " string: " << test3.second << endl;
	}

	{
		cout << endl;
		ft::pair <string, int> planet, homeplanet;

		planet = ft::make_pair("Earth", 6371);

		homeplanet = planet;

		cout << "Home planet: " << homeplanet.first << endl;
		cout << "Planet size: " << homeplanet.second << endl;
	}

	{
		cout << endl;
		std::pair<int,char> foo (10,'x');
		std::pair<int,char> bar (90,'a');

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}

	{
		cout << endl;
		std::map<int, string> i;
		
	}
}