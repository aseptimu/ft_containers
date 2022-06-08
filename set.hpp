#ifndef SET_HPP
# define SET_HPP

# include "tree_balance.hpp"

namespace ft
{
	
template < typename Key, typename Comp = std::less<Key>, typename Alloc = std::allocator<Key> >
class set
{
public:
	typedef	Key		key_type;
	typedef Key		value_type;
	typedef Comp	key_compare;
	typedef Comp	value_compare;
	typedef Alloc	allocator_type;

private:
	typedef Tree<key_type, value_type, Identity<value_type>, key_compare, Alloc>	Tree_type;

	Tree_type	tree;

public:
	typedef typename Alloc::pointer						pointer;
	typedef typename Alloc::const_pointer				const_pointer;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef typename Tree_type::const_iterator			iterator;
	typedef typename Tree_type::const_iterator			const_iterator;
	typedef typename Tree_type::size_type				size_type;
	typedef typename Tree_type::difference_type			difference_type;
	typedef typename Tree_type::const_reverse_iterator	reverse_iterator;
	typedef typename Tree_type::const_reverse_iterator	const_reverse_iterator;

	// Member functions
	set() : tree() { }
	explicit set(const Comp& comp, const allocator_type& alloc = allocator_type()) : tree(comp, Alloc(alloc)) { }
	template < typename InputIterator >
	set(InputIterator first, InputIterator last) : tree()
	{ tree._insert_range(first, last); }
	template < typename InputIterator >
	set(InputIterator first, InputIterator last, const Comp& comp, const allocator_type& alloc = allocator_type()) : tree(comp, Alloc(alloc))
	{ tree._insert_range(first, last); }
	set(const set& copy) : tree(copy.tree) { }
	set& operator=(const set& assign)
	{
		tree = assign.tree;
		return *this;
	}

	// Accessors
	key_compare	key_comp() const { return tree.key_comp(); }
	value_compare	value_comp() const { return tree.key_comp(); }
	allocator_type	get_allocator() const { return tree.get_allocator(); }
	iterator	begin() const { return tree.begin(); }
	iterator	end() const { return tree.end(); }
	reverse_iterator	rbegin() const { return tree.rbegin(); }
	reverse_iterator	rend() const { return tree.rend(); }

	// Capacity
	bool	empty() const { return tree.empty(); }
	size_type	size() const { return tree.size(); }
	size_type	max_size() const { return tree.max_size(); }

	void	swap(set& s) { tree.swap(s.tree); }

	// Modifiers
	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		ft::pair<typename Tree_type::iterator, bool> p = tree._insert_unique(val);
		return ft::pair<iterator, bool>(p.first, p.second);	
	}

	iterator	insert(const_iterator position, const value_type& val)
	{ return tree._insert_(position, val); }

	template<typename InputIterator>
	void	insert(InputIterator first, InputIterator last)
	{ tree._insert_range(first, last); }

	void	erase(iterator position) { tree.erase(position); }

	size_type	erase(const key_type& key)
	{ return tree.erase(key); }

	void	erase(iterator first, iterator last)
	{ tree.erase(first, last); }

	void	clear ()
	{ tree.clear(); }

	// Operations
	size_type count(const key_type& key) const
	{ return tree.count(key); }

	iterator find(const key_type& key)
	{ return tree.find(key); }

	const_iterator	find(const key_type& key) const
	{ return tree.find(key); }

	iterator	lower_bound(const key_type& key)
	{ return tree.lower_bound(key); }

	const_iterator	lower_bound(const key_type& key) const
	{ return tree.lower_bound(key); }

	iterator	upper_bound(const key_type& key)
	{ return tree.upper_bound(key); }

	const_iterator	upper_bound(const key_type& key) const
	{ return tree.upper_bound(key); }

	ft::pair<iterator, iterator>	equal_range(const key_type& key)
	{ return tree.equal_range(key); }

	ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const
	{ return tree.equal_range(key); }

	template<typename _Key, typename _Comp, typename _Alloc>
	friend bool	operator==(const set<_Key, _Comp, _Alloc>& lhs, const set<_Key, _Comp, _Alloc>& rhs);

	template<typename _Key, typename _Comp, typename _Alloc>
	friend bool	operator<(const set<_Key, _Comp, _Alloc>& lhs, const set<_Key, _Comp, _Alloc>& rhs);
};

template<typename Key, typename Comp, typename Alloc>
bool	operator==(const set<Key, Comp, Alloc>& lhs, const set<Key, Comp, Alloc>& rhs)
{ return (lhs.tree == rhs.tree); }

template<typename Key, typename Comp, typename Alloc>
bool	operator<(const set<Key, Comp, Alloc>& lhs, const set<Key, Comp, Alloc>& rhs)
{ return (lhs.tree < rhs.tree); }

template<typename Key, typename Comp, typename Alloc>
bool	operator!=(const set<Key, Comp, Alloc>& lhs, const set<Key, Comp, Alloc>& rhs)
{ return !(lhs == rhs); }

template<typename Key, typename Comp, typename Alloc>
bool	operator>(const set<Key, Comp, Alloc>& lhs, const set<Key, Comp, Alloc>& rhs)
{ return (rhs < lhs); }

template<typename Key, typename Comp, typename Alloc>
bool	operator<=(const set<Key, Comp, Alloc>& lhs, const set<Key, Comp, Alloc>& rhs)
{ return !(rhs < lhs); }

template<typename Key, typename Comp, typename Alloc>
bool	operator>=(const set<Key, Comp, Alloc>& lhs, const set<Key, Comp, Alloc>& rhs)
{ return !(lhs < rhs); }

template<typename _Key, typename _Comp, typename _Alloc>
void	swap(set<_Key, _Comp, _Alloc>& x, set<_Key, _Comp, _Alloc>& y)
{ x.swap(y); }

} // namespace ft



#endif