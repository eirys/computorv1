/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:29:23 by eli               #+#    #+#             */
/*   Updated: 2022/12/23 16:25:36 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP

# include <type_traits>

namespace math {
	/* -- PROTOTYPES ---------------------------------------------- */
	template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value
		|| std::is_integral<T>::value>::type>
	T
		abs(const T& x);

	template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value
		|| std::is_integral<T>::value>::type>
	double
		sqrt(const T& x);


	/* -- FUNCTION DEFINITIONS ------------------------------------ */
	template <typename T,
		typename = typename std::enable_if<std::is_floating_point<T>::value
		|| std::is_integral<T>::value>::type>
	inline T
		abs(const T& x) {
			return (x < 0) ? -x : x;
		}

	/* Fast inverse square root (Quake III algorithm) */
	template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value
		|| std::is_integral<T>::value>::type>
	double
		sqrt(const T& x) {
		}
}

#endif
