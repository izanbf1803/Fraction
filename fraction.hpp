#ifndef __FRACTION_HPP__
#define __FRACTION_HPP__

#include <cassert>
#include <cstdint>
#include <string>
#include <sstream>

namespace fraction 
{
	typedef std::int64_t bigint;

	bigint gcd(bigint a, bigint b)
	{
		bigint x, y, temp;

		if (a > b) {
			x = a;
			y = b;
		}
		else {
			x = b;
			y = a;
		}

		assert(y != 0);

		while (y > 0) {
			temp = y;
			y = x % y;
			x = temp;
		}

		return x;
	}

	class Fraction 
	{
	public:
		inline ~Fraction() {};
		Fraction(bigint numerator, bigint denominator);
		Fraction(bigint integer);
		Fraction(double real);
		Fraction(std::string str);

		inline bigint n() const { return N; };
		inline bigint d() const { return D; };

		inline void set_n(bigint _N) { N = _N; };
		inline void set_d(bigint _D) { D = _D; };

		Fraction simplified();
		void simplify();
		Fraction inverted();
		void invert();

		bigint as_int() const;
		double as_real() const;
		std::string as_string() const;

		inline bool operator==(const Fraction& f) const { return N * f.d() == f.n() * D; }
		inline bool operator!=(const Fraction& f) const { return N * f.d() != f.n() * D; }
		inline bool operator>=(const Fraction& f) const { return N * f.d() >= f.n() * D; }
		inline bool operator<=(const Fraction& f) const { return N * f.d() <= f.n() * D; }
		inline bool operator>(const Fraction& f) const { return N * f.d() > f.n() * D; }
		inline bool operator<(const Fraction& f) const { return N * f.d() < f.n() * D; }

		inline Fraction operator+(const Fraction& f) const { return Fraction(N + f.n(), D + f.d()); }
		inline Fraction operator-(const Fraction& f) const { return Fraction(N - f.n(), D - f.d()); }
		inline Fraction operator*(const Fraction& f) const { return Fraction(N * f.n(), D * f.d()); }
		inline Fraction operator/(const Fraction& f) const { return Fraction(N * f.d(), D * f.n()); }

		inline Fraction operator+=(const Fraction& f) { *this = *this + f; return *this; }
		inline Fraction operator-=(const Fraction& f) { *this = *this - f; return *this; }
		inline Fraction operator*=(const Fraction& f) { *this = *this * f; return *this; }
		inline Fraction operator/=(const Fraction& f) { *this = *this / f; return *this; }

		friend std::ostream& operator<<(std::ostream& out, const Fraction& f) 
		{
	        out << f.n() << '/' << f.d();
	        return out;
	    }

	    friend std::istream& operator>>(std::istream& in, Fraction& f) 
	    {
	        std::string str;
	        in >> str;
	        f = Fraction(str);
	        return in;
	    }

	private:
		bigint N, D;
	};

	Fraction::Fraction(bigint numerator, bigint denominator)
	{
		assert(denominator != 0);
		N = numerator;
		D = denominator;
	}

	Fraction::Fraction(bigint integer)
	{
		N = integer;
		D = 1;
	}

	Fraction::Fraction(double real)
	{
		assert(real != 0.0);

		D = 1;
		N = 0;
		std::string str = std::to_string(real);
		auto dot_pos = str.find('.');

		if (str.size() > dot_pos) {
			str.erase (str.find_last_not_of('0') + 1, std::string::npos);
		}

		if (dot_pos == std::string::npos) {
			N = real;
		}
		else {
			N += str[0] - '0';
			for (std::size_t i = 1; i < str.size(); ++i) {
				if (str[i] != '.') {
					D *= 10;
					N *= 10;
					N += str[i] - '0';
				}
			}
		}
	}

	Fraction::Fraction(std::string str)
	{
		N = 0;
		D = 0;
		bool division_symbol_found = false;
		for (std::size_t i = 0; i < str.size(); ++i) {
			if (str[i] == '/') {
				assert(not division_symbol_found);
				division_symbol_found = true;
			}
			else if (str[i] >= '0' and str[i] <= '9') {
				if (division_symbol_found) {
					D *= 10;
					D += str[i] - '0';
				}
				else {
					N *= 10;
					N += str[i] - '0';
				}
			}
			else if (str[i] != ' ') {
				assert(false); // Syntax error: Only digits [0-9] and '/' or ' ' allowed.
			}
		}
	}

	void Fraction::simplify()
	{
		assert(D != 0);

		if (D < 0) {
			N *= -1;
			D *= -1;
		}

		bigint _gcd = gcd(N, D);
		N /= _gcd;
		D /= _gcd;
	}

	Fraction Fraction::simplified()
	{
		assert(D != 0);

		Fraction frac(N, D);
		frac.simplify();

		return frac;
	} 

	void Fraction::invert()
	{
		bigint temp = N;
		N = D;
		D = temp;
	}

	Fraction Fraction::inverted()
	{
		Fraction frac(N, D);
		frac.invert();

		return frac;
	}

	bigint Fraction::as_int() const
	{
		return N * D;
	}

	double Fraction::as_real() const
	{
		return ((double)N) / ((double)D);
	}

	std::string Fraction::as_string() const
	{
		return std::to_string(N) + "/" + std::to_string(D);
	}

}

#endif