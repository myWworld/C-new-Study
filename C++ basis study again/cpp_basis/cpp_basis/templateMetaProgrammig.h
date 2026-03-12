#pragma once
#include <iostream>
#include <typeinfo>
#include <vector>

template<int N>
struct Factorial
{
	static const int result = N * Factorial<N - 1>::result;
};

template<>
struct Factorial<1>
{
	static const int result = 1;
};

template<int A, int B>
struct gcd
{
	static const int result = gcd<B, A % B>::result;
};

template<int A>
struct gcd<A, 0>
{
	static const int result = A;
};

template<int N, int D = 1>
struct Ratio
{
private:

	const static int _gcd = gcd<N, D>::result;

public:

	typedef Ratio<N / _gcd, D / _gcd> type;
	static const int num = N / _gcd;
	static const int den = D / _gcd;
};

template<class R1, class R2>
struct _Ratio_add
{
	using type =  Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> ;
};

template<class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

template<class R1, class R2>
struct _Ratio_subtract
{
	using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};


template<class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

template<class R1, class R2>
struct _Ratio_multiply
{
	using type = Ratio<R1::num *  R2::num, R1::den* R2::den>;
};


template<class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

template<class R1, class R2>
struct _Ratio_divide
{
	using type = Ratio<R1::num * R2::den, R1::den* R2::num>;
};


template<class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

template<typename U, typename V, typename W>
struct Dim
{
	using M = U;
	using L = V;
	using T = W;

	using type = Dim<M, L, T>;
};

template<typename U, typename V>
struct add_dim_
{
	typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,
		typename Ratio_add<typename U::L, typename V::L>::type,
		typename Ratio_add<typename U::T, typename V::T>::type>
		type;

};


template<typename U, typename V>
struct subtract_dim_
{
	typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
		typename Ratio_subtract<typename U::L, typename V::L>::type,
		typename Ratio_subtract<typename U::T, typename V::T>::type>
		type;

};

template<typename T, typename D>
struct quantity
{
	T q;
	using dim_type = D;

	quantity operator+(quantity<T, D> quant)
	{
		return quantity<T, D>(q + quant.q);
	}

	quantity operator-(quantity<T, D> quant)
	{
		return quantity<T, D>(q - quant.q);
	}

	template<typename D2>
	quantity <T, typename add_dim_<D, D2>::type> operator* (quantity<T, D2> quant)
	{
		return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
	}

	template<typename D2>
	quantity <T, typename subtract_dim_<D, D2>::type> operator/ (quantity<T, D2> quant)
	{
		return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
	}

	quantity<T, D> operator *(T scalar) { return quantity<T, D>(q * scalar); }
	quantity<T, D> operator /(T scalar) { return quantity<T, D>(q / scalar); }

	quantity(T q) : q(q){}

};

template<typename T, typename D>
std::ostream& operator << (std::ostream& out, const quantity<T, D>& q)
{
	out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den << "s^" << D::T::num / D::T::den;
	return out;
}


//int main()
//{
//	std::vector<int> v;
//	v.push_back(4);
//	v.push_back(5);
//	v.push_back(2);
//	v.push_back(1);
//
//	for (std::vector<int>::iterator itr = v.begin(); itr != v.end(); itr++)
//	{
//		std::cout << *itr << std::endl;
//	}
//	std::cout << *(v.begin() + 2) << std::endl;
//
//	v.insert(v.begin() + 2, 2);
//
//	for (std::vector<int>::iterator itr = v.begin(); itr != v.end(); itr++)
//	{
//		std::cout << *itr << std::endl;
//	}
//
//	v.erase(v.begin());
//
//	for (std::vector<int>::iterator itr = v.begin(); itr != v.end(); itr++)
//	{
//		std::cout << *itr << std::endl;
//	}
//}

template<int A>
struct fibo
{
	static_assert(A >= 0, "must be non-negative");

	static const int result = fibo<A - 1>::result + fibo<A - 2>::result;
};


template<>
struct fibo<1>
{
	static const int result = 1;
};

template<>
struct fibo<0>
{
	static const int result = 0;
};

template<int N>
struct INT
{
	static const int num = N;
};

template<typename a, typename b>
struct add
{
	typedef INT<a::num + b::num> result;
};


template<typename a, typename b>
struct divide
{
	typedef INT<a::num / b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template<typename N, typename d>
struct check_div
{
	static const bool result = (N::num % d::num == 0) || check_div<N, typename add<d, one>::result>::result;
};

template<typename N>
struct check_div<N, typename divide<N, two>::result>
{
	static const bool result = (N::num % (N::num / 2) == 0);
};

template<typename N>
struct _is_prime
{

	static const bool result = !check_div<N, two>::result;
};

template<>
struct _is_prime<two>
{
	static const bool result = true;
};

template<>
struct _is_prime<three>
{
	static const bool result = true;
};




template<int N>
struct is_prime
{
	static const bool result = _is_prime<INT<N>>::result;
};

