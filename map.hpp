/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:38:49 by aseptimu          #+#    #+#             */
/*   Updated: 2022/05/25 16:19:50 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional> // less<Key>
# include "tree.hpp"

namespace ft
{

template <	class Key,
			class T,
			class Compare = std::less<Key>, // TODO: может быть свою написать?
			class Alloc = std::allocator<ft::pair< const Key, T> >
			>
class map
{
public:
	typedef Key									key_type;
	typedef	T									mapped_type;
	typedef pair<const key_type, mapped_type>	value_type;
	// typedef std::size_t							size_type
	// typedef std::ptrdiff_t						difference_type;
	typedef Compare								key_compare;
	typedef Alloc								allocator_type;
	// TODO: iterator typedef
	// typedef reverse_iterator<iterator>										reverse_iterator;
	// typedef reverse_iterator<const_iterator>								const_reverse_iterator;

public:
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map<Key, T, Compare, Alloc>;
		protected:
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
	typedef const value_type							const_reference;
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
	~map();

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
	const_reverse_iterator	rend() { return tree.rend(); }
	
	// Capacity
	bool	empty() const 

};


} // namespace ft


#endif