/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:59 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 17:55:25 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "identifier.hpp"
#include "variable.hpp"
#include "add.hpp"
#include "substract.hpp"
#include "multiply.hpp"
#include "divide.hpp"
#include "power.hpp"
#include "negate.hpp"
#include "equality.hpp"
#include "utils.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Parser::Parser(const std::string& raw):
	_tokenizer(raw),
	_ret(EEMPTY) {
		if (raw.find(EQUAL) == std::string::npos) {
			throw IncorrectSyntax("Missing `=` sign	");
		}
	}

Parser::~Parser() {}

/* Main Function ------------------------------------------------------------ */

Parser::result_tree Parser::parse() {
	unique_node	result = _parseS();
	LOG("Getting main tree now");

	if (_ret != EEMPTY)
		throw IncorrectSyntax("Unexpected token");	
	if (result == nullptr)
		throw EmptyContent();

	result_tree	tree = std::make_shared<unique_node>(std::move(result));
	return tree;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

/* Parsing Differentiation -------------------------------------------------- */

/**
 * Solver parsing
 *
 * GRAMMAR:
 * S	: E = E
*/
Parser::unique_node	Parser::_parseS() {
	unique_node	lhs = _parseE();
	unique_node	result;

	if (lhs == nullptr)
		throw IncorrectSyntax("Left hand side expression incorrect");
	if (_ret != EEMPTY && _token == EQUAL) {
		// Equality
		unique_node	rhs = _parseE();
		if (rhs == nullptr)
			throw IncorrectSyntax("Right hand side expression incorrect");
		Equality	eq(std::move(lhs), std::move(rhs));
		result = eq.toNode();
	}
	return result;
}

/* Parse Function Helper ---------------------------------------------------- */

/**
 * Expression parsing (P)
 *
 * GRAMMAR:
 * E	: T + T
 * 		| T - T
 * 		| T
*/
Parser::unique_node	Parser::_parseE() {
	LOG("In _parseE");
	unique_node	a = _parseT();

	if (a == nullptr)
		return a;
	while (_ret != EEMPTY) {
		if (_token == ADDITION) {
			// T + T
			unique_node b = _parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting term after `+`");
			Add	add(std::move(a), std::move(b));
			a = add.toNode();
		} else if (_token == SUBSTRACTION) {
			// T - T
			unique_node	b = _parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting term after `-`");
			Substract	sub(std::move(a), std::move(b));
			a = sub.toNode();
		} else {
			break;
		}
	}
	return a;
}

/**
 * Term parsing (MD)
 *
 * GRAMMAR:
 * 	T	: P
 * 		| T * P
 * 		| T / P
*/
Parser::unique_node	Parser::_parseT() {
	LOG("In _parseT");
	unique_node	a = _parseP();

	if (a == nullptr)
		return a;
	while (1) {
		if (_token == MULTIPLICATION) {
			// T * F
			unique_node	b = _parseP();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `*`");
			Multiply	mul(std::move(a), std::move(b));
			a = mul.toNode();
		} else if (_token == DIVISION) {
			// T / F
			unique_node	b = _parseP();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `/`");
			Divide		div(std::move(a), std::move(b));
			a = div.toNode();
		} else {
			break;
		}
	}
	return a;
}

/**
 * Exponentiation parsing (E)
 * 
 * GRAMMAR:
 * 	P	: F ^ F
 * 		: F
*/
Parser::unique_node	Parser::_parseP() {
	unique_node	a = _parseF();

	if (a == nullptr)
		return a;
	while (1) {
		if (_token == POWER) {
			// F ^ F
			unique_node b = _parseF();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `^`");
			Power		pow(std::move(a), std::move(b));
			a = pow.toNode();
		} else {
			break;
		}
	}
	return a;
}

/**
 * Factor parsing (AS)
 *
 * GRAMMAR:
 * F	: Identifier
 * 		| Variable
 * 		| ( E )
 * 		| - F
 * 		| + F
 **/
Parser::unique_node	Parser::_parseF() {
	LOG("In _parseF");
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		Identifier		id(_token, nullptr);
		_ret = _tokenizer.scanToken(_token);
		return id.toNode();
	} else if (_ret == ERATIONAL) {
		// Rational
		return _parseSimpleValue();
	} else if (_ret == EDELIMITER) {
		if (_token == L_PARENTHESIS) {
			// Parenthesis
			unique_node	a = _parseE();
			if (a == nullptr)
				throw IncorrectSyntax("Expecting content inside parenthesis");
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				return a;
			}
			throw IncorrectSyntax("Expecting final `)`");
		}
	} else if (_ret == ESYMBOL) {
		if (_token == NEGATE) {
			// Negate
			unique_node	a = _parseF();
			if (a == nullptr)
				throw IncorrectSyntax("Expecting value after `-`");
			Negate	negation(std::move(a));
			return negation.toNode();
		} else if (_token == ADDITION) {
			unique_node a = _parseF();
			if (a == nullptr)
				throw IncorrectSyntax("Expecting value after `+`");
			return a;
		}
	}
	return nullptr;
}

/* Utils -------------------------------------------------------------------- */

Parser::unique_node	Parser::_parseSimpleValue() {
	if (_token.size() >= 10)
		throw IncorrectSyntax("Value too big");
	try {
		Rational	value(std::stold(_token));
		_ret = _tokenizer.scanToken(_token);
		return createVariable(value);
	} catch (const std::invalid_argument& e) {
		return nullptr;
	}
	return nullptr;
}