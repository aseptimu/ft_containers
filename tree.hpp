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

template < class Key, class Val, class KeyOfValue, class Comp, class Alloc = std::allocator<Val> >
class Tree
{
private: // TODO: or protected?
	// Node typedef
	typedef NodeBase*			_base_ptr;
	typedef const NodeBase*		_const_base_ptr;
	typedef Node<Val>*			_link;
	typedef const Node<Val>*	_const_link;

public:
	// Basic typedef
	typedef Key					key_type;
	typedef Val					value_type;
	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;
	typedef Alloc				allocator_type;


	typedef typename allocator_type::template rebind<Node<Val> >::other	_node_allocator; // TODO: перенести в private?
	typedef std::allocator_traits<_node_allocator>	_alloc_traits; // c++11!!!

private: // TODO: or protected?
// 	Node
struct Alloc_node
{
	Alloc_node(Tree& tree) : _tree(tree) { }

	template<typename Arg>
	_link	operator()(const Arg& arg) const { return _tree._create_node(arg); }

	Tree& _tree;
};

public: // TODO: delete!!!
	// Node management
	_node_allocator&	_get_node_allocator() { return this->_impl; }
	const _node_allocator&	_get_node_allocator() const { return this->_impl; }
	allocator_type	get_allocator() const { return allocator_type(_get_node_allocator()); }
	_link	_get_node() { return _node_allocator().allocate(1); } // allocate node
	void	_put_node(_link _p) { _node_allocator().deallocate(_p, 1); } // deallocate node
	void	_construct_node(_link node, const value_type& val) // construct node. Try/catch!
	{
		try
		{
			get_allocator().construct(&node->_value, val);
		}
		catch(...)
		{
			_put_node(node);
			throw ;
		}
	}
	_link	_create_node(const value_type& val) // allocate + construct.
	{
		_link	tmp = _get_node();
		_construct_node(tmp, val);
		return tmp;
	}
	void	_destroy_node(_link node) { get_allocator().destroy(&node->_value); } // destruct node
	void	_drop_node(_link node) { _destroy_node(node); _put_node(node); } // destroy + deallocate
	template< typename NodeGen >
	_link	_clone_node(_link copy, NodeGen& gen )
	{ 
		_link	tmp = gen(copy->_value);
		tmp->_color = copy->_color;
		tmp->_left = copy->_left;
		tmp->_right = copy->_right;
		return tmp;
	}

	template < typename _Key_comp > // TODO: может удалить и вынести за структуру?
	struct _tree_impl : public NodeHeader, public _node_allocator
	{
		_Key_comp	_key_compare;

		_tree_impl() : _node_allocator() { }
		_tree_impl(const _tree_impl& _x) : _node_allocator(), _key_compare(_x._key_compare), NodeHeader()  {}
		_tree_impl(const _Key_comp& _comp, const _node_allocator& _a) : _node_allocator(_a), _key_compare(_comp) { }
	};

	_tree_impl<Comp> _impl;

//protected?
	// Tree accessors
	_base_ptr& _get_root() { return this->_impl._header._parent; }
	_const_base_ptr& _get_root() const { return this->_impl._header._parent; }
	_base_ptr& _get_min_node() { return this->_impl._header._left; }
	_const_base_ptr& _get_min_node() const { return this->_impl._header._left; }
	_base_ptr& _get_max_node() { return this->_impl._header._right; }
	_const_base_ptr& _get_max_node() const { return this->_impl._header._right; }
	_link	_tree_begin() { return static_cast<_link>(this->_impl._header._parent); }
	_const_link	_tree_begin() const { return static_cast<_const_link>(this->_impl._header._parent); }
	_base_ptr	_tree_end() { return this->_impl._header; }
	_const_base_ptr	_tree_end() const { return this->_impl._header; }

	// Node accessors
	static const key_type&	_node_key(_const_link node) { return KeyOfValue()(node->_value); }
	static const key_type&	_node_key(_const_base_ptr node) { return _node_key(static_cast<_const_link>(node)); }	
	static _link	_node_left(_base_ptr node) { return static_cast<_link>(node->_left); }
	static _const_link	_node_left(_const_base_ptr node) { return static_cast<_const_link>(node->_left); }
	static _link	_node_right(_base_ptr node) { return static_cast<_link>(node->_right); }
	static _const_link	_node_right(_const_base_ptr node) { return static_cast<_const_link>(node->_right); }
	static _base_ptr	_min_node(_base_ptr node) { return NodeBase::_Node_min(node); }
	static _const_base_ptr	_min_node(_const_base_ptr node) { return NodeBase::_Node_min(node); }
	static _base_ptr	_max_node(_base_ptr node) { return NodeBase::_Node_max(node); }
	static _const_base_ptr	_max_node(_const_base_ptr node) { return NodeBase::_Node_max(node); }

	// Iterator typedef
	typedef TreeIterator<value_type>								iterator;
	typedef TreeConstIterator<value_type>							const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	// Prototypes and methods

	template < typename NodeGen >
	_link	_copy_tree(_link copy, _base_ptr parent, NodeGen& node_generator); // Deep copy (every node must be copied)

	template < typename NodeGen >
	_link	_copy_tree(Tree& tree, NodeGen& node_generator)
	{
		_link	root = _copy_tree(tree._tree_begin(), tree._tree_end(), node_generator);
		_min_node() = NodeBase::_Node_min(root);
		_max_node() = NodeBase::_Node_max(root);
		_impl._nodeCount = tree._impl._nodeCount;
		return (root);
	}

	_link	_copy_tree(const Tree& tree)
	{
		Alloc_node	an(*this);
		return _copy_tree(tree, an);
	}

	// allocation/deallocation
	Tree() { }
	Tree(const Comp& comp, const allocator_type& a = allocator_type()) : _impl(comp, _node_allocator(a)) { }
	Tree(const Tree& tree) : _impl(tree._impl)
	{ 
		if (tree._get_root() != 0)
			_get_root() = _copy_tree(tree);
	}
	// ~Tree() { erase(_tree_begin()) } TODO: erase!
	Tree& operator=(const Tree& assign);

	// Accessors
	Comp	key_comp() const { return _impl._key_compare; }
	iterator	begin() { return iterator(_impl._header._left); }
	const_iterator	begin() const { return const_iterator(_impl._header._left); }
	iterator	end() { return iterator(_impl._header); }
	const_iterator	end() const { return const_iterator(_impl._header); }
	reverse_iterator	rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const { return reverse_iterator(end()); }
	reverse_iterator	rend() { return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }
	bool	empty() const { return _impl._nodeCount == 0; }
	size_type	size() const { return _impl._nodeCount; }
	size_type	max_size() const { return _node_allocator().max_size(); }
	void	swap(Tree& tree); //TODO: сделать

	// Insert/erase

	// Operators
	friend bool	operator==(const Tree& lhs, const Tree& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend bool	operator<(const Tree& lhs, const Tree& rhs) // TODO: другие должны быть?
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

};

// template < class Key, class Val, class KeyOfValue, class Comp, class Alloc >
// template < typename NodeGen >
// typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::_link	Tree<Key, Val, KeyOfValue, Comp, Alloc>::


}

#endif