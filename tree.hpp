#ifndef TREE_HPP
# define TREE_HPP

# include "iterator.hpp"
#include <map> // TOOD: delete
// https://programmersought.com/article/57362384120/
//https://programmersought.com/article/11974230627/

namespace ft
{

enum _tree_color { _red_n = false, _black_n = true };

struct NodeBase {
	typedef NodeBase*		_Node_ptr;
	typedef const NodeBase*	_Const_Node_ptr;


	_tree_color			_color;
	_Node_ptr			_parent;
	_Node_ptr			_left;
	_Node_ptr			_right;

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
}

};

struct NodeHeader
{
	NodeBase	_header;
	size_t		_nodeCount;

	NodeHeader()
	{
		_header._color = _red_n;
		_reset();
	}

	void	_move_data(NodeHeader& copy)
	{
		_header._color = copy._header._color;
		_header._parent = copy._header._parent;
		_header._left = copy._header._left;
		_header._right = copy._header._right;
		_header._parent->_parent = &_header;
		_nodeCount = copy._nodeCount;
	}

	void	_reset()
	{
		_header._parent = 0;
		_header._left = &_header;
		_header._right = &_header;
		_nodeCount = 0;
	}
};


template < typename _Val >
struct Node : public NodeBase
{
	typedef Node*	_link;
	_Val	_value;
};

struct TreeBaseIterator
{
	typedef NodeBase::_Node_ptr			_Node_ptr;
	typedef bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t					difference_type;

	_Node_ptr _node;

	void	increment()
	{
		if (_node->_right != 0)
		{
			_node = _node->_right;
			while (_node->_left)
				_node = _node->_left;
		}
		else
		{
			_Node_ptr	tmp = _node->_parent;
			while (tmp->_right == _node)
			{
				_node = tmp;
				tmp = _node->_parent;
			}
			if (_node->_right != tmp)
				_node = tmp;
		}
	}

	void	decrement()
	{
		if (_node->_color == _red_n && 
			_node->_parent->_parent == _node)
			_node = _node->_right;
		else if (_node->_left != 0)
		{
			_node = _node->_left;
			while (_node->_right != 0)
				_node = _node->_right;
		}
		else
		{
			_Node_ptr	tmp = _node->_parent;
			while (_node == tmp->_left)
			{
				_node = tmp;
				tmp = tmp->_parent;
			}
			_node = tmp;
		}
	}
};

template < class T >
struct TreeIterator : public TreeBaseIterator
{
	typedef T							value_type;
	typedef T&							reference;
	typedef T*							pointer;
	typedef Node<T>*					_link;

	typedef TreeIterator<T>				iterator;

	TreeIterator() { _node = NULL; }
	explicit TreeIterator(_Node_ptr node) { _node = node; }

	reference	operator*() const 
	{ return static_cast<_link>(_node)->_value;  }

	pointer	operator->() const
	{ return &(operator*()); }

	iterator& operator++()
	{ increment(); return (*this); }
	iterator operator++(int)
	{
		iterator	tmp = *this;
		++_node;
		return (tmp);
	}

	iterator& operator--()
	{ decrement(); return (*this); }
	iterator operator--(int)
	{
		iterator	tmp = *this;
		--_node;
		return (tmp);
	}
	friend bool operator==(const TreeIterator<T>& left, const TreeIterator<T>& right)
	{
		return left._node == right._node;
	}
	friend bool	operator!=(const TreeIterator<T>& left, const TreeIterator<T>& right)
	{
		return left._node != right._node;
	}

};

template < class T >
struct TreeConstIterator : public TreeBaseIterator //TODO:Проверить!
{
	typedef T							value_type;
	typedef const T&					reference;
	typedef const T*					pointer;
	typedef const Node<T>*				_link;

	typedef TreeIterator<T>				iterator;

	TreeConstIterator() {_node = NULL; }
	explicit TreeConstIterator(_Node_ptr node) { _node = node; }
	TreeConstIterator(const iterator& it) { _node = it._node; }

	reference	operator*() const 
	{ return static_cast<_link>(_node)->_value;  }

	pointer	operator->() const
	{ return &(operator*()); }

	iterator& operator++()
	{ increment(); return (*this); }
	iterator operator++(int)
	{
		iterator	tmp = *this;
		++_node;
		return (tmp);
	}

	iterator& operator--()
	{ decrement(); return (*this); }
	iterator operator--(int)
	{
		iterator	tmp = *this;
		--_node;
		return (tmp);
	}
	friend bool operator==(const TreeConstIterator<T>& left, const TreeConstIterator<T>& right)
	{
		return left._node == right._node;
	}
	
	friend bool operator!=(const TreeConstIterator<T>& left, const TreeConstIterator<T>& right)
	{
		return left._node != right._node;
	}
};

template < class Key, class Val, class Comp, class Alloc = std::allocator<Val> >
class Tree
{
	private: // TODO: or protected?
	typedef NodeBase*		_base_ptr;
	typedef const NodeBase* _const_base_ptr;
	typedef Node<Val>		_link;
	typedef const Node<Val>	_const_link;

public:
	typedef Key														key_type;
	typedef Val														value_type;
	typedef value_type*												pointer;
	typedef const value_type*										const_pointer;
	typedef value_type&												reference;
	typedef const value_type&										const_reference;
	typedef size_t													size_type;
	typedef Alloc													allocator_type;
// public:
// 	typedef T														value_type;
// 	typedef Comp													key_compare;
// 	typedef Alloc													allocator_type;
// 	typedef Node<T>													_Node;

// 	typedef typename allocator_type::reference								reference;
// 	typedef typename allocator_type::const_reference							const_reference;
// 	typedef typename allocator_type::pointer									pointer;
// 	typedef typename allocator_type::const_pointer							const_pointer;

	typedef typename allocator_type::template rebind<Node<Val> >::other	_node_allocator; // TODO: перенести в private?

	// typedef typename TreeIterator<T>								iterator;
	// typedef typename ConstTreeIterator<T>							const_iterator;
	// typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	// typedef typename ft::reverse_iterator<const iterator>			const_reverse_iterator;

// private:
// 	Node

};

}

#endif