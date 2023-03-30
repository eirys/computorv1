/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equality.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:43:36 by etran             #+#    #+#             */
/*   Updated: 2023/03/30 18:48:43 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUALITY_HPP
# define EQUALITY_HPP

# include "atree_node.hpp"

class Equality: public ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Equality(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Equality() {}

		const shared_rational	eval() const {
			Indeterminates	ind = collapse();
			if (ind.getMap().empty())
				std::cout << "True\n";
			else
				std::cout << "False\n";
			return nullptr;
		}

		void				print() {}

		unique_node			toNode() {
			return unique_node(
				new Equality(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Equality(base::getLeft()->clone(), base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates	lhs = base::getLeft()->collapse();
			std::cout << "Left hand side:\n" << lhs << NL;
			Indeterminates	rhs = base::getRight()->collapse();
			std::cout << "Right hand side:\n" << rhs << NL;
			DEBUG("Equality: ");
			Indeterminates	ind = lhs - rhs;
			std::cout << "Combining members:\n" << ind << " = 0" << NL;
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif