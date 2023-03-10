/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:24:40 by eli               #+#    #+#             */
/*   Updated: 2023/03/06 18:46:30 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_HPP
# define VARIABLE_HPP

# include "atree_node.hpp"

/**
 * Variable		: Rational
 * 				| Complex
 * 				| Matrix
*/
class Variable: virtual public ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		/* Constructor ------------------------------------------------------------ */
		Variable(const shared_itype& val_ptr):
			base(),
			_val_ptr(val_ptr) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Variable() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype	eval() {
			return _val_ptr;
		}

		void				print() {
			std::cout << *_val_ptr;
		}

		unique_node			toNode() {
			return unique_node(new Variable(_val_ptr));
		}

		Indeterminates collapse() {
			return Indeterminates(this);
		}

	private:
		shared_itype	_val_ptr;
};

/* ========================================================================== */
/*                                    UTILS                                   */
/* ========================================================================== */

inline Variable::unique_node	createVariable(const Rational& x) {
	Variable::shared_itype	tmp(new Rational(x));

	return Variable::unique_node(new Variable(tmp));
}

inline Variable::unique_node	createVariable(const Complex& x) {
	Variable::shared_itype	tmp(new Complex(x));

	return Variable::unique_node(new Variable(tmp));
}

inline Variable::unique_node	createVariable(const Matrix& x) {
	Variable::shared_itype	tmp(new Matrix(x));

	return Variable::unique_node(new Variable(tmp));
}

#endif