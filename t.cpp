#include "tree.hpp"
#include <iostream>
#include <map>

using namespace std;

int main(void)
{

{
	    // std::map<int, int> i;
        // i.insert(std::pair<int, int>(30, 10));
        // // i.insert(std::pair<int, int>(15, 10));
        // // i.insert(std::pair<int, int>(70, 10));
        // // i.insert(std::pair<int, int>(10, 10));
        // // i.insert(std::pair<int, int>(20, 10));
        // // i.insert(std::pair<int, int>(60, 10));
        // // i.insert(std::pair<int, int>(85, 10));
        // // i.insert(std::pair<int, int>(5, 10));
        // // i.insert(std::pair<int, int>(50, 10));
        // // i.insert(std::pair<int, int>(65, 10));
        // // i.insert(std::pair<int, int>(80, 10));
        // // i.insert(std::pair<int, int>(90, 10));
        // // i.insert(std::pair<int, int>(6, 10));
        // // i.erase(6);
        // // i.insert(std::pair<int, int>(89, 10));
        // std::map<int, int>::iterator it = i.begin();
        // // cout << (*it).first << endl;
        // // it--;
        // // cout << (*it).first << endl;
        // // it++;
        // it++;
        
        // cout << (*it).first << endl;
        // it++;
        
        // cout << (*it).first << endl;
        //     it++;
        
        // cout << (*it).first << endl;
}
	ft::NodeBase t;
	t._color = ft::_red_n;

	ft::NodeHeader l;
	l._nodeCount = 100;
	// cout << l._header._color;
	ft::TreeBaseIterator o;
	ft::Node<int> *n1 = ft::Tree<int, int, std::less<int> >::_node_allocator().allocate(1);
	ft::Node<int> *n2 = ft::Tree<int, int, std::less<int> >::_node_allocator().allocate(1);
	ft::Node<int> *n3 = ft::Tree<int, int, std::less<int> >::_node_allocator().allocate(1);
	ft::Node<int> *n4 = ft::Tree<int, int, std::less<int> >::_node_allocator().allocate(1);
	ft::Node<int> *n5 = ft::Tree<int, int, std::less<int> >::_node_allocator().allocate(1);
	ft::Node<int> *n6 = ft::Tree<int, int, std::less<int> >::_node_allocator().allocate(1);
	n2->_left = n1;
	n2->_right = n3;
	n3->_left = n4;
	n3->_right = n5;
	n1->_color = ft::_red_n;

	ft::TreeIterator<int> a(n1);
	ft::TreeConstIterator<int> b(n2);
	std::cout << (b!=a) << std::endl;
	b = a;
	n1->_value = 10;

	
	// std::map<int, int> fdg;
	// fdg.insert(std::pair<int,int>(1, 10));
	// fdg.insert(std::pair<int,int>(2, 10));
	// fdg.insert(std::pair<int,int>(3, 10));
	// fdg.insert(std::pair<int,int>(4, 10));
	// fdg.insert(std::pair<int,int>(5, 10));
	// fdg.insert(std::pair<int,int>(6, 10));
	// std::map<int, int>::const_iterator cit = fdg.begin();
	// std::map<int,int>::iterator it = fdg.begin();
	// std::cout << (cit == it); //TODO: проверить на ft::! 
}