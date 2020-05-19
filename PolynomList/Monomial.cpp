#include "Monomial.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>  
using namespace std;

int Monomial::monomialNumber = 0;
Monomial::Monomial(double coefficient, int degree) : degree(degree)
{ //c'tor with initialize list for the const variable for Monomial class
	if (degree < 0)
		( this->~Monomial() );
	else
	{
		this->coefficient = coefficient;
		monomialNumber++;
	}
	
}
Monomial::Monomial(const Monomial &copyCtor)
{ //copy c'tor using operator overloading m1 equal m2

	*this = copyCtor;
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

const Monomial& Monomial::operator=(const Monomial& other)
{
	this->setCoefficient(other.getCoefficient());
	this->setDegree(other.getDegree());
	return *this;
}
Monomial Monomial::operator+(const Monomial& other) const
{
	if (this->getDegree() == other.getDegree())
		return Monomial(this->coefficient + other.coefficient,this->degree);
	else
	{
		monomialNumber++;
		return Monomial(*this);
	}
}
Monomial Monomial::operator-(const Monomial& other) const
{
	if (this->getDegree() == other.getDegree())
		return Monomial(this->coefficient - other.coefficient, this->degree);
	else
	{
		monomialNumber++;
		return Monomial(*this);
	}
}
Monomial Monomial::operator*(const Monomial& other) const
{
	return Monomial(this->getCoefficient() * other.getCoefficient(), this->getDegree() + other.getDegree());
}
const Monomial& Monomial::operator+=(const Monomial& other)
{
	//a+=b ===> a=a+b
	*this = *this + other;
	return *this;
}
const Monomial& Monomial::operator-=(const Monomial& other)
{
	//a-=b ===> a=a+b
	*this = *this - other;
	return *this;
}
const Monomial& Monomial::operator*=(const Monomial& other)
{
	//a*=b ===> a=a*b
	*this = (*this) * other;
	return *this;
}
const Monomial& Monomial::operator-()
{
	//a=-a 
	this->coefficient *= -1;
	return *this;
}
bool Monomial::operator==(const Monomial& other)
{
	if ( (this->getCoefficient() == other.getCoefficient())&&(this->getDegree()==other.getDegree()))
		return true;
	else
		return false;
}
bool Monomial::operator!=(const Monomial& other)
{
	return !(*this == other);
}  

ostream& operator<<(ostream & out, const Monomial &other)
{
	if (other.getDegree() == 0) {
		out << other.getCoefficient();
		return out;
	}
	if (other.getCoefficient() != 1 && other.getCoefficient() != -1)
		out << other.getCoefficient() << "*";
	else if (other.getCoefficient() == -1) out << "-1*";
	if (other.getDegree() > 1) out << "x^" << other.getDegree();
	else out << "x";
	return out;
}
istream& operator>>(istream & stream, Monomial &monom)
{
	string str;
	string temp_coefficient, temp_degree="";
	getline(stream, str);
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	int i = 0;
	unsigned int x_index;
	temp_coefficient = str;
	monom.setDegree(0);
	if ((x_index = str.find('x')) != string::npos)
	{
		temp_coefficient = "";
		while ((unsigned)i != x_index)
			temp_coefficient += str[i++];
		if (str[x_index + 1] != '\0')
		{
			x_index += 2;
			while (str[x_index] != '\0')
				temp_degree += str[x_index++];
			monom.degree = stoi(temp_degree);
		}
		else
			monom.degree = 1;
	}
	monom.coefficient = stod(temp_coefficient);
	return stream;
}
double Monomial::operator()(const double r)
{
	double num = this->getCoefficient()*(pow(r, this->getDegree())) ;
	return num;
}

