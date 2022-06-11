/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:38:49 by aseptimu          #+#    #+#             */
/*   Updated: 2022/06/11 14:17:26 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional> // less<Key>
# include "tree.hpp"
# include "tree_balance.hpp"

namespace ft
{

template <	class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair< const Key, T> >
			>
class map
{
public:
	typedef Key									key_type;
	typedef	T									mapped_type;
	typedef pair<const key_type, mapped_type>	value_type;
	typedef Compare								key_compare;
	typedef Alloc								allocator_type;

public:
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		public:
		Compare	comp;
		
		value_compare(Compare c) : comp(c) { }

		public:
		bool operator()(const value_type& x, const value_type& y) const
		{ return comp(x.first, y.first); }
	};

private:
typedef Tree<key_type, value_type, Select1st<value_type>, key_compare, Alloc>	Tree_type;

Tree_type	tree;

public:
	typedef typename Alloc::pointer						pointer;
	typedef typename Alloc::const_pointer				const_pointer;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef typename Tree_type::iterator				iterator;
	typedef typename Tree_type::const_iterator			const_iterator;
	typedef typename Tree_type::size_type				size_type;
	typedef typename Tree_type::difference_type			difference_type;
	typedef typename Tree_type::reverse_iterator		reverse_iterator;
	typedef typename Tree_type::const_reverse_iterator	const_reverse_iterator;

// Constructors, destructor, copy
	map() : tree() { }
	explicit map(const Compare& comp, const allocator_type& alloc = allocator_type()) : tree(comp, Alloc(alloc)) { }
	map(const map& copy) : tree(copy.tree) { }
	template<typename InputIterator>
	map(InputIterator first, InputIterator last) : tree() { tree._insert_range(first, last); }
	template<typename InputIterator>
	map(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a = allocator_type()) : tree(comp, Alloc(a))
	{ tree._insert_range(first, last); }

	map& operator=(const map& assign)
	{
		tree = assign.tree;
		return *this;
	}

	allocator_type	get_allocator() const { return allocator_type(tree.get_allocator()); }

	// Iterators
	iterator	begin() { return tree.begin(); }
	const_iterator	begin() const { return tree.begin(); }
	iterator	end() { return tree.end(); }
	const_iterator	end() const { return tree.end(); }
	reverse_iterator	rbegin() { return tree.rbegin(); }
	const_reverse_iterator	rbegin() const { return tree.rbegin(); }
	reverse_iterator	rend() { return tree.rend(); }
	const_reverse_iterator	rend() const { return tree.rend(); }
	
	// Capacity
	bool	empty() const 
	{ return tree.empty(); }

	size_type	size() const
	{ return tree.size(); }

	size_type	max_size() const
	{ return tree.max_size(); }

	// Element access
	mapped_type&	operator[](const key_type& key)
	{
		iterator	i = lower_bound(key);

		if (i == end() || key_comp()(key ,(*i).first))
			i = insert(i, value_type(key, mapped_type()));
		return (*i).second;
	}

	mapped_type&	at(const key_type& key)
	{
		iterator	i = lower_bound(key);

		if (i == end() || key_comp()(key, (*i).first))
			throw std::out_of_range("map::at:  key not found");
		return (*i).second;
	}

	const mapped_type&	at(const key_type& key) const
	{
		const_iterator	i = lower_bound(key);

		if (i == end() || key_comp()(key, (*i).first))
			throw std::out_of_range("map::at:  key not found");
		return (*i).second;
	}

	// Modifiers
	ft::pair<iterator, bool>	insert(const value_type& val)
	{ return tree._insert_unique(val); }

	iterator	insert(iterator pos, const value_type& val)
	{ return tree._insert_(pos, val); }

	template < typename InputIterator >
	void	insert(InputIterator first, InputIterator last)
	{ tree._insert_range(first, last); }

	void	erase(iterator pos)
	{ tree.erase(pos); }

	size_type	erase(const key_type& key)
	{ return tree.erase(key); }

	void	erase(iterator first, iterator last)
	{ tree.erase(first, last); }

	void	swap(map& map)
	{ tree.swap(map.tree); }

	void	clear()
	{ tree.clear(); }

	key_compare	key_comp() const
	{ return tree.key_comp(); }

	value_compare	value_comp() const
	{ return value_compare(tree.key_comp()); }

	iterator	find(const key_type& key)
	{ return tree.find(key); }

	const_iterator	find(const key_type& key) const
	{ return tree.find(key); }

	size_type	count(const key_type& key) const
	{ return tree.count(key); }

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

	ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{ return tree.equal_range(key); }

	template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
	friend bool operator==(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs);

	template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
	friend bool operator<(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs);

};

template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
bool operator==(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs)
{ return (lhs.tree == rhs.tree); }

template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
bool operator<(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs)
{ return (lhs.tree < rhs.tree); }

template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
bool operator!=(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs)
{ return !(lhs == rhs); }

template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
bool operator>(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs)
{ return (rhs < lhs); }

template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
bool operator<=(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs)
{ return !(rhs < lhs); }

template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
bool operator>=(const map<_Key, _Val, _Comp, _Alloc>& lhs, const map<_Key, _Val, _Comp, _Alloc>& rhs)
{ return !(lhs < rhs); }

template<typename _Key, typename _Val, typename _Comp, typename _Alloc>
void	swap(map<_Key, _Val, _Comp, _Alloc>& x, map<_Key, _Val, _Comp, _Alloc>& y)
{ x.swap(y); }

} // namespace ft


#endif