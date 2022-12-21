#include "Parser.hpp"

int main(int ac, const char** av) {
	(void)ac;
	(void)av;
	try {
		Parser	parser(av[1]);
		parser.parse();
	} catch (const char* e) {
		std::cerr << e << std::endl;
		return 1;
	}
	return 0;
}
