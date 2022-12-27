/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:29:23 by eli               #+#    #+#             */
/*   Updated: 2022/12/28 00:52:36 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP

# include <cstddef>
# include <string>
# include <type_traits>

# define SQRT_DEPTH 20 // Bigger = better precision

namespace math {

	/* -- PROTOTYPE ----------------------------------------------- */

	template <typename T>
		T abs(const T& x);

	template <typename T, typename U>
		double binomial_coefficient(const T& n, const U& p);

	template <typename T>
		T factorial(const T& n);

	template <typename T, typename U>
		double pow(const T& n, const U& exp);

	template <typename T>
		double sqrt(const T& x);

	template <typename T, typename U>
		int quotient(const T& a, const U& b);

	template <typename T, typename U>
		double remainder(const T& a, const U& b);

	bool isPrime(const long long int& n);

	/* -- DEFINITION ---------------------------------------------- */

	/*
	 **  | x |
	 */
	template <typename T>
		inline T abs(const T& x) {
			return (x < 0) ? -x : x;
		}

	/*
	 **  / n \          n!
	 ** |     |  =  ----------
	 **  \ p /       p!(n - p)!
	 */
	template <typename T, typename U>
		inline double binomial_coefficient(const T& n, const U& p) {
			const T denominator = factorial(p);
			T numerator = 1;
			for (T i = 0; i < p; ++i)
				numerator *= n - i;
			return numerator/denominator;
		}

	/*
	 **  n! = n * (n - 1) * ... * 2 * 1
	 */
	template <typename T>
		inline T factorial(const T& n) {
			if (n == 1 || n == 0)
				return 1;
			return n * factorial(n - 1);
		}


	/*
	 **  n ^ exp
	 */
	template <typename T, typename U>
		inline double pow(const T& n, const U& exp) {
			if (exp == 0 || n == 1)
				return 1;
			else if (n == 0)
				return 0;
			else
				return n * pow(n, exp - 1);
		}

	/*   ___
	 **  √ x    cf. Taylor Series:
	 **            (1 + x) ^ .5 = sum(binomial_coef(.5, k) * x ^ k) for k = [0, inf[
	 */
	template <typename T>
		inline double sqrt(const T& val) {
			const size_t	exponent = std::to_string(static_cast<long long>(val)).size();
			const double	x = (val / pow(10, exponent)) - 1;
			double			sum = 0;
			for (T i = 0; i < SQRT_DEPTH; ++i)
				sum += binomial_coefficient(.5, i) * pow(x, i);
			if (exponent % 2 == 0)
				return sum * pow(10, exponent * .5);
			else
				return sum * 3.16227766017 * pow(10, (exponent - 1) * .5);
		}

	template <typename T, typename U>
		inline int quotient(const T& a, const U& b) {
			int q = 0;
			while (a - (q + 1) * b > 0)
				++q;
			return q;
		}

	template <typename T, typename U>
		inline double remainder(const T& a, const U& b) {
			const int q = quotient(a, b);
			return a - (q * b);
		}

	inline bool isPrime(const long long int& n) {
		if (math::abs(n) < 2)
			return false;
		const int	limit = sqrt(n);
		int			i = 2;

		while (i < limit) {
			if (remainder(n, i))
				return false;
			++i;
		}
		return true;
	}

	inline long long int nearestPrime(const long long int& n) {
		if (isPrime(n))
			return n;
		long long int	limit = sqrt(n);

		while (limit) {
			if (remainder(n, limit))
				break;
			--limit;
		}
		return limit;
	}
}

#endif
