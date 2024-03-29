/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:34:39 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 16:44:09 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTRACT_HPP
# define SUBSTRACT_HPP

# include "atree_node.hpp"

class Substract: virtual public ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Initialized ------------------------------------------------------------ */
		Substract(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Substract() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational	eval() const {
			const Rational	result = *base::getLeft()->eval() - *base::getRight()->eval();
			return result.toShared();
		}

		void				print() {
			LOG("[subs]");
			std::cout << '(';
			base::getLeft()->print();
			std::cout << '-';
			base::getRight()->print();
			std::cout << ')';
		}

		unique_node			toNode() {
			return unique_node(
				new Substract(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Substract(base::getLeft()->clone(), base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates ind(base::getLeft()->collapse() - base::getRight()->collapse());
			DEBUG("Substract: " << ind);
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif