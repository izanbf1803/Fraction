#include "fraction.hpp"
#include <iostream>

using namespace std;
using fraction::Fraction;

#define SEP "-----------------------------"

int main()
{
	Fraction f(50, 4);
	f.set_n(60);
	f.set_d(5);

	cout << f.n() << "/" << f.d() << " = ";  //
	cout << f.as_string() << " = ";			 // Same output
	cout << f << ", ";						 // 

	f.simplify();

	cout << f << " " << f.as_real() << ", ";
	cout << endl;

	cout << SEP << endl; ///////////////////

	Fraction x("45 / 3");
	cout << x << " " << x.as_real() << endl;
	x.simplify();
	cout << x << " " << x.as_real() << endl;

	cout << SEP << endl; ///////////////////

	string str = Fraction(3.141592).as_string();
	double re = Fraction(3.141592).as_real();

	cout << str << endl;
	cout << re << endl;

	cout << SEP << endl; ///////////////////

	Fraction a("10 / 7");
	Fraction b("84355 / 64356");

	cout << (a > b ? a : b) << endl;
	cout << (a + b).simplified() << " " << (a * b).simplified() << " " 
		 << (a / b).simplified() << " " << (a - b).simplified() << endl;
}