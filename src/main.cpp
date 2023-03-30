/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 18:20:36 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>

#define __ARGUMENTS_COMPUTOR "Argument was unexpected\n"
#define __DANGEROUS_COMPUTOR "Dangerous maneuver...\n"

void	puterror(const char* msg) {
	write(STDERR_FILENO, msg, strlen(msg));
}

#include "utils.hpp"
#include "math.hpp"

#include "rational.hpp"
#include "complex.hpp"
#include "atree_node.hpp"

#include "parser.hpp"
#include "solver.hpp"

using std::cin;
using std::cout;
using std::cerr;

void	computeEntry(const std::string& entry) {
	try {
		Parser				parser(entry);
		Parser::result_tree	output = parser.parse();

		Indeterminates		ind_res;

		DEBUG("Collapsing");
		ind_res = (*output)->collapse();
		cout	<< "Expanded expression:\n" << ind_res << " = 0 " << NL;

		Solver	solver(ind_res);
		solver.solve();
		DEBUG("Finished solving");
	} catch (const Tokenizer::EmptyInput& empty) {
		return;
	} catch (const Indeterminates::ExpansionNotSupported& e) {
		cerr << e.what() << NL;
	} catch (const std::exception& e) {
		cerr << "Error: " << e.what() << NL;
	}
}


int main(int ac, char* const* av) {
	if (ac == 2) {
		// Input
		computeEntry(av[1]);
		return 0;
	} else if (ac != 1) {
		puterror(__ARGUMENTS_COMPUTOR);
		std::exit(EXIT_FAILURE);
	} else if (!isatty(STDIN_FILENO)) {
		puterror(__DANGEROUS_COMPUTOR);
		std::exit(EXIT_FAILURE);
	}

	cout <<	"Welcome to computorv1 (v1.0.0, 2023), computorv2's lil brother, "
			"made with love by @etran.\n"
			"With this program, you can only solve equations (1st and 2nd degree polynomials of R only)\n"
			"  (example: `x+1 = 2*x`).\n";

	while (!cin.eof()) {
		cout << PROMPT;
		std::string			entry;
		std::getline(cin, entry);

		computeEntry(entry);
	}
	cout << "quit\n";
	return 0;
}