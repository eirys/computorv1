/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:46:16 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 16:55:27 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include "atree_node.hpp"
# include "utils.hpp"
# include "rational.hpp"

class Complex {
	public:
		typedef typename	std::shared_ptr<Rational>		shared_rational;
		typedef				std::unique_ptr<ATreeNode>		unique_node;

		Complex();
		virtual ~Complex();

		Complex(const Rational& x, const Rational& y = Rational(0));

		/* Getter ----------------------------------------------------------------- */
		const Rational&	getReal() const;
		const Rational&	getImaginary() const;

		/* Tools ------------------------------------------------------------------ */
		bool			isComplex() const;
		bool			isReal() const;
		bool			isImaginary() const;

	private:
		Rational		_re;
		Rational		_im;
};

std::ostream&			operator<<(std::ostream& o, const Complex& x);

#endif