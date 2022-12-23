/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:26:40 by eli               #+#    #+#             */
/*   Updated: 2022/12/24 00:30:25 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <list>

# define NL std::endl

#if DEBUG == 1
# define LOG(X) std::cerr << X << NL
#else
# define LOG(X)
#endif

namespace utils {

	/* -- PROTOTYPES ---------------------------------------------- */

	template <typename T>
	void
		display(const std::list<T>& l);

	/* -- DEFINITIONS --------------------------------------------- */

	template <typename T>
	inline void
		display(const std::list<T>& l) {
			for (typename std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
				std::cout << '[' << *it << "] ";
			std::cout << std::endl;
		}
}

#endif
