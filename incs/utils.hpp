/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:26:40 by eli               #+#    #+#             */
/*   Updated: 2022/12/23 12:44:32 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <type_traits>
# include <list>
# include <map>

# define NUMBER_STR "0123456789"
# define POLYNOMIAL_STR "0123456789X"
# define NL std::endl

#if DEBUG == 1
# define LOG(X) std::cerr << X << NL
#else
# define LOG(X)
#endif

namespace utils {
	/* -- PROTOTYPES ---------------------------------------------- */
	const std::list<std::string>
		parseTerms(std::string copy);

	std::string
		getNextTerm(std::string& copy);

	std::string
		cutOut(const std::string& chunk);

	double
		extractCoef(const std::string& chunk);

	int
		extractOrder(const std::string& chunk);

	template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value
		|| std::is_integral<T>::value>::type>
	T
		abs(const T& x);

	void
		newOrder(std::map<int, double>& m, const int order, const double value);

	template <typename T>
	void
		display(const std::list<T>& l);

	/* -- PARSE UTILS --------------------------------------------- */
	inline const std::list<std::string>
		parseTerms(std::string copy) {
			std::list<std::string>	terms;

			while (!copy.empty())
				terms.push_back(getNextTerm(copy));
			return terms;
		}

	inline std::string
		getNextTerm(std::string& copy) {
			const size_t		sum_pos = copy.find_first_of("+-", 1);
			const std::string	term = cutOut(copy.substr(0, sum_pos));

			if (sum_pos == std::string::npos)
				copy.clear();
			else
				copy = copy.substr(sum_pos);
			return term;
		}

	inline std::string
		cutOut(const std::string& chunk) {
			const size_t	last_ws = chunk.find_last_of(POLYNOMIAL_STR);

			return chunk.substr(0, last_ws + 1);
		}

	inline double
		extractCoef(const std::string& chunk) {
			const size_t	first_nb = chunk.find_first_of(NUMBER_STR);
			int				sign;

			if (first_nb == 2)
				sign = chunk[0] == '-' ? -1 : 1;
			else if (!first_nb)
				sign = 1;
			else
				throw std::string("Not a correct value");
			return sign * std::stod(chunk.substr(first_nb, chunk.find(' ', first_nb)));
		}

	inline int
		extractOrder(const std::string& chunk) {
			const size_t	var_pos = chunk.find("X ^ ");

			if (var_pos == std::string::npos)
				return 0;
			return std::stoi(chunk.substr(var_pos + 4));
		}

	inline void
		newOrder(std::map<int, double>& m, const int order, const double value) {
			std::map<int, double>::iterator	it = m.find(order);

			if (it != m.end()) {
				it->second += value;
			} else {
				m.insert(std::pair<int, double>(order, value));
			}
		}

	/* -- MATH TOOLS ---------------------------------------------- */
	template <typename T,
		typename = typename std::enable_if<std::is_floating_point<T>::value
		|| std::is_integral<T>::value>::type>
	inline T
		abs(const T& x) {
			return (x < 0) ? -x : x;
		}

	/* -- MISCELLANEOUS ------------------------------------------- */
	template <typename T>
	inline void
		display(const std::list<T>& l) {
			for (typename std::list<T>::const_iterator it = l.begin(); it != l.end(); it++)
				std::cout << '[' << *it << "] ";
			std::cout << std::endl;
		}
}

#endif
