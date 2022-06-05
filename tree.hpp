#ifndef TREE_HPP
# define TREE_HPP

# include "iterator.hpp"
# include "utils.hpp"
#include <map> // TOOD: delete
// https://programmersought.com/article/57362384120/
//https://programmersought.com/article/11974230627/

// _M_insert_range_equal не нужны!
// _M_insert_equal* НЕ НУЖНЫ! Для multi set/map!

namespace ft
{

enum _tree_color { _red_n = false, _black_n = true };

template < typename _Val >
struct Node
{
	typedef Node*			_link;
	typedef const Node*		_Const_link;

	_tree_color	_color;
	_link	_parent;
	_link	_left;
	_link	_right;
	_Val		_value;

static _link	_Node_min(_link _n) throw()
{
	while (_n->_left != 0)
		_n = _n->_left;
	return (_n);
}

static _Const_link	_Node_min(_Const_link _n) throw()
{
	while (_n->_left != 0)
		_n = _n->_left;
	return (_n);
}

static _link	_Node_max(_link _n) throw()
{
	while (_n->_right != 0)
		_n = _n->_right;
	return (_n);
}

static _Const_link	_Node_max(_Const_link _n) throw()
{
	while (_n->_right != 0)
		_n = _n->_right;
	return (_n);
}
};

template < typename _Val >
struct NodeHeader
{
	Node<_Val>	_header;
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

template < typename T >
static Node<T>*	increment(Node<T>* _node)
{
	if (_node->_right != 0)
	{
		_node = _node->_right;
		while (_node->_left)
			_node = _node->_left;
	}
	else
	{
		Node<T>*	tmp = _node->_parent;
		while (tmp->_right == _node)
		{
			_node = tmp;
			tmp = _node->_parent;
		}
		if (_node->_right != tmp)
			_node = tmp;
	}
	return _node;
}

template < typename T >
static Node<T>*	decrement(Node<T>* _node)
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
		Node<T>*	tmp = _node->_parent;
		while (_node == tmp->_left)
		{
			_node = tmp;
			tmp = tmp->_parent;
		}
		_node = tmp;
	}
	return _node;
}

template < class T >
struct TreeIterator
{
	typedef T							value_type;
	typedef T&							reference;
	typedef T*							pointer;
	typedef bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t					difference_type;
	typedef typename Node<T>::_link		_link;
	typedef TreeIterator<T>				iterator;

	_link	_node;
	TreeIterator() { _node = NULL; }
	explicit TreeIterator(_link node) { _node = node; }

	reference	operator*() const 
	{ return static_cast<_link>(_node)->_value;  }

	pointer	operator->() const
	{ return &(operator*()); }

	iterator& operator++()
	{ _node = increment(_node); return (*this); }
	iterator operator++(int)
	{
		iterator	tmp = *this;
		_node = increment(_node);
		return (tmp);
	}

	iterator& operator--()
	{ _node = decrement(_node); return (*this); }
	iterator operator--(int)
	{
		iterator	tmp = *this;
		_node = decrement(_node);
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
struct TreeConstIterator//TODO:Проверить!
{
	typedef T							value_type;
	typedef const T&					reference;
	typedef const T*					pointer;
	typedef bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t					difference_type;
	typedef typename Node<T>::_link		_link;
	typedef TreeIterator<T>				iterator;

	_link	_node;
	TreeConstIterator() {_node = NULL; }
	explicit TreeConstIterator(_link node) { _node = node; }
	TreeConstIterator(const iterator& it) { _node = it._node; }

	reference	operator*() const 
	{ return static_cast<_link>(_node)->_value;  }

	pointer	operator->() const
	{ return &(operator*()); }

	iterator& operator++()
	{ _node = increment(_node); return (*this); }
	iterator operator++(int)
	{
		iterator	tmp = *this;
		_node = increment(_node);
		return (tmp);
	}

	iterator& operator--()
	{ _node = decrement(_node); return (*this); }
	iterator operator--(int)
	{
		iterator	tmp = *this;
		_node = decrement(_node);
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
// private: // TODO: or protected?
	// Node typedef
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
	// typedef std::allocator_traits<_node_allocator>	_alloc_traits; // TODO: c++11!!!

// private: // TODO: or protected?
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
	void	_construct_node(_link node, const value_type& val) // construct node.
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
	struct _tree_impl : public NodeHeader<Val>, public _node_allocator
	{
		_Key_comp	_key_compare;

		_tree_impl() : _node_allocator() { }
		_tree_impl(const _tree_impl& _x) : _node_allocator(), _key_compare(_x._key_compare), NodeHeader<Val>()  {}
		_tree_impl(const _Key_comp& _comp, const _node_allocator& _a) : _node_allocator(_a), _key_compare(_comp) { }
	};

	_tree_impl<Comp> _impl;

//protected?
	// Tree accessors
	_link& _get_root() { return this->_impl._header._parent; }
	_const_link& _get_root() const { return this->_impl._header._parent; }
	_link& _get_min_node() { return this->_impl._header._left; }
	_const_link& _get_min_node() const { return this->_impl._header._left; }
	_link& _get_max_node() { return this->_impl._header._right; }
	_const_link& _get_max_node() const { return this->_impl._header._right; }
	_link	_tree_begin() { return this->_impl._header._parent; }
	_const_link	_tree_begin() const { return this->_impl._header._parent; }
	_link	_tree_end() { return &this->_impl._header; }
	_const_link	_tree_end() const { return &this->_impl._header; }

	// Node accessors
	static const key_type&	_node_key(_const_link node) { return KeyOfValue()(node->_value); }
	static _link	_node_left(_link node) { return node->_left; }
	static _const_link	_node_left(_const_link node) { return node->_left; }
	static _link	_node_right(_link node) { return node->_right; }
	static _const_link	_node_right(_const_link node) { return node->_right; }
	static _link	_min_subtree_node(_link node) { return Node<Val>::_Node_min(node); }
	static _const_link	_min_subtree_node(_const_link node) { return Node<Val>::_Node_min(node); }
	static _link	_max_subtree_node(_link node) { return Node<Val>::_Node_max(node); }
	static _const_link	_max_subtree_node(_const_link node) { return Node<Val>::_Node_max(node); }

	// Iterator typedef
	typedef TreeIterator<value_type>								iterator;
	typedef TreeConstIterator<value_type>							const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	// Prototypes and methods

// private:
	template < typename NodeGen >
	_link	_copy_tree(_link copy, _link parent, NodeGen& node_generator); // Deep copy (every node must be copied)

	template < typename NodeGen >
	_link	_copy_tree(Tree& tree, NodeGen& node_generator)
	{
		_link	root = _copy_tree(tree._tree_begin(), tree._tree_end(), node_generator);
		_get_min_node() = _min_subtree_node(root);
		_get_max_node() = _max_subtree_node(root);
		_impl._nodeCount = tree._impl._nodeCount;
		return (root);
	}

	_link	_copy_tree(const Tree& tree)
	{
		Alloc_node	an(*this);
		return _copy_tree(tree, an);
	}

	void	_erase(_link node); // pure erase without rebalancing
	iterator	_lower_bound(_link begin, _link end, const key_type& key);
	const_iterator	_lower_bound(_const_link begin, _const_link end, const key_type& key) const;
	iterator	_upper_bound(_link begin, _link end, const key_type& key);
	const_iterator	_upper_bound(_const_link begin, _const_link end, const key_type& key) const;

public: // TODO: delete
	// allocation/deallocation
	Tree() { }
	Tree(const Comp& comp, const allocator_type& a = allocator_type()) : _impl(comp, _node_allocator(a)) { }
	Tree(const Tree& tree) : _impl(tree._impl)
	{ 
		if (tree._get_root() != 0)
			_get_root() = _copy_tree(tree);
	}
	~Tree() { _erase(_tree_begin()); }
	Tree& operator=(const Tree& assign);

	// Accessors
	Comp	key_comp() const { return _impl._key_compare; }
	iterator	begin() { return iterator(_impl._header._left); }
	const_iterator	begin() const { return const_iterator(_impl._header._left); }
	iterator	end() { return iterator(&_impl._header); }
	const_iterator	end() const { return const_iterator(&_impl._header); }
	reverse_iterator	rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const { return reverse_iterator(end()); }
	reverse_iterator	rend() { return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }
	bool	empty() const { return _impl._nodeCount == 0; }
	size_type	size() const { return _impl._nodeCount; }
	size_type	max_size() const { return _node_allocator().max_size(); }
	void	swap(Tree& tree); //TODO: сделать

	// Insert/erase

	ft::pair<iterator, bool>	_insert_unique(const value_type& val);

	ft::pair<_link, _link>	get_check_position(const key_type& key);

	ft::pair<_link, _link>	get_insert_hint_pos(const_iterator pos, const key_type& key);

	template < typename NodeGen >
	iterator	_insert_in_tree(_link node, _link parent, const value_type& val, NodeGen& gen);

	template < typename NodeGen >
	iterator	_insert_(const_iterator it, const value_type& val, NodeGen& gen);
	iterator	_insert_(const_iterator it, const value_type& val)
	{
		Alloc_node	an(*this);
		return _insert_(it, val, an);
	}
	template < typename InputIterator >
	void	_insert_range(InputIterator first, InputIterator end)
	{
		Alloc_node	an(*this);

		for(; first != end; ++first)
			_insert_(end(), *first, an);
	}

// private:
	void	_erase_aux(const_iterator pos);
	void	_erase_aux(const_iterator first, const_iterator last);
public: // TODO: what???
	void	erase(iterator	pos)
	{
		if (pos != end()) // TODO: проверить!
			_erase_aux(pos);
	}
	void	erase(const_iterator	pos)
	{
		if (pos != end()) // TODO: проверить!
			_erase_aux(pos);
	}
	size_type	erase(const key_type& key);
	void	erase(iterator first, iterator last) { _erase_aux(first, last); }
	void	erase(const_iterator first, const_iterator last) { _erase_aux(first, last); }

	void	clear()
	{
		_erase(_tree_begin());
		_impl._reset();
	}

// Operations
	iterator	find(const key_type& key);
	const_iterator	find(const key_type& key) const;
	size_type	count(const key_type& key) const;
	iterator	lower_bound(const key_type& key) { return _lower_bound(_tree_begin(), _tree_end(), key); }
	const_iterator	lower_bound(const key_type& key) const { return _lower_bound(_tree_begin(), _tree_end(), key); }
	iterator	upper_bound(const key_type& key) { return _upper_bound(_tree_begin(), _tree_end(), key); }
	const_iterator	upper_bound(const key_type& key) const { return _upper_bound(_tree_begin(), _tree_end(), key); }
	ft::pair<iterator, iterator>	equal_range(const key_type& key);
	ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const;


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

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
Tree<Key, Val, KeyOfValue, Comp, Alloc>& Tree<Key, Val, KeyOfValue, Comp, Alloc>::operator=(const Tree& assign) // TODO: првоерить!
{
	if (this != &assign)
	{
		Alloc_node an(*this); //TODO: обсобенно это проверить!
		_impl._reset(); //TODO: проверить утечки!
		_impl._key_compare = assign._impl._key_compare;
		if (assign._get_root() != 0)
			_get_root() = _copy_tree(assign, an); // TODO: Ещё раз! УТЕЧКИ!
	}
	return (*this);
}

// Insert

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
ft::pair<typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::_link, typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::_link>	
Tree<Key, Val, KeyOfValue, Comp, Alloc>::get_check_position(const key_type& key)
{
	typedef ft::pair<_link, _link>	res;
	_link		node = _tree_begin();
	_link	prev = _tree_end();
	bool	compare = true;
	
	while(node != 0) // going to leaf
	{
		prev = node;
		compare = _impl._key_compare(key, _node_key(node));
		node = compare ? _node_left(node) : _node_right(node);
	}
	iterator check = iterator(prev);
	if (compare) // if left leaf reached
	{
		if (check == begin()) // if the minimum value is insert
			return res(node, prev);
		else
			--check; // go back to check that the value is unique		
	}
	if (_impl._key_compare(_node_key(check._node), key)) // if value is unique
		return res(node, prev);
	return res(check._node, 0);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
ft::pair<typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::_link, typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::_link>	
Tree<Key, Val, KeyOfValue, Comp, Alloc>::get_insert_hint_pos(const_iterator pos, const key_type& key)
{
	typedef	pair<_link, _link>	res;
	iterator	position = iterator(const_cast<_link>(pos._node));

	if (position._node == _tree_end())
	{
		if (size() > 0 && _impl._key_compare(_node_key(_get_max_node()), key))
			return res(0, _get_max_node());
		else
			return get_check_position(key);
	}
	else if(_impl._key_compare(key, _node_key(position._node)))
	{
		iterator	before = position;
		if (position._node == _get_min_node())
			return res(_get_min_node(), _get_min_node());
		else if (_impl._key_compare(_node_key((--before)._node), key))
		{
			if (_node_right(before._node) == 0)
				return res(0, before._node);
			else
				return res(position._node, position._node);
		}
			return get_check_position(key);
	}
	else if(_impl._key_compare(_node_key(position._node), key))
	{
		iterator	after = position;
		if (position._node == _get_max_node())
			return res(0, _get_max_node());
		else if (_impl._key_compare(key, _node_key((++after)._node)))
		{
			if (_node_right(position._node) == 0)
				return res(0, position._node);
			else
				return res(after._node, after._node);
		}
		else
			return get_check_position(key);
	}
	else
		return res(position._node, 0);
}

//
template < typename Val >
void	tree_insert_and_rebalance(const bool insert_left, Node<Val>* node, Node<Val>* parent, Node<Val>& header);

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
template < typename NodeGen >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_insert_in_tree(_link node, _link parent, const value_type& val, NodeGen& gen)
{
	bool	insert_left = (node != 0 || parent == _tree_end() || _impl._key_compare(KeyOfValue()(val), _node_key(parent)));
	_link	n = _create_node(val);

	tree_insert_and_rebalance(insert_left, n, parent, _impl._header);
	++_impl._nodeCount;
	return iterator(n);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
template < typename NodeGen >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_insert_(const_iterator it, const value_type& val, NodeGen& gen)
{
	ft::pair<_link, _link> res = get_insert_hint_pos(it, KeyOfValue()(val));

	if (res.second)
		return (_insert_in_tree(res.first, res.second, val, gen));
	return iterator(res.first);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
ft::pair<typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator, bool>	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_insert_unique(const value_type& val)
{
	typedef	pair<iterator, bool>	Res;
	pair<_link, _link> 	res = get_check_position(KeyOfValue()(val));

	if (res.second)
	{
		Alloc_node	an(*this);
		return Res(_insert_in_tree(res.first, res.second, val, an), true);
	}
	return Res(iterator(res.first), false);
}

// Erase

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
void	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_erase_aux(const_iterator pos)
{
	_link	del = tree_rebalance_for_erase(pos._node, _impl._header);

	_drop_node(del);
	--_impl._nodeCount;
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
void	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_erase_aux(const_iterator first, const_iterator last)
{
	if (first == begin() && last == end())
		clear();
	else
	{
		while (first != last)
			_erase_aux(first++);
	}
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
Tree<Key, Val, KeyOfValue, Comp, Alloc>::size_type	Tree<Key, Val, KeyOfValue, Comp, Alloc>::erase(const key_type& key)
{
	pair<iterator, iterator> del = equal_range(key);
	const size_type	old_size = size();

	_erase_aux(del.first, del.second);
	return (old_size - size());
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
template < typename NodeGen >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::_link	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_copy_tree(_link copy, _link parent, NodeGen& gen) // TODO: проверить!!
{
	_link	top = _clone_node(copy, gen);

	top->_parent = parent;
	try
	{
		if (copy->_right)
			top->_right = _copy_tree(_node_right(copy), top, gen);
		parent = top;
		copy = copy->_left;
		while (copy != 0)
		{
			_link tmp = _clone_node(copy, gen);
			parent->_left = tmp;
			tmp->_parent = parent;
			if (copy->_right)
				tmp->_right = _copy_tree(_node_right(copy), tmp, gen);
			parent = tmp;
			copy = _node_left(copy);
		}		
	}
	catch(...)
	{
		_erase(top);
		throw ;
	}
	return (top);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
void	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_erase(_link node) //pure erase without rebalance
{
	while (node != 0)
	{
		_erase(_node_right(node));
		_link	tmp = _node_left(node);
		_drop_node(node);
		node = tmp;
	}
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_lower_bound(_link begin, _link end, const key_type& key)
{
	while (begin != 0)
	{
		if (!_impl._key_compare(_node_key(begin), key))
		{
			end = begin;
			begin = _node_left(begin);
		}
		else
			begin = _node_right(begin); 
	}
	return iterator(end);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::const_iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_lower_bound(_const_link begin, _const_link end, const key_type& key) const
{
	while (begin != 0)
	{
		if (!_impl._key_compare(_node_key(begin), key))
		{
			end = begin;
			begin = _node_left(begin);
		}
		else
			begin = _node_right(begin); 
	}
	return const_iterator(end);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_upper_bound(_link begin, _link end, const key_type& key)
{
	while (begin != 0)
	{
		if (_impl._key_compare(key, _node_key(begin)))
		{
			end = begin;
			begin = _node_left(begin);
		}
		else
			begin = _node_right(begin); 
	}
	return iterator(end);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::const_iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::_upper_bound(_const_link begin, _const_link end, const key_type& key) const
{
	while (begin != 0)
	{
		if (_impl._key_compare(key, _node_key(begin)))
		{
			end = begin;
			begin = _node_left(begin);
		}
		else
			begin = _node_right(begin);
	}
	return const_iterator(end);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
ft::pair<typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator, typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator>
Tree<Key, Val, KeyOfValue, Comp, Alloc>::equal_range(const key_type& key) // TODO: проверить!!!
{
	return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
ft::pair<typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::const_iterator, typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::const_iterator>
Tree<Key, Val, KeyOfValue, Comp, Alloc>::equal_range(const key_type& key) const //TODO: ЭТО ТОЖЕ ПРОВЕРИТЬ! В оригинале больше
{
	return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
void	swap(Tree<Key, Val, KeyOfValue, Comp, Alloc>& a, Tree<Key, Val, KeyOfValue, Comp, Alloc>& b)
{
	a.swap(b);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
void	Tree<Key, Val, KeyOfValue, Comp, Alloc>::swap(Tree& tree)
{
	if (_get_root() == 0)
	{
		if (tree._get_root != 0)
			_impl._move_data(tree._impl);
	}
	else if (tree._get_root() == 0)
		tree._impl._move_data(_impl);
	else
	{
		ft::swap(_get_root(), tree._get_root());
		ft::swap(_get_min_node(), tree._get_min_node());
		ft::swap(_get_max_node(), tree._get_max_node());

		_get_root()->_parent = _tree_end();
		tree._get_root()->_parent = tree._tree_end();
		ft::swap(_impl._nodeCount, tree._impl._nodeCount);
	}
	ft::swap(_impl._key_compare, tree._impl._key_compare);
	//TODO: возможно, добавить swap alloc'аторов
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::find(const key_type& key)
{
	iterator	tmp = _lower_bound(_tree_begin(), _tree_end(), key);

	return (tmp == end() || _impl._key_compare(key, _node_key(tmp._node)) ? end() : tmp);
}

template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::const_iterator	Tree<Key, Val, KeyOfValue, Comp, Alloc>::find(const key_type& key) const
{
	const_iterator	tmp = _lower_bound(_tree_begin(), _tree_end(), key);

	return (tmp == end() || _impl._key_compare(key, _node_key(tmp._node)) ? end() : tmp);
}
template < typename Key, typename Val, typename KeyOfValue, typename Comp, typename Alloc >
typename Tree<Key, Val, KeyOfValue, Comp, Alloc>::size_type	Tree<Key, Val, KeyOfValue, Comp, Alloc>::count(const key_type& key) const
{
	const_iterator	it = find(key);

	return (it == end() ? 0 : 1);
}

} // namespace ft

#endif