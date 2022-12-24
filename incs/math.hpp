/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:29:23 by eli               #+#    #+#             */
/*   Updated: 2022/12/24 14:55:08 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP

# include <type_traits>

# define SQRT_DEPTH 20 // Bigger = better precision

namespace math {

	/* -- PROTOTYPES ---------------------------------------------------------------------------- */

	template <typename T>
		T abs(const T& x);

	template <typename T, typename U>
		T binomial_coefficient(const T& n, const U& p);

	template <typename T>
		T factorial(const T& n);

	template <typename T, typename U>
		T pow(const T& n, const U& exp);

	template <typename T>
		T sqrt(const T& x);

	/* -- DEFINITIONS --------------------------------------------------------------------------- */

	/*
	**  | x |
	*/
	template <typename T>
	inline T
		abs(const T& x) {
			return (x < 0) ? -x : x;
		}

	/*
	**  / n \          n!
	** |     |  =  ----------
	**  \ p /       (n - p)!
	*/
	template <typename T, typename U>
	inline T
		binomial_coefficient(const T& n, const U& p) {
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
	inline T
		factorial(const T& n) {
			if (n == 1 || n == 0)
				return 1;
			return n * factorial(n - 1);
		}


	/*
	**  n ^ exp
	*/
	template <typename T, typename U>
	inline T
		pow(const T& n, const U& exp) {
			if (exp == 0 || n == 1)
				return 1;
			else if (n == 0)
				return 0;
			else
				return n * pow(n, exp - 1);
		}

	/*   ___
	**  √ x    cf. Taylor Series:
	**            (1 + x) ^ .5
	*/
	template <typename T>
	inline T
		sqrt(const T& val) {
			const size_t	exponent = std::to_string(static_cast<long long>(val)).size();
			const double	x = (val / pow(val, exponent)) - 1;
			T				sum = 0;
			for (T i = 0; i < SQRT_DEPTH; ++i)
				sum += binomial_coefficient(.5, i) * pow(x, i);
			if (exponent % 2 == 0)
				return sum * pow(10, exponent * .5);
			else
				return sum * 3.16227766017 * pow(10, (exponent - 1) * .5);
		}
}

#endif
