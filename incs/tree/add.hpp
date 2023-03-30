/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:13:54 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 15:48:13 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_HPP
# define ADD_HPP

# include <memory>

# include "atree_node.hpp"

class Add: virtual public ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Add(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Add() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational	eval() const {
			const Rational	result(
				*base::getLeft()->eval() + *base::getRight()->eval()
			);
			return result.toShared();
		}

		void				print() {
			LOG("[add]");
			std::cout << '(';
			base::getLeft()->print();
			std::cout << '+';
			base::getRight()->print();
			std::cout << ')';
		}

		unique_node			toNode() {
			return unique_node(
				new Add(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Add(base::getLeft()->clone(), base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates	ind(base::getLeft()->collapse() + base::getRight()->collapse());
			DEBUG("Add: " << ind);
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif