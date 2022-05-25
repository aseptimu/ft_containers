/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:38:49 by aseptimu          #+#    #+#             */
/*   Updated: 2022/05/25 12:08:07 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"
# include "functional"

namespace ft
{

template <	class _Key,
			class _T,
			class _Compare = std::less<_Key>, // TODO: может быть свою написать?
			class _Alloc = std::allocator<ft::pair< const _Key,_T> >
			>
class map
{
public:
	typedef _Key								key_type;
	typedef	_T									mapped_type;
	typedef pair<const key_type, mapped_type>	value_type;
	typedef _Compare							key_compare;
	typedef value_type&							reference;
	typedef const value_type					const_reference;

private:
};


} // namespace ft


#endif