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

# include "utils.hpp"
# include <functional> // less<Key>
# include "iterator.hpp"

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
	typedef std::size_t							size_type
	typedef std::ptrdiff_t						difference_type;
	typedef Compare								key_compare;
	typedef Alloc								allocator_type;
	typedef value_type&							reference;
	typedef const value_type					const_reference;
	typedef typename Alloc::pointer				pointer;
	typedef typename Alloc::const_pointer		const_pointer;
	// TODO: iterator typedef
	// typedef map_iterator<typename _tree</* TODO: */>::iterator>				iterator;
	// typedef map_const_iterator<typename _tree</* TODO: */>::const_iterator>	const_iterator;
	// typedef reverse_iterator<iterator>										reverse_iterator;
	// typedef reverse_iterator<const_iterator>								const_reverse_iterator;

	// template <typename T>
	// class value_compare
	// {
	// private:
	// 
	
	// public:
	// 
	// };

private:
};


} // namespace ft


#endif