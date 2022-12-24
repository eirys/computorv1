/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:18:37 by eli               #+#    #+#             */
/*   Updated: 2022/12/24 16:58:04 by eli              ###   ########.fr       */
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
			solve() const {
				if (!_a && !_b) {
					return _noRoots();
				} else if (!_a && _b && !_c) {
					return _deltaNull();
				}
				return _solvePolynomial();
			}

	private:
	/* -- PROPERTIES ---------------------------------------------- */
		double		_a;
		double		_b;
		double		_c;

	/* -- SOLVING TOOLS ------------------------------------------- */
		double
			_computeDiscriminant() const {
				return (_b * _b) - (4 * _a * _c);
			}

		void
			_deltaPositive(const double discriminant) const {
				const double	sqrt_delta = math::sqrt(discriminant);
				const double	x1 = (- _b - sqrt_delta) / 2 * _a;
				const double	x2 = (- _b + sqrt_delta) / 2 * _a;

				std::cout << "There are two roots: "
					<< "x1 = " << (x1 ? x1 : 0) << ", x2 = " << (x2 ? x2 : 0) << NL;
			}

		void
			_deltaNull() const {
				const double	x = - _b / 2 * _a;

				std::cout << "There is one root: "
					<< "x = " << (x ? x : 0) << NL;
			}

		void
			_deltaNegative(const double discriminant) const {
				//TODO: complex solutions
				(void)discriminant;
				return _noRoots();
			}

		void
			_noRoots() const {
				std::cout << "There are no roots." << NL;
			}

		void
			_solvePolynomial() const {
				const double delta = _computeDiscriminant();
				if (delta > 0) {
					return _deltaPositive(delta);
				} else if (delta < 0) {
					return _deltaNegative(delta);
				} else {
					return _deltaNull();
				}
			}
};

#endif
