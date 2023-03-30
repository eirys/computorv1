/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:18:44 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 15:52:14 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDE_HPP
# define DIVIDE_HPP

# include "atree_node.hpp"

class Divide: public virtual ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Divide(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Divide() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational	eval() const {
			const Rational	result(
				*base::getLeft()->eval() / *base::getRight()->eval()
			);
			return result.toShared();
		}

		void				print() {
			LOG("[div]");
			base::getLeft()->print();
			std::cout << '/';
			base::getRight()->print();
		}

		unique_node			toNode() {
			return unique_node(
				new Divide(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Divide(base::getLeft()->clone(), base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates ind = base::getLeft()->collapse() / base::getRight()->collapse();
			DEBUG("Divide: " << ind);
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif