/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:07:29 by eli               #+#    #+#             */
/*   Updated: 2023/03/07 17:12:42 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.hpp"
#include "matrix.hpp"
#include "math.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Complex::Complex():
	_re(0),
	_im(0) {}

Complex::~Complex() {}

Complex::Complex(const Complex& x):
	_re(x.getReal()),
	_im(x.getImaginary()) {}

Complex::Complex(const Rational& x, const Rational& y):
	_re(x),
	_im(y) {}

/* -------------------------------------------------------------------------- */

Complex& Complex::operator=(const Complex& rhs) {
	if (this == &rhs)
		return *this;
	_re = rhs.getReal();
	_im = rhs.getImaginary();
	return *this;
}

/* Getters ------------------------------------------------------------------ */

Rational Complex::getReal() const {
	return Rational(_re);
}

Rational Complex::getImaginary() const {
	return Rational(_im);
}

/* Tools -------------------------------------------------------------------- */

bool	Complex::operator!() const {
	return !getReal() && !getImaginary();
}

bool	Complex::isComplex() const {
	return getImaginary().getVal() && getReal().getVal();
}

bool	Complex::isReal() const {
	return !getImaginary().getVal();
}

bool	Complex::isImaginary() const {
	return !isReal();
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

/* Relational operators ----------------------------------------------------- */

bool operator==(const Complex& x, const Complex& y) {
	return x.getReal() == y.getReal() && x.getImaginary() == y.getImaginary();
}

bool operator!=(const Complex& x, const Complex& y) {
	return !operator==(x,y);
}

/* I/O stream operator ------------------------------------------------------ */

std::ostream& operator<<(std::ostream& o, const Complex& x) {
	if (x.isComplex()) {
		o << x.getReal();
		if (x.getImaginary() > 0)
			o << " + ";
		else if (x.getImaginary() < 0)
			o << " - ";
		if (math::abs(x.getImaginary()) != 1)
			o << math::abs(x.getImaginary());
		o << 'i';
	} else if (x.isReal()) {
		o << x.getReal();
	} else if (x.isImaginary()) {
		if (x.getImaginary() < 0)
			o << " - ";
		if (math::abs(x.getImaginary()) != 1)
			o << math::abs(x.getImaginary());
		o << 'i';
	}
	return o;
}
