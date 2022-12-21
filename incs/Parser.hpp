/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:03:58 by eli               #+#    #+#             */
/*   Updated: 2022/12/22 00:22:29 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <list>

# define NUMBER_STR "0123456789"
# define POLYNOMIAL_STR "0123456789X"

class Parser {
	public:

	/* -- CONSTRUCTOR - DESTRUCTOR -------------------------------------------------------------- */
		Parser(const char* input):
			_raw(input) {}

		~Parser() {}

	/* -- PARSING ------------------------------------------------------------------------------- */
		void 
			parse() {
				const size_t pos_equal = _raw.find('=');

				if (pos_equal == std::string::npos)
					throw "Not a polynomial";
				const std::list<std::string> l1 = _parseBeforeEqual(_raw.substr(0, pos_equal));
				const std::list<std::string> l2 = _parseAfterEqual(_raw.substr(pos_equal + 1));

				_display(l1);
				_display(l2);
			}

	/* -- GETTERS ------------------------------------------------------------------------------- */
		const std::list<float>&
			getOrder2() const {
				return _order2;
			}

		const std::list<float>&
			getOrder1() const {
				return _order1;
			}

		const std::list<float>&
			getOrder0() const {
				return _order0;
			}


	private:
	/* -- PROPERTIES ---------------------------------------------------------------------------- */
		const std::string					_raw;
		std::list<float>					_order2;
		std::list<float>					_order1;
		std::list<float>					_order0;

	/* -- PARSE UTILS --------------------------------------------------------------------------- */
		const std::list<std::string>
			_parseBeforeEqual(std::string copy) {
				std::list<std::string> terms;

				while (!copy.empty()) {
					terms.push_back(_getNextTerm(copy));
				}
				return terms;
			}

		const std::list<std::string>
			_parseAfterEqual(std::string copy) {
				std::list<std::string> terms;

				while (!copy.empty()) {
					terms.push_back(_getNextTerm(copy));
				}
				return terms;
			}

		std::string
			_getNextTerm(std::string& copy) const {
				const size_t sum_pos = copy.find("+-", 1);
				std::string term = _cutOut(copy.substr(0, sum_pos));

				if (sum_pos == std::string::npos)
					copy.clear();
				else
					copy = copy.substr(sum_pos);
				return term;
			}

		std::string
			_cutOut(const std::string& chunk) const {
				const size_t last_ws = chunk.find_last_of(POLYNOMIAL_STR);

				return chunk.substr(0, last_ws + 1);
			}

	/* -- MISCELLANEOUS ------------------------------------------------------------------------- */
		void
			_display(const std::list<std::string>& l) const {
				for (std::list<std::string>::const_iterator it = l.begin();
						it != l.end();
						it++) {
					std::cout << *it << " - " << std::endl;
				}
			}
};

#endif
