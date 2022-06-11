/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseptimu <aseptimu@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:38:20 by aseptimu          #+#    #+#             */
/*   Updated: 2022/06/11 10:58:26 by aseptimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"
# include "utils.hpp"
# include <limits>


namespace ft
{
template < class T, class Allocator = std::allocator<T> > 
class vector
{

public:

	typedef T														value_type;
	typedef	Allocator												allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef	std::size_t												size_type;
	typedef std::ptrdiff_t											difference_type;
	typedef typename ft::random_access_iterator<value_type>			iterator;
	typedef typename ft::const_random_access_iterator<value_type>	const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const iterator>			const_reverse_iterator;
	
	

	// Constructors
	explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (size_type n, const value_type& val = value_type(), 
					const allocator_type& alloc = allocator_type());
	template <class InputIterator>
		vector (InputIterator first, typename enable_if<is_iterator<InputIterator>::value, InputIterator>::type last, 
								const allocator_type& alloc = allocator_type());
	vector (const vector& copy);

	// Destructor
	~vector();
	
	// Assign operator
	vector&	operator= (const vector& assign);

	// Iterators
	iterator				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator			end() const;
	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	// Capacity
	size_type	size() const;
	size_type	max_size() const;
	void		resize(size_type n, value_type val = value_type());
	size_type	capacity() const;
	bool		empty() const;
	void		reserve (size_type n);

	// Element access
	reference		operator[] (size_type n);
	const_reference	operator[] (size_type n) const;
	reference		at (size_type n);
	const_reference	at (size_type n) const;
	reference		front();
	const_reference	front() const;
	reference		back();
	const_reference	back() const;

	// Modifiers
	template <class InputIterator>
		void	assign (typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last);
	void		assign (size_type n, const value_type& val);
	void		push_back (const value_type& val);
	void		pop_back();
	iterator	insert (iterator position, const value_type& val);
	void		insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator>
		void	insert (iterator position, typename enable_if<is_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last);
	iterator	erase (iterator position);
	iterator	erase (iterator first, iterator last);
	void		swap (vector& x);
	void		clear();
	
	allocator_type get_allocator() const;

private:
	size_type	_size;
	size_type	_cap;
	Allocator	_alloc;
	pointer		_data;
};

// Constructors
template < class T, class Allocator >
vector< T, Allocator >::vector(const allocator_type& alloc) : _size(0), _cap(0), _alloc(alloc)
{
	_data = _alloc.allocate(0);
}

template < class T, class Allocator >
vector< T, Allocator >::vector(size_type n, const value_type& val, 
							const allocator_type& alloc) : _size(n), _cap(n), _alloc(alloc)
{
	size_type	i;

	_data = _alloc.allocate(n);
	try
	{
		for (i = 0; i < n; i++)
			_alloc.construct(_data + i, val);
	}
	catch(...)
	{
		for (; i > 0; i--)
			_alloc.destroy(_data + i - 1);
		_alloc.deallocate(_data, _cap);
		throw ;
	}	
}

template < class T, class Allocator >
template <class InputIterator>
vector< T, Allocator >::vector (InputIterator first, typename enable_if<is_iterator<InputIterator>::value, InputIterator>::type last, 
								const allocator_type& alloc) : _alloc(alloc)
{
	size_type		i;
	difference_type	sub = last - first;

	_data = _alloc.allocate(sub);
	try
	{
		for (i = 0; first != last; first++, i++)
			_alloc.construct(_data + i, *first);
	}
	catch(...)
	{
		for (; i > 0; i--)
			_alloc.destroy(_data + i - 1);
		_alloc.deallocate(_data, sub);			
	}
	_size = sub;
	_cap = sub;		
}

template < class T, class Allocator >
vector< T, Allocator >::vector (const vector& copy) : _size(copy._size), _cap(copy._cap), _alloc(copy._alloc)
{
	size_type	i;

	_data = _alloc.allocate(copy._cap);
	try
	{
		for (i = 0; i < copy._size; i++)
			_alloc.construct(_data + i, *(copy._data + i));
	}
	catch(...)
	{
		for (; i > 0; i--)
			_alloc.destroy(_data + i - 1);
		_alloc.deallocate(_data, _cap);
		throw ;
	}
	
}

// Destructor
template < class T, class Allocator >
vector< T, Allocator >::~vector()
{
	for (size_type i = 0; i < _size; i++)
		_alloc.destroy(_data + i);
	_alloc.deallocate(_data, _cap);
}

// Assign operator
template < class T, class Allocator >
vector< T, Allocator >&	vector< T, Allocator >::operator= (const vector& assign)
{
	T *tmp;
	size_type i;

	tmp = _alloc.allocate(assign._cap);
	try
	{
		for (i = 0; i < assign._size; i++)
			_alloc.construct(tmp + i, *(assign._data + i));
	}
	catch(...)
	{
		for (; i > 0; i--)
			_alloc.destroy(tmp + i - 1);
		_alloc.deallocate(tmp, _cap);
		throw ;
	}
	for (size_type i = 0; i < _size; i++)
		_alloc.destroy(_data + i);
	_alloc.deallocate(_data, _cap);
	this->_data = tmp;
	this->_size = assign._size;
	this->_cap = assign._cap;
	
	return (*this);
}

// Iterators
template < class T, class Allocator >
typename vector< T, Allocator >::iterator	vector< T, Allocator >::begin()
{
	return (_data);
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_iterator	vector< T, Allocator >::begin() const
{
	return (_data);
}

template < class T, class Allocator >
typename vector< T, Allocator >::iterator	vector< T, Allocator >::end()
{
	return (_data + _size);
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_iterator	vector< T, Allocator >::end() const
{
	return (_data + _size);
}

template < class T, class Allocator >
typename vector< T, Allocator >::reverse_iterator		vector< T, Allocator >::rbegin()
{
	return (reverse_iterator(end()));
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_reverse_iterator	vector< T, Allocator >::rbegin() const
{
	return (reverse_iterator(end()));
}

template < class T, class Allocator >
typename vector< T, Allocator >::reverse_iterator		vector< T, Allocator >::rend()
{
	return (reverse_iterator(begin()));
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_reverse_iterator	vector< T, Allocator >::rend() const
{
		return (reverse_iterator(begin()));
}

// Capacity
template < class T, class Allocator >
typename vector< T, Allocator >::size_type	vector< T, Allocator >::size() const
{
	return _size;
}

template < class T, class Allocator >
typename vector< T, Allocator >::size_type	vector< T, Allocator >::max_size() const
{
	size_type	size = static_cast<size_type>(std::numeric_limits<size_type>::max() / sizeof(value_type));
	size_type	signed_size_max = std::numeric_limits<difference_type>::max();

	if (size < signed_size_max)
		return size;
	return signed_size_max;
}

template < class T, class Allocator >
void		vector< T, Allocator >::resize(size_type n, value_type val)
{
	if (n < _size)
	{
		for (size_type i = n; i < _size; i++)
			_alloc.destroy(_data + i);
	}
	else if (n > _size)
	{
		size_type	recover = _size;
		size_type	i;
		for (i = _size; i < n; i++)
		{
			try
			{
				push_back(val);
			}
			catch(...)
			{
				for (size_type j = _size; j < i; j++)
					_alloc.destroy(_data + j);
				_size = recover;
				throw ;
			}	
		}
	}
	(void) val;
	_size = n;
}

template < class T, class Allocator >
typename vector< T, Allocator >::size_type	vector< T, Allocator >::capacity() const
{
	return _cap;
}

template < class T, class Allocator >
bool		vector< T, Allocator >::empty() const
{
	return _size == 0;
}

template < class T, class Allocator >
void		vector< T, Allocator >::reserve (size_type n)
{
	if (n > max_size())
		throw std::length_error("vector");
	if (n > _cap)
	{
		value_type * tmp = _alloc.allocate(n);
		size_type	i;
		try
		{
			for (i = 0; i < _size; i++)
				_alloc.construct(tmp + i, *(_data + i));
		}
		catch(...)
		{
			for  (size_type j = 0; j < i; j++)
				_alloc.destroy(tmp + j);
			_alloc.deallocate(tmp, n);
			throw ;
		}
		for (size_type j = 0; j < _size; j++)
			_alloc.destroy(_data + j);
		_alloc.deallocate(_data, _cap);
		_data = tmp;
		_cap = n;
	}
}

// Element access
template < class T, class Allocator >
typename vector< T, Allocator >::reference		vector< T, Allocator >::operator[] (size_type n)
{
	return *(_data + n);
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_reference	vector< T, Allocator >::operator[] (size_type n) const
{
	return *(_data + n);
}

template < class T, class Allocator >
typename vector< T, Allocator >::reference		vector< T, Allocator >::at (size_type n)
{
	if (n > _size)
		throw std::out_of_range("vector");
	return *(_data + n);
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_reference	vector< T, Allocator >::at (size_type n) const
{
	if (n > _size)
		throw std::out_of_range("vector");
	return *(_data + n);
}

template < class T, class Allocator >
typename vector< T, Allocator >::reference		vector< T, Allocator >::front()
{
	return (*_data);
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_reference	vector< T, Allocator >::front() const
{
	return (*_data);
}

template < class T, class Allocator >
typename vector< T, Allocator >::reference		vector< T, Allocator >::back()
{
	return (*(_data + _size - 1));
}

template < class T, class Allocator >
typename vector< T, Allocator >::const_reference	vector< T, Allocator >::back() const
{
	return (*(_data + _size - 1));
}

// Modifiers
template < class T, class Allocator >
template <class InputIterator>
void	vector< T, Allocator >::assign (typename enable_if<is_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last)
{
	size_type	d = ft::distance(first, last);
	size_type	i;

	this->clear();
	if (d > _cap)
	{
		pointer tmp = _alloc.allocate(d);
		try
		{
			for (i = 0; i < d; ++i, ++first)
				_alloc.construct(tmp + i, *first);
		}
		catch(...)
		{
			for (; i > 0; i--)
				_alloc.destroy(tmp + i - 1);
			_alloc.deallocate(tmp, d);
			_size = 0;
			throw ; 
		}
		_alloc.deallocate(_data, _cap);
		_data = tmp;
		_cap = d;
	}
	else
	{
		try
		{
			for (i = 0; i < d; ++i, ++first)
				_alloc.construct(_data + i, *first);
		}
		catch(...)
		{
			for (; i > 0; i--)
				_alloc.destroy(_data + i - 1);
			_size = 0;
			throw ;
		}
	}
	_size = d;
}

template < class T, class Allocator >
void	vector< T, Allocator >::assign(size_type n, const value_type& val)
{
	size_type	i;

	for (size_type j = 0; j < _size; j++)
		_alloc.destroy(_data + j);
	if (n > _cap)
	{
		pointer	tmp = _alloc.allocate(n);
		for (i = 0; i < n; i++)
		{
			try
			{
				_alloc.construct(tmp + i, val);
			}
			catch(...)
			{
				for (; i > 0; i--)
					_alloc.destroy(tmp + i - 1);
				_alloc.deallocate(tmp, n);
				throw ;
			}
		}
		_alloc.deallocate(_data, _cap);
		_data = tmp;
		_size = n;
		_cap = n;
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			try
			{
				_alloc.construct(_data + i, val);
			}
			catch(...)
			{
				for (; i > 0; i--)
					_alloc.destroy(_data + i - 1);
				_size = 0;
				throw ;				
			}
		}
		_size = n;
	}
}

template < class T, class Allocator >
void		vector< T, Allocator >::push_back (const value_type& val)
{
	if (_cap == 0)
	{
		_alloc.deallocate(_data, 0);
		_data = _alloc.allocate(1);
		_cap++;
	}
	else if (_cap == _size)
	{
		pointer tmp = _alloc.allocate(_cap * 2);
		size_type	i;
		try
		{
			for (i = 0; i < _size; i++)
			{
				_alloc.construct(tmp + i, *(_data + i));
			}
		}
		catch(...)
		{
			for (; i > 0; i++)
				_alloc.destroy(tmp + i - 1);
			_alloc.deallocate(tmp, _cap * 2);
			throw ;
		}
		for (i = 0; i < _size; i++)
			_alloc.destroy(_data + i);
		_alloc.deallocate(_data, _cap);
		_data = tmp;
		_cap *= 2;
	}
	_alloc.construct(_data + _size, val);
	_size++;
}

template < class T, class Allocator >
void		vector< T, Allocator >::pop_back()
{
	_alloc.destroy(_data + _size - 1);
	_size--;
}

template < class T, class Allocator >
typename vector< T, Allocator >::iterator	vector< T, Allocator >::insert (typename vector< T, Allocator >::iterator position, const value_type& val)
{
	size_type	dist = distance(begin(), position);
	size_type	i;

	if (_size < _cap)
	{
		try
		{
			for (i = _size; i > dist; --i)
			{
				_alloc.construct(_data + i, *(_data + i - 1));
				_alloc.destroy(_data + i - 1);
			}
		}
		catch(...)
		{
			for (size_type j = 0; j < i; ++j)
				_alloc.destroy(_data + j);
			for (size_type j = i + 1; j < _size + 1; ++j)
				_alloc.destroy(_data + j);
			_size = 0;
			throw ;
		}
		try
		{
			_alloc.construct(_data + dist, val);
		}
		catch(...)
		{
			for (size_type j = 0; j < _size + 1; j++)
				_alloc.destroy(_data + j);
			_size = 0;
			throw ;
		}
		_size++;
	}
	else
	{
		pointer tmp = _alloc.allocate(_cap * 2);
		try
		{
			for (i = 0; i < dist; ++i)
				_alloc.construct(tmp + i, *(_data + i));
			_alloc.construct(tmp + dist, val);
		}
		catch(...)
		{
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(tmp + j);
			_alloc.deallocate(tmp, _cap * 2);
			throw ;
		}
		try
		{
			for (i = _size; i > dist; i--)
				_alloc.construct(tmp + i, *(_data + i - 1));
		}
		catch(...)
		{
			for (size_type j = 0; j < i; ++j)
				_alloc.destroy(_data + j);
			for (size_type j = i + 1; j < _size + 1; ++j)
				_alloc.destroy(_data + j);
			_alloc.deallocate(tmp, _cap * 2);
			_size = 0;
			throw ;
		}
		for (i = 0; i < _size; i++)
			_alloc.destroy(_data + i);
		_alloc.deallocate(_data, _cap);
		_data = tmp;
		_size++;
		_cap *= 2;		
	}
	return (iterator(_data + dist));
}

template < class T, class Alloc >
void		vector< T, Alloc >::insert (vector< T, Alloc >::iterator position, size_type n, const value_type& val)
{
	size_type	dist = distance(begin(), position);
	size_type	i;

	if (n + _size <= _cap)
	{
		try
		{
			for (i = _size; i > dist; i--) // TODO: было i++
			{
				_alloc.construct(_data + i + n - 1, *(_data + i - 1));
				_alloc.destroy(_data + i - 1);
			}
			for (size_type j = dist + n; j > dist; j--)
				_alloc.construct(_data + j - 1, val);
		}
		catch(...)
		{
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(_data + j);
			for (size_type j = i + 1; j < _size + n; j++)
				_alloc.destroy(_data + j);
			_size = 0;
			throw ;
		}
		_size += n;
	}
	else
	{
		size_type	new_cap = _cap * 2;
		if (new_cap < _cap + n)
			new_cap = _cap + n;
		pointer	tmp = _alloc.allocate(new_cap);
		try
		{
			for (i = 0; i < dist; i++)
				_alloc.construct(tmp + i, *(_data + i));
			for (; i < dist + n; i++)
				_alloc.construct(tmp + i, val);
			for (; i < _size + n; i++)
				_alloc.construct(tmp + i, *(_data + i - n));
		}
		catch(...)
		{
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(tmp + j);
			_alloc.deallocate(tmp, new_cap);
			throw ;
		}
		for (size_type j = 0; j < _size; j++)
			_alloc.destroy(_data + j);
		_alloc.deallocate(_data, _cap);
		_data = tmp;
		_size += n;
		_cap = new_cap;		
	}
		
}

template < class T, class Alloc >
template < class InputIterator >
void	vector< T, Alloc >::insert (vector< T, Alloc >::iterator position, typename enable_if<is_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last)
{
	size_type	beg = distance(begin(), position);
	size_type	dist = ft::distance(first, last);
	size_type	i;

	if (dist + _size <= _cap)
	{
		try
		{
			for (i = _size; i > beg; i--)
			{
				_alloc.construct(_data + i + dist - 1, *(_data + i - 1));
				_alloc.destroy(_data + i - 1);
			}
			for (size_type j = beg + dist; j > beg; j--, last--)
				_alloc.construct(_data + j - 1, *(last - 1));
		}
		catch(...)
		{
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(_data + j);
			for (size_type j = i + 1; j < _size + dist; j++)
				_alloc.destroy(_data + j);
			_size = 0;
			throw ;
		}
		_size += dist;
	}
	else
	{
		size_type	new_cap = _cap * 2;
		if (new_cap < _cap + dist)
			new_cap = _cap + dist;
		pointer	tmp = _alloc.allocate(new_cap);
		try
		{
			for (i = 0; i < beg; i++)
				_alloc.construct(tmp + i, *(_data + i));
			for (; i < beg + dist; i++, ++first)
				_alloc.construct(tmp + i, *first);
			for (; i < _size + dist; i++)
				_alloc.construct(tmp + i, *(_data + i - dist));
		}
		catch(...)
		{
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(tmp + j);
			_alloc.deallocate(tmp, new_cap);
			throw ;
		}
		for (size_type j = 0; j < _size; j++)
			_alloc.destroy(_data + j);
		_alloc.deallocate(_data, _cap);
		_data = tmp;
		_size += dist;
		_cap = new_cap;		
	}
}

template < class T, class Alloc >
typename vector< T, Alloc >::iterator	vector< T, Alloc >::erase (typename vector< T, Alloc >::iterator position)
{
	size_type	d = distance(begin(), position);
	size_type	i;

	for (i = d; i < _size - 1; ++i)
	{
		_alloc.destroy(_data + i);
		try
		{
			_alloc.construct(_data + i, *(_data + i + 1));
		}
		catch(...)
		{
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(_data + j);
			for (size_type j = i + 1; j < _size; j++)
				_alloc.destroy(_data + j);	
			throw ;
		}
	}
	_alloc.destroy(_data + _size - 1);
	--_size;
	return (iterator(_data + d));	
}

template < class T, class Alloc >
typename vector< T, Alloc >::iterator	vector< T, Alloc >::erase (typename vector< T, Alloc >::iterator first, typename vector< T, Alloc >::iterator last)
{
	size_type	beg = distance(begin(), first);
	size_type	dist = distance(first, last);
	size_type	i;

	if (dist == 0)
		return (last);
	for (i = beg; i < dist + beg; i++)
		_alloc.destroy(_data + i);
	for (i = beg + dist ; i < _size; i++)
	{
		try
		{
			_alloc.construct(_data + i - dist, *(_data + i));
		}
		catch(...)
		{
			for (size_type j = 0; j < i - dist; j++)
				_alloc.destroy(_data + j);
			for (size_type j = i; j < _size; j++)
				_alloc.destroy(_data + j);
			_size = 0;
			throw ;
		}
		_alloc.destroy(_data + i);		
	}
	_size -= dist;
	return (iterator(_data + beg));
}

template < class T, class Alloc >
void	vector< T, Alloc >::swap( vector& x )
{
		if (&x == this)
			return;
		size_type		tmp_size = x._size;
		size_type		tmp_cap = x._cap;
		allocator_type	tmp_alloc = x._alloc;
		pointer			tmp_data = x._data;

		x._size = this->_size;
		x._cap = this->_cap;
		x._data = this->_data;
		x._alloc = this->_alloc;

		this->_size = tmp_size;
		this->_cap = tmp_cap;
		this->_data = tmp_data;
		this->_alloc = tmp_alloc;
}

template < class T, class Alloc >
void	vector< T, Alloc >::clear()
{
	for (size_type i = 0; i < _size; i++)
		_alloc.destroy(_data + i);
	_size = 0;
}

template < class T, class Alloc >
typename vector< T, Alloc >::allocator_type vector< T, Alloc >::get_allocator() const
{
	return (_alloc);
}

// Operators

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);

	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs < rhs));
}

} // namespace ft

namespace std
{
	template <class T, class Allocator>
	void	swap( ft::vector<T, Allocator> & lhs,
				ft::vector<T, Allocator> & rhs)
	{
		lhs.swap(rhs);
	}
}

#endif