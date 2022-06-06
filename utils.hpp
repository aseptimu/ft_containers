#ifndef UTILS_HPP
# define UTILS_HPP
#include <type_traits> // TODO::delete
namespace ft
{

/* enable_if */
template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

/* is_integral */
template <class T, T v>
struct integral_constant
{
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T,v> type;
	const value_type operator ()() const { return value; }
	operator value_type () const { return value; }
};

typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;


template <class T>	struct _is_integrall							: public false_type {};
template <>			struct _is_integrall<bool>						: public true_type {};
template <>			struct _is_integrall<char>						: public true_type {};
template <>			struct _is_integrall<char16_t>					: public true_type {}; //TODO: не 98й стандарт, но тестер тестит
template <>			struct _is_integrall<char32_t>					: public true_type {}; //TODO: не 98й стандарт, но тестер тестит
template <>			struct _is_integrall<wchar_t>					: public true_type {};
template <>			struct _is_integrall<signed char>				: public true_type {};
template <>			struct _is_integrall<short int>					: public true_type {};
template <>			struct _is_integrall<int>						: public true_type {};
template <>			struct _is_integrall<long int>					: public true_type {};
template <>			struct _is_integrall<long long int>				: public true_type {};
template <>			struct _is_integrall<unsigned char>				: public true_type {};
template <>			struct _is_integrall<unsigned short int>		: public true_type {};
template <>			struct _is_integrall<unsigned int>				: public true_type {};
template <>			struct _is_integrall<unsigned long int>			: public true_type {};
template <>			struct _is_integrall<unsigned long long int>	: public true_type {};

template <class T> struct	_remove_const	{typedef T type;};
template <class T> struct	_remove_const<const T>{typedef T type;};

template <class T> 
struct is_integral : public _is_integrall<typename _remove_const<T>::type> { };

/* is_iterator */
template <class _Iter>
struct is_iterator
{
private:
	struct _two{char _trash; char _trashh;};
	template <class _It> static _two _test(...);
	template <class _It> static char _test(typename _It::iterator_category* = 0);
public:
	static const bool	value = sizeof(_test<_Iter>(0)) == 1;
};

/* other */
template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2)
{
	while (first1 != last1) {
		if (!(*first1 == *first2))
			return (false);
		++first1; ++first2;
	}
	return (true);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred)
{
	while (first1 != last1) {
		if (!pred(*first1, *first2))
			return (false);
		++first1; ++first2;
	}
	return (true);
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1) return (false);
		else if (*first1 < *first2) return (true);
		++first1; ++first2;
	}
	return (first2!=last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp)
{
	while (first1 != last1)
	{
		if (first2 == last2 || comp(*first2, *first1)) return (false);
		else if (comp(*first1, *first2)) return (true);
		++first1; ++first2;
	}
	return (first2!=last2);
}

template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}

/* pair */
template <class T1, class T2>
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	first_type	first;
	second_type	second;

	pair() : first(), second() {}
	template <class U, class V> 
		pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
	pair (const first_type& a, const second_type& b) : first(a), second(b) {}

	pair& operator= (const pair& pr) {
		this->first = pr.first;
		this->second = pr.second;
		return (*this);
	}

};

template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs==rhs); }

template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(rhs<lhs); }

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return rhs<lhs; }

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs<rhs); }

template <class T1, class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{ return pair<T1, T2> (x, y); }

template < typename Pair >
struct Select1st
{
	typename Pair::first_type& operator()(Pair& x) const
	{ return x.first; }

	const typename Pair::first_type& operator()(const Pair& x) const
	{ return x.first; }
};


} // namespace ft


#endif