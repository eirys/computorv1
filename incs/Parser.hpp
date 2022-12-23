/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:03:58 by eli               #+#    #+#             */
/*   Updated: 2022/12/23 02:17:28 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "utils.hpp"

class Parser {
	public:
	/* -- CONSTRUCTOR - DESTRUCTOR -------------------------------- */
		Parser(const char* input):
			_raw(input),
			_order0(0),
			_order1(0),
			_order2(0) {}

		~Parser() {}

	/* -- PARSING ------------------------------------------------- */
		void 
			parse() {
				const size_t	pos_equal = _raw.find('=');

				if (pos_equal == std::string::npos)
					throw std::string("Not a polynomial");
				_parseCoefficients(utils::parseTerms(_raw.substr(0, pos_equal)));
				_parseCoefficients(utils::parseTerms(_raw.substr(pos_equal + 2)));

				LOG(_order0);
				LOG(_order1);
				LOG(_order2);
				display();
			}

	/* -- PRESENTATION ------------------------------------------- */
		void
			display() const {
				if (!(_order0 || _order1 || _order2))
					std::cout << "Nothing to display\n";
				else
					_displayReducedEquation();
			}

	/* -- GETTERS ------------------------------------------------ */
		double
			getOrder0() const {
				return _order0;
			}
		
		double
			getOrder1() const {
				return _order1;
			}

		double
			getOrder2() const {
				return _order2;
			}

	private:
	/* -- PROPERTIES ---------------------------------------------- */
		const std::string					_raw;
		double								_order0;
		double								_order1;
		double								_order2;

	/* -- MAIN PARSE FUNCTION ------------------------------------- */
		void
			_parseCoefficients(const std::list<std::string>& list) {
				for (std::list<std::string>::const_iterator it = list.begin();
				it != list.end();
				it++) {
					const double value = utils::extractCoef(*it);
					switch (utils::extractOrder(*it)) {
						case 1:
							_order1 += value;
							break;
						case 2:
							_order2 += value;
							break;
						default:
							_order0 += value;
							break;
					}
				}
			}

	/* -- PRESENTATION ------------------------------------------- */
		void
			_displayReducedEquation() const {
				const bool	is_positive0 = _order0 > 0;
				const bool	is_positive1 = _order1 > 0;
				const bool	is_positive2 = _order2 > 0;
				bool		has_precedent = false;
				using std::cout;

				if (_order0) {
					cout << (is_positive0 ? "" : "- ")
						 << utils::abs(_order0) << " * X ^ 0";
					has_precedent = true;
				}
				if (_order1) {
					if (has_precedent) {
						cout << (is_positive1 ? " + " : " - ");
					} else {
						has_precedent = true;
						cout << (is_positive1 ? "" : "- ");
					}
					cout << utils::abs(_order1) << " * X ^ 1";
				}
				if (_order2) {
					if (has_precedent) {
						cout << (is_positive2 ? " + " : " - ");
					} else {
						cout << (is_positive2 ? "" : "- ");
					}
					cout << utils::abs(_order2) << " * X ^ 2";
				}
				cout << " = 0" << NL;
			}
};

#endif
