#ifndef TREE_HPP
# define TREE_HPP

template <class T>
typedef struct Node {
	typedef T	value_type;
	bool 		_is_black;
	Node		*right;
	Node		*left;
	Node		*parent;
};


namespace ft
{

template < class _T, class _Comp = std::less<T>, class 

}

#endif