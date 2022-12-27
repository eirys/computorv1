
#include <iostream>
#include "Parser.hpp"
#include "Solver.hpp"

int main(int ac, char** av) {

	(void)ac;(void)av;

	double a = 323.0f; int b = 2;
	std::cout << a << NL
		<< b << NL
		<< std::boolalpha
		<< math::isPrime(a) << NL
		<< math::isPrime(b) << NL;

	std::cout << math::nearestPrime(a) << NL;
	std::cout << math::nearestPrime(b) << NL;
}

/*

int main(int ac, const char** av) {
	if (ac != 2) {
		std::cerr << "Argument incorrect. Usage examples:" << NL
			<< "./computor \"5 * X ^ 2 = 15 * X ^ 1 + 12 * X ^ 0\"" << NL
			<< "./computor \"- 15.02 * X ^ 2 + 13 * X ^ 1 = 0\"" << NL;
		return 1;
	}
	try {
		Parser			parser(av[1]);
		parser.parse();

		const Solver	solver(parser);
		solver.solve();
	} catch (const std::string& e) {
		std::cerr << e << NL;
		return 1;
	} catch (const std::exception& ex) {
		std::cerr << ex.what() << NL;
		return 1;
	}
	return 0;
}

*/

