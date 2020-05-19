/*
Student:Tal Haim
ID 206220451
*/
#include <iostream>
#pragma once
class Polynomial;
class Monomial
{

public:
	static int monomialNumber;
	Monomial(double coefficient = 1, const int degree = 0);
	~Monomial();
	void print() const;
	bool add(const Monomial &other);
	static int getNumberOfMonomials();
	double getCoefficient() const { return coefficient; }
	void setCoefficient(double value) { coefficient = value; }
	unsigned int getDegree() const { return degree; }
	friend Polynomial;
private:
	double coefficient;
	const int degree;
	Monomial* next=NULL;
};
