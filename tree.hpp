#ifndef TREE_HPP
# define TREE_HPP

#include <map>

namespace ft
{

enum _tree_color { _red_n = false, _black_n = true };

template <class Val>
struct Node {
	typedef Node* 		_Node_ptr;
	typedef const Node* _Const_Node_ptr;
	typedef Val			value_type;

	_tree_color			_is_black;
	_Node_ptr			_parent;
	_Node_ptr			_left;
	_Node_ptr			_right;
	value_type			_value;
	size_t				_node_count; // Возможно стоит перенести в дерево

Node() // может стоит добавить конструктор с инициализацией полей?
{
	_is_black = _red_n;
	_parent = 0;
	_left = 0;
	_right = 0;
	_node_count = 0;
}

//возможно добавить метод или конструктор копирования

static _Node_ptr	_Node_min(_Node_ptr _n) throw()
{
	while (_n->_left != 0)
		_n = _n->_left;
	return (_n);
}

static _Const_Node_ptr	_Node_min(_Const_Node_ptr _n) throw()
{
	while (_n->_left != 0)
		_n = _n->_left;
	return (_n);
}

static _Node_ptr	_Node_max(_Node_ptr _n) throw()
{
	while (_n->_right != 0)
		_n = _n->_right;
	return (_n);
}

static _Const_Node_ptr	_Node_max(_Const_Node_ptr _n) throw()
{
	while (_n->_right != 0)
		_n = _n->_right;
	return (_n);
} //TODO: нужно ли?




};

template < class T >
struct TreeIterator
{
	typedef T							value_type;
	typedef T&							reference;
	typedef T*							pointer;

	typedef bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t					difference_type;

	typedef typename Node<T>::_Node_ptr	Node_ptr;
	typedef TreeIterator<T>				iterator;

	TreeIterator() : _node() {}
	explicit TreeIterator(Node_ptr node) : _node(node) {}

	reference	operator*() const 
	{ return _node->_value;  }

	pointer	operator->() const
	{ return &_node->_value; }

	iterator& operator++()// предусмотреть отсутствие родителя и правого/левого поддерева
	{
		if (_node->right != 0)
		{
			_node = _node->right;
			while (_node->left)
				_node = _node->left;
		}
		else
		{
			Node_ptr	tmp = _node->parent;
			while (tmp->right == _node)
			{
				_node = tmp;
				tmp = _node->parent;
			}
			if () // TODO: Разобраться! реализуется в зависимости от структуры дерева https://stackoverflow.com/questions/17150544/what-is-the-definition-of-rb-tree-increment-in-bits-stl-tree-h
		}
		return (*this);
	} // https://programmersought.com/article/57362384120/
//https://programmersought.com/article/11974230627/
	iterator operator++(int)
	{
		iterator	tmp = *this;
		++_node;
		return (tmp);
	}

	Node_ptr	_node;
};



template < class T, class Comp = std::less<T>, class Alloc = std::allocator<T> >
class Tree
{
public:
	typedef T														value_type;
	typedef Comp													key_compare;
	typedef Alloc													allocator_type;
	typedef Node<T>													_Node;

	typedef typename allocator_type::reference								reference;
	typedef typename allocator_type::const_reference							const_reference;
	typedef typename allocator_type::pointer									pointer;
	typedef typename allocator_type::const_pointer							const_pointer;

	typedef typename allocator_type::template rebind<_Node>::other	_node_allocator;

	// typedef typename TreeIterator<T>								iterator;
	// typedef typename ConstTreeIterator<T>							const_iterator;
	// typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	// typedef typename ft::reverse_iterator<const iterator>			const_reverse_iterator;

// private:
// 	Node

};

}

#endif