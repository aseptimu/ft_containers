/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:39:10 by aseptimu          #+#    #+#             */
/*   Updated: 2022/05/24 12:02:05 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
template < class T, class Container = ft::vector<T> >
class stack
{
public:
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef Container							container_type;
	typedef typename Container::const_reference	const_reference;
protected:
	Container c;

public:
	explicit stack () : c() {}
	explicit stack(const Container& __c) : c(__c) {}
	~stack() {}

	bool				empty() const { return c.empty(); }
	size_type			size() const { return c.size(); }
	value_type& 		top() { return c.back(); }
	const value_type&	top() const { return c.back(); }
	void				push(const value_type& val) { c.push_back(val); }
	void				pop() { return c.pop_back(); }

	stack& operator= (const stack& assign) {c = assign.c; return (*this); }

	template <class T1, class C1>//перетащить все перегрузки операторов в non-member
		bool operator== (const stack<T1,C1>& rhs) { return c == rhs.c; }

	template <class T1, class C1>
		bool operator!= (const stack<T1,C1>& rhs) { return c != rhs.c; }

	template <class T1, class C1>
		bool operator<  (const stack<T1,C1>& rhs) { return c < rhs.c; }

	template <class T1, class C1>
		bool operator<= (const stack<T1,C1>& rhs) { return c <= rhs.c; }

	template <class T1, class C1>
		bool operator>  (const stack<T1,C1>& rhs) { return c > rhs.c; }

	template <class T1, class C1>
		bool operator>= (const stack<T1,C1>& rhs) { return c >= rhs.c; }
};
}

#endif
