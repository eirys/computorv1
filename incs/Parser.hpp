/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:03:58 by eli               #+#    #+#             */
/*   Updated: 2022/12/21 17:30:48 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <list>

class Parser {
	public:

	/* == CONSTRUCTOR - DESTRUCTOR ============================================================== */
		Parser(const char* input):
			_raw(input) {}

		~Parser() {}

	/* == PARSING =============================================================================== */
		void 
			parse() {
				_parseBeforeEqual(_raw.substr(0, copy.find('=')));
				_parseAfterEqual(_raw.substr(copy.find('=') + 1));
			}

	/* == GETTERS =============================================================================== */
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
	/* == PROPERTIES ============================================================================ */
		const std::string					_raw;
		std::list<float>					_order2;
		std::list<float>					_order1;
		std::list<float>					_order0;

	/* == PARSE UTILS =========================================================================== */
		void
			_parseBeforeEqual(std::string copy) {
				while (!copy.empty()) {
				}
			}

		void
			_parseAfterEqual(std::string copy) {
				while (!copy.empty()) {
					copy.find();
				}
			}

};

#endif
