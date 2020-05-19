/*
Student:Tal Haim
ID 206220451
*/
#pragma once
#include <iostream>
using namespace std;
class Polynomial;
class Monomial
{
	friend Polynomial;
	friend ostream & operator<<(ostream &, const Polynomial &);
	friend ostream & operator<<(ostream &, const Monomial &);
	friend istream & operator>>(istream & , Monomial &);
	
public:
	Monomial(double coefficient = 1, int degree = 0);
	Monomial(const Monomial &toCopy);
	~Monomial();
	double getCoefficient() const { return coefficient; }
	int getDegree() const { return this->degree; }
	static int getNumberOfMonomials();
	Monomial* ptrNext() { return this->next; }
	double& getCoefficentReference() { return coefficient; };

	////operator overloading section////
	const Monomial& operator=(const Monomial&);
	Monomial operator+(const Monomial&) const;
	Monomial operator-(const Monomial&) const;
	Monomial operator*(const Monomial&) const;
	const Monomial& operator+=(const Monomial&);
	const Monomial& operator-=(const Monomial&);
	const Monomial& operator*=(const Monomial&);
	const Monomial& operator-();
	bool operator==(const Monomial&);
	bool operator!=(const Monomial&);
	double operator()(const double);

private:
	double coefficient;
	int degree;
	static int monomialNumber;
	void setCoefficient(double value) { coefficient = value; }
	void setDegree(int setDegree) { degree = setDegree; }
	Monomial* next=NULL;
};
