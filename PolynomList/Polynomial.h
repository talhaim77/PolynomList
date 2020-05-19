/*
Student:Tal Haim
ID 206220451
*/
#pragma once
#include <iostream>
#include <stdlib.h>
#include "Monomial.h"
using namespace std;

class Polynomial
{
	friend ostream & operator<<(ostream &, const Polynomial &);
	friend istream & operator>>(istream &, Polynomial &); 
private:
	Monomial *head;
public:
	Polynomial();
	Polynomial(const Polynomial &copyCtor);
	~Polynomial();
	void add(const Monomial &m);
	void addMonomial(Monomial *monom);
	void deleteNodes();
	void print();
	const Polynomial& addWithString(string, int);
	////operator overloading section////
	const Polynomial& operator=(const Polynomial&);
	Polynomial operator+(const Monomial&) const;
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator-(const Monomial&) const;
	Polynomial operator-(const Polynomial&) const;
	Polynomial& operator+=(Polynomial&);
	const Polynomial& operator+=(const Monomial&);
	Polynomial& operator-=(Polynomial&);
	const Polynomial& operator-=(const Monomial&);
	const bool operator==(const Monomial&) const;
	const bool operator!=(const Monomial&) const;
	const bool operator==(const Polynomial&)const;
	const bool operator!=(const Polynomial&) const;
	Polynomial& operator-();
	const double operator()(const double op)const;
	double operator[](int) const;
	
};