/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:39:57 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 16:38:59 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLY_HPP
# define MULTIPLY_HPP

# include "atree_node.hpp"

class Multiply: public virtual ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Multiply(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Multiply() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational	eval() const {
			const Rational	result(
				*base::getLeft()->eval() * *base::getRight()->eval()
			);
			return result.toShared();
		}

		void				print() {
			LOG("[mult]");
			base::getLeft()->print();
			std::cout << '*';
			base::getRight()->print();
		}

		unique_node			toNode() {
			return unique_node(
				new Multiply(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Multiply(base::getLeft()->clone(), base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates ind(base::getLeft()->collapse() * base::getRight()->collapse());
			DEBUG("Multiply : " << ind);
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif