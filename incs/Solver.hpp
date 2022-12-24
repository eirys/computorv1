/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:18:37 by eli               #+#    #+#             */
/*   Updated: 2022/12/24 15:22:00 by eli              ###   ########.fr       */
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

	/* -- SOLVER -------------------------------------------------- */
		void
			solve() {
				const double delta = _compute_discriminant();
				if (delta > 0) {
					_delta_positive(delta);
				}
			}

	private:
	/* -- PROPERTIES ---------------------------------------------- */
		double		_a;
		double		_b;
		double		_c;

	/* ------------------------------------------------------------ */

		double
			_compute_discriminant() {
				return (_b * _b) - (4 * _a * _c);
			}

		void
			_delta_positive(const double discriminant) const {
				double	sqrt_delta = math::sqrt(discriminant);
				double	x1 = (- _b - sqrt_delta) / 2 * _a;
				double	x2 = (- _b + sqrt_delta) / 2 * _a;
				using std::cout;

				cout << "There are two roots:" << NL
					<< "x1 = " << x1 << " & x2 = " << x2 << NL;
			}

};

#endif
