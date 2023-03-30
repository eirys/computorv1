/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 17:32:42 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>
# include <memory>

# include "utils.hpp"

class Rational {
	public:
		typedef typename	std::shared_ptr<Rational>		shared_rational;

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

		/* Getter ----------------------------------------------------------------- */
		long double		getVal() const;

		/* Tools ------------------------------------------------------------------ */
		bool			operator!() const;
		bool			isInteger() const;
		shared_rational	toShared() const;

		/* Relational Operators --------------------------------------------------- */
		bool			operator==(const Rational& y) const;
		bool			operator<(const Rational& y) const;
		bool			operator!=(const Rational& y) const;
		bool			operator<=(const Rational& y) const;
		bool			operator>(const Rational& y) const;
		bool			operator>=(const Rational& y) const;

	private:
		long double		_val;
};

std::ostream&	operator<<(std::ostream& o, const Rational& x);

#endif