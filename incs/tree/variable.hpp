/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:24:40 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 16:44:56 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_HPP
# define VARIABLE_HPP

# include "atree_node.hpp"
# include "rational.hpp"

class Variable: virtual public ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Variable(const shared_rational& val_ptr):
			base(),
			_val_ptr(val_ptr) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Variable() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational	eval() const {
			return _val_ptr;
		}

		void				print() {
			LOG("[var]");
			std::cout << *_val_ptr;
		}

		unique_node			toNode() {
			return unique_node(new Variable(_val_ptr));
		}

		unique_node			clone() const {
			return unique_node(new Variable(_val_ptr));
		}

		Indeterminates		collapse() const {
			return Indeterminates(_val_ptr);
		}

	private:
		shared_rational	_val_ptr;
};

/* ========================================================================== */
/*                                    UTILS                                   */
/* ========================================================================== */

inline Variable::unique_node	createVariable(const Rational& x) {
	Variable::shared_rational	tmp = x.toShared();

	return Variable::unique_node(new Variable(tmp));
}

#endif