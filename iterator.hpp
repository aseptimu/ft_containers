#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iterator> // TODO: одумайся!

namespace ft
{

// Iteratro tags
struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// Base class iterator tmeplate
template < class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

// Iterator traits
template <class Iterator> 
struct iterator_traits
{
	typedef	Iterator								iterator_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T> 
struct iterator_traits<T*>
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <class T>
class random_access_iterator
{
public:
	typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
	typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
	typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
	typedef typename iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category; //TODO: костыль для теста
	typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
	typedef	T*																	iterator_type; // TODO: костыль для теста

	random_access_iterator() : _ptr(NULL) { }
	random_access_iterator(pointer copy) : _ptr(copy) { }
	random_access_iterator(const random_access_iterator& copy) : _ptr(copy._ptr) { }
	~random_access_iterator() { }
	random_access_iterator& operator= (const random_access_iterator& assign) {
		if (this == &assign)
			return (*this);
		_ptr = assign._ptr;
		return (*this);
	}

	pointer base() const { return (_ptr); }

	bool	operator==(const random_access_iterator& it) const {
		return (*_ptr == *(it._ptr));
	}

	bool	operator!=(const random_access_iterator& it) const {
		return (*_ptr != *(it._ptr));
	}

	reference	operator*(void) const {
		return (*_ptr);
	}
	
	pointer	operator->(void) const {
		return (_ptr);
	}

	random_access_iterator&	operator++ (void) {
		_ptr++;
		return (*this);
	}

	random_access_iterator	operator++ (int) {
		random_access_iterator tmp = *this;
		_ptr++;
		return (tmp);
	}

	random_access_iterator&	operator-- (void) {
		_ptr--;
		return (*this);
	}

	random_access_iterator	operator-- (int) {
		random_access_iterator tmp = *this;
		_ptr--;
		return (tmp);
	}

	random_access_iterator operator+ (difference_type n) const {
		return (_ptr + n);
	}

	random_access_iterator operator- (difference_type n) const {
		return (_ptr - n);
	}

	random_access_iterator& operator+= (difference_type n) {
		_ptr += n;
		return (*this);
	}

	random_access_iterator& operator-= (difference_type n) {
		_ptr -= n;
		return (*this);
	}

	reference	operator[](difference_type n) {
		return (*(_ptr + n));
	}


private:
	pointer _ptr;
};
	template <typename Tl>
	typename ft::random_access_iterator<Tl>::difference_type
	operator-(const ft::random_access_iterator<Tl> lhs,
			const ft::random_access_iterator<Tl> rhs) {	return (lhs.base() - rhs.base()); }



template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

	reverse_iterator() : _iter() {}
	explicit reverse_iterator (iterator_type it) : _iter(it) {}
	template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _iter(rev_it.base()) {}

	
	iterator_type base() const { return (_iter); }
	reference operator*() const { iterator_type tmp = _iter; return *--tmp;}
	reverse_iterator operator+ (difference_type n) const { return reverse_iterator(_iter - n); }
	reverse_iterator& operator++() { --_iter; return (*this); }
	reverse_iterator  operator++(int) { reverse_iterator tmp = *this; --_iter; return tmp; }
	reverse_iterator& operator+= (difference_type n) { _iter -= n; return (*this); }
	reverse_iterator operator- (difference_type n) const { return reverse_iterator(_iter + n); }
	reverse_iterator& operator--() { ++_iter; return (*this); }
	reverse_iterator  operator--(int) { reverse_iterator tmp = *this; ++_iter; return tmp; }
	reverse_iterator& operator-= (difference_type n) { _iter += n; return (*this); }
	pointer operator->() const { return &(operator*()); }
	reference operator[] (difference_type n) const { return (*(_iter - n - 1)); }

	// template <class It>
	// friend bool operator== (const reverse_iterator<It>& lhs,
	// 				const reverse_iterator<It>& rhs);
	// template <class It>
	// friend bool operator!= (const reverse_iterator<It>& lhs,
	// 				const reverse_iterator<It>& rhs);
	// template <class It>
	// friend bool operator<  (const reverse_iterator<It>& lhs,
	// 				const reverse_iterator<It>& rhs);
	// template <class It>
	// friend bool operator<= (const reverse_iterator<It>& lhs,
	// 				const reverse_iterator<It>& rhs);
	// template <class It>
	// friend bool operator>  (const reverse_iterator<It>& lhs,
	// 				const reverse_iterator<It>& rhs);
	// template <class It>
	// friend bool operator>= (const reverse_iterator<It>& lhs,
	// 				const reverse_iterator<It>& rhs);

	// template <class It>
	// friend reverse_iterator<It> operator+ (
	// 			typename reverse_iterator<It>::difference_type n,
	// 			const reverse_iterator<It>& rev_it);
	
	// template <class It>
	// friend typename reverse_iterator<It>::difference_type operator- (
	// 	const reverse_iterator<It>& lhs,
	// 	const reverse_iterator<It>& rhs);

private:
	iterator_type	_iter;
};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); }
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs) { return lhs.base() > rhs.base(); }
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); }

	template <class Iterator>
	reverse_iterator<Iterator>	operator+ (
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it) { return reverse_iterator<Iterator>(rev_it.base() - n); }
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) { return rhs.base() - lhs.base(); } // TODO: уточнить порядок вычитания!!

	template<class It>
	void	do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
						ft::input_iterator_tag)
	{
		while (n > 0) {
			--n;
			++it;
		}
	}

	template<class It>
	void	do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
						ft::bidirectional_iterator_tag)
	{
		while (n > 0) {
			--n;
			++it;
		}
		while (n < 0) {
			++n;
			--it;
		}
	}

	template<class It>
	void	do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
						ft::random_access_iterator_tag)
	{
		it += n;
	}

	template <class InputIterator, class Distance>
	void	advance (InputIterator& it, Distance n)
	{
		do_advance(it, typename ft::iterator_traits<InputIterator>::difference_type(n),
								typename ft::iterator_traits<InputIterator>::iterator_category());
	}

	template <class It>
	typename ft::iterator_traits<It>::differenct_type	do_distance(It first, It last, ft::input_iterator_tag)
	{
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

	template <class It>
	typename ft::iterator_traits<It>::differenct_type	do_distance(It first, It last, std::input_iterator_tag)
	{
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

	template <class It>
	typename ft::iterator_traits<It>::difference_type	do_distance(It first, It last, ft::random_access_iterator_tag)
	{
		return last - first;
	}

	template <class It>
	typename ft::iterator_traits<It>::difference_type	do_distance(It first, It last, std::random_access_iterator_tag)
	{
		return last - first;
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type	distance(InputIterator first, InputIterator last)
	{
		return do_distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
	}

template <class _Tp, class _NodePtr, class _DiffType>
class tree_iterator
{
public:
	typedef bidirectional_iterator_tag	iterator_category;
	typedef _Tp							value_type;
	typedef _DiffType					difference_type;
	typedef value_type&					reference;
};


}
#endif