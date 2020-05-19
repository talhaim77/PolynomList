/*
Student:Tal Haim
ID 206220451
*/
#include <iostream>
#include <stdlib.h>
#include "Monomial.h"
#pragma once
class Polynomial
{
	Monomial *head;
	
public:
	Polynomial();
	~Polynomial();
	void add(const Monomial &m);
	void addMonomial(Monomial *monom);
	void print();
};