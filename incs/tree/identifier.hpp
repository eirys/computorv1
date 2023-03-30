/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:10:49 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 17:50:47 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFIER_HPP
# define IDENTIFIER_HPP

# include <string>

# include "atree_node.hpp"

class Identifier: public ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_rational	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Identifier(
			const std::string& name,
			unique_node&& value
		):
			base(nullptr, std::move(value)),
			_name(name) {
				LOG("Creating identifier " << name  );
			}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Identifier() {}

		/* ------------------------------------------------------------------------ */
		const shared_rational		eval() const {
			return nullptr;
		}

		void					print() {
			LOG("[id]");
			std::cout << _name;
		}

		unique_node				toNode() {
			return unique_node(
				new Identifier(
					_name,
					std::move(base::getRight())
				)
			);
		}

		unique_node				clone() const {
			unique_node		new_right;
			if (base::getRight() != nullptr)
				new_right = base::getRight()->clone();
			return unique_node(
				new Identifier(
					_name,
					std::move(new_right)
				)
			);
		}

		Indeterminates			collapse() const {
			return Indeterminates(nullptr, _name);
		}

		/* Getter ----------------------------------------------------------------- */
		const std::string&		getName() const {
			return _name;
		}

	private:
		const std::string		_name;
};

#endif