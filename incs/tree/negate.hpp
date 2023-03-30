/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negate.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:10:38 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 16:40:37 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEGATE_HPP
# define NEGATE_HPP

# include "atree_node.hpp"

class Negate: public virtual ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Negate(unique_node&& right):
			base(nullptr, std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Negate() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational	eval() const {
			const Rational	result(- *base::getRight()->eval());
			return result.toShared();
		}

		void				print() {
			LOG("[neg]");
			std::cout << "(-";
			base::getRight()->print();
			std::cout <<')';			
		}

		unique_node			toNode() {
			return unique_node(
				new Negate(std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Negate(base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates	ind = -(base::getRight()->collapse());
			DEBUG("Negate: " << ind);
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif