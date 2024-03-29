/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:45:04 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 17:17:34 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.hpp"
#include <cstring>

# include "utils.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Tokenizer::Tokenizer(const std::string& raw):
	_raw(raw),
	_current_pos(0) {
		if (raw.empty())
			throw EmptyInput();
	}

Tokenizer::~Tokenizer() {}

/* Main function ------------------------------------------------------------ */

Tokenizer::e_tokentype Tokenizer::scanToken(std::string& holder) {
	e_tokentype		ret;
	size_t			next_pos = 0;

	 if (_current_pos == std::string::npos) {
		next_pos = _current_pos;
		ret = EEMPTY;
	} else if (utils::isCharset(_raw[_current_pos], WHITESPACES)) {
		next_pos = _find_not_of(WHITESPACES);
		ret = EWHITESPACE;
	} else if (utils::isCharset(_raw[_current_pos], DIGIT)) {
		next_pos = _find_not_of(DIGIT);
		if (utils::isCharset(_raw[next_pos], DOT)) {
			++next_pos;
			if (utils::isCharset(_raw[next_pos], DIGIT)) {
				next_pos = _find_not_of(DIGIT, next_pos);
			}
		}
		ret = ERATIONAL;
	} else if (utils::isCharset(_raw[_current_pos], NAME)) {
		next_pos = _find_not_of(NAME);
		ret = ENAME;
	} else if (utils::isCharset(_raw[_current_pos], DELIMITER)) {
		next_pos = _current_pos + 1;
		if (next_pos >= _raw.size())
			next_pos = std::string::npos;
		ret = EDELIMITER;
	} else if (utils::isCharset(_raw[_current_pos], SYMBOL)) {
		next_pos = _current_pos + 1;
		if (next_pos >= _raw.size())
			next_pos = std::string::npos;
		ret = ESYMBOL;
	} else {
		throw BadFormat();
	}
	holder = _update_token(next_pos);
	LOG("Sanned: `" << holder << '`');
	_current_pos = next_pos;
	if (ret == EWHITESPACE) {
		// Ignore whitespace
		return scanToken(holder);
	}
	return ret;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */


/* Utils -------------------------------------------------------------------- */

bool	Tokenizer::_find(const char* charset) const {
	return _raw.find_first_of(charset, _current_pos) != std::string::npos;
}

size_t	Tokenizer::_find_not_of(const char* charset, size_t pos) const {
	if (pos == std::string::npos)
		return _raw.find_first_not_of(charset, _current_pos);
	else
		return _raw.find_first_not_of(charset, pos);
}

std::string	Tokenizer::_update_token(const size_t& next_pos) const {
	if (next_pos == _current_pos)
		return "";
	if (next_pos != std::string::npos)
		return _raw.substr(_current_pos, next_pos - _current_pos);
	return _raw.substr(_current_pos);
}