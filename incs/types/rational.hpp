/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/03/07 17:04:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>

# include "utils.hpp"
# include "itype.hpp"

class Complex;
class Matrix;

/**
 * Rational		: { - } digit { digit | { . digit } }
 * 
 * example:		-123
 * 				0.56
 *
*/
class Rational: public IType {
	public:
		typedef typename	IType::unique_itype		unique_itype;
		typedef typename	IType::shared_itype		shared_itype;
		typedef typename	IType::weak_itype		weak_itype;

		Rational();
		virtual ~Rational();

		Rational(long double x);
		Rational(const Rational& x);
		
		Rational&		operator=(long double rhs);
		Rational&		operator=(const Rational& rhs);

		/* Arith Operators -------------------------------------------------------- */
		Rational		operator-() const;

		Rational&		operator+=(const Rational& rhs);
		Rational&		operator++();
		Rational		operator++(int);
		Rational		operator+(const Rational& rhs) const;

		Rational&		operator-=(const Rational& rhs);
		Rational&		operator--();
		Rational		operator--(int);
		Rational		operator-(const Rational& rhs) const;

		Rational&		operator*=(const Rational& rhs);
		Rational		operator*(const Rational& rhs) const;

		Rational&		operator/=(const Rational& rhs);
		Rational		operator/(const Rational& rhs) const;

		Rational&		operator^=(const Rational& rhs);
		Rational		operator^(const Rational& rhs) const;

		Rational&		operator%=(const Rational& rhs);
		Rational		operator%(const Rational& rhs) const;

		/* Complex Operators ------------------------------------------------------ */
		Complex			operator+(const Complex& rhs) const;
		Complex			operator-(const Complex& rhs) const;
		Complex			operator*(const Complex& rhs) const;
		Complex			operator/(const Complex& rhs) const;
		Complex			operator^(const Complex& rhs) const;
		Complex			operator%(const Complex& rhs) const;

		/* Getter ----------------------------------------------------------------- */
		long double		getVal() const;

		/* Tools ------------------------------------------------------------------ */
		bool			operator!() const;
		bool			isInteger() const;

	private:
		long double		_val;
};

bool			operator==(const Rational& x, const Rational& y);
bool			operator<(const Rational& x, const Rational& y);
bool			operator!=(const Rational& x, const Rational& y);
bool			operator<=(const Rational& x, const Rational& y);
bool			operator>(const Rational& x, const Rational& y);
bool			operator>=(const Rational& x, const Rational& y);

std::ostream&	operator<<(std::ostream& o, const Rational& x);

#endif