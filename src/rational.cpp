/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 16:56:01 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.hpp"
#include "rational.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Rational::Rational():
	_val(0) {}

Rational::~Rational() {}

Rational::Rational(long double x):
	_val(x) {}

Rational::Rational(const Rational& x):
	_val(x.getVal()) {}

/* -------------------------------------------------------------------------- */

Rational& Rational::operator=(long double rhs) {
	if (this->getVal() == rhs)
		return *this;
	_val = rhs;
	return *this;
}

Rational& Rational::operator=(const Rational& rhs) {
	if (*this == rhs)
		return *this;
	_val = rhs.getVal();
	return *this;
}

/* Arith operators ---------------------------------------------------------- */

Rational Rational::operator-() const {
	if (!getVal())
		return Rational(*this);
	return Rational(-getVal());
}

Rational& Rational::operator+=(const Rational& rhs) {
	_val += rhs.getVal();
	return *this;
}

Rational& Rational::operator++() {
	_val += 1;
	return *this;
}

Rational Rational::operator++(int) {
	Rational tmp(*this);

	operator++();
	return tmp;
}

Rational Rational::operator+(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator+=(rhs);
	return tmp;
}

Rational& Rational::operator-=(const Rational& rhs) {
	_val -= rhs.getVal();
	return *this;
}

Rational& Rational::operator--() {
	_val -= 1;
	return *this;
}

Rational Rational::operator--(int) {
	Rational tmp(*this);

	operator--();
	return tmp;
}

Rational Rational::operator-(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator-=(rhs);
	return tmp;
}

Rational& Rational::operator*=(const Rational& rhs) {
	if (getVal() != 0)
		_val *= rhs.getVal();
	return *this;
}

Rational Rational::operator*(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.getVal() == 0)
		throw math::operation_undefined();
	_val /= rhs.getVal();
	return *this;
}

Rational Rational::operator/(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator/=(rhs);
	return tmp;
}

Rational& Rational::operator^=(const Rational& rhs) {
	if (!rhs.isInteger())
		throw math::operation_undefined();
	_val = math::pow(getVal(), rhs.getVal());
	return *this;
}

Rational Rational::operator^(const Rational& rhs) const {
	Rational	tmp(*this);

	tmp.operator^=(rhs);
	return tmp;
}

Rational& Rational::operator%=(const Rational& rhs) {
	if (!rhs || !isInteger() || !rhs.isInteger())
		throw math::operation_undefined();
	_val = math::modulo(getVal(), rhs.getVal());
	return *this;
}

Rational Rational::operator%(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator%=(rhs);
	return tmp;
}

/* Getters ------------------------------------------------------------------ */

long double Rational::getVal() const {
	return _val;
}

/* Tools -------------------------------------------------------------------- */

bool Rational::operator!() const {
	return !getVal();
}

bool Rational::isInteger() const {
	const long long int	tmp = static_cast<long long int>(getVal());
	return tmp == getVal();
}

Rational::shared_rational	Rational::toShared() const {
	return std::make_shared<Rational>(*this);
}

/* Relational operators ----------------------------------------------------- */

bool	Rational::operator==(const Rational& y) const {
	return getVal() == y.getVal();
}

bool	Rational::operator<(const Rational& y) const {
	return getVal() < y.getVal();
}

bool	Rational::operator!=(const Rational& y) const {
	return !operator==(y);
}

bool	Rational::operator>(const Rational& y) const {
	return !operator<=(y);
}

bool	Rational::operator<=(const Rational& y) const {
	return operator==(y) || operator<(y);
}

bool	Rational::operator>=(const Rational& y) const {
	return !operator<(y);
}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

/* I/O stream operator ------------------------------------------------------ */

std::ostream&	operator<<(std::ostream& o, const Rational& x) {
	o << x.getVal();
	return o;
}
