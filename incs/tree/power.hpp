/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:08:46 by etran             #+#    #+#             */
/*   Updated: 2023/03/30 17:51:05 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWER_HPP
# define POWER_HPP

# include "atree_node.hpp"

class Power: public virtual ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Power(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Power() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational	eval() const {
			const Rational	result = *base::getLeft()->eval() ^ *base::getRight()->eval();
			return result.toShared();
		}

		void				print() {
			LOG("[pow]");
			base::getLeft()->print();
			std::cout << '^';
			base::getRight()->print();
		}

		unique_node			toNode() {
			return unique_node(
				new Power(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Power(base::getLeft()->clone(), base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates	ind = base::getLeft()->collapse() ^ base::getRight()->collapse();
			DEBUG("Power: " << ind);
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif