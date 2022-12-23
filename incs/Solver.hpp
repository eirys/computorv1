/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:18:37 by eli               #+#    #+#             */
/*   Updated: 2022/12/23 15:52:51 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include "Parser.hpp"

class Solver {
	public:
	/* -- CONSTRUCTOR - DESTRUCTOR -------------------------------- */
		Solver(const Parser& p):
			_a(p.getOrder2()),
			_b(p.getOrder1()),
			_c(p.getOrder0()) {}

		~Solver() {}

	/* -- PRESENTATION -------------------------------------------- */


	private:
	/* -- PROPERTIES ---------------------------------------------- */
		double		_a;
		double		_b;
		double		_c;

	/* ------------------------------------------------------------ */
		double
			getDiscriminant() const {
				return (_b * _b) - (4 * _a * _c);
			}

		double
			delta_positive() const {
			}
};

#endif
