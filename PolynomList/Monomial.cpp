#include "Monomial.h"
#include <iostream>
using namespace std;

int Monomial::monomialNumber = 0;

Monomial::Monomial(double coefficient, const int degree) : degree(degree)
{ //c'tor with initialize list for the const variable for Monomial class
	if (degree < 0)
		( this->~Monomial() );
	else
	{
		this->coefficient = coefficient;
		monomialNumber++;
	}
	
}
Monomial::~Monomial()
{ //destructor of Monomial class
	if(this->degree>=0)
	monomialNumber--;
}
int Monomial::getNumberOfMonomials()
{ // A function that returns how many instance still in the memory.
	return monomialNumber;
}
void Monomial::print() const
{
	if (this->degree == 0) {
		cout << this->coefficient;
		return;
	}
	if (this->coefficient != 1 && this->coefficient != -1)
		cout << this->coefficient <<"*";
	else if (this->coefficient == -1) cout << '-';
	if (this->degree > 1) cout << "x^" << this->degree;
	else cout << "x";
}
bool Monomial::add(const Monomial &other)
{
	if (this->degree == other.degree)
	{
		this->coefficient += other.coefficient;
		return true;
	}
	return false;
}


