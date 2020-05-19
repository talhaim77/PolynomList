#include "Polynomial.h"
using namespace std;
#pragma once
void Polynomial::add(const Monomial &m)
{
	Monomial *temp;
	temp = new Monomial(m.getCoefficient(), m.getDegree());
	if (!temp)
		exit(1);
	addMonomial(temp);
}

void Polynomial::addMonomial(Monomial *monom)
{
	Monomial *current =this->head;
	Monomial *previous=NULL;
	if (current == NULL)  // insertFirst
	{
		this->head = monom;
		return;
	}
		while (current->getDegree() > monom->getDegree() )
		{
			previous = current;
			if (current->next != NULL)
				current = current->next;
			else
			{
				current->next = monom;
				return;
			}
	}
	if(current->degree == monom->getDegree())
	{
		current->coefficient +=monom->getCoefficient();
		if (current->coefficient == 0)// delete A Node from the list
		{
				Monomial *temp = current; //save reference to first link
				if (current->next == NULL) 
				{
					if (previous == NULL) //a private case,if there is only one node in the list,
						//after delete the list will be empty,head will point to null.
					{
						this->head = NULL;
					}
					else
					previous->next = NULL;
				}
				else if (current == this->head)
				{
					this->head = this->head->next;
				}
				else
					previous->next = current->next;
				delete(temp);
		}
		delete(monom);
	}
	else  // insertBefore the current node
	{
		monom->next = current;
		if (this->head == current)
			this->head = monom;
		else
		{
			previous->next = monom;
		}
	}
}


void Polynomial::print()
{

	Monomial *temp = this->head;
	if (!temp)
	{
		cout << "0";
		return;
	}
	if (temp->degree == 0) {
		cout << temp->coefficient;
		return;
	}
	if (temp->coefficient != 1 && temp->coefficient != -1) 
		cout << temp->coefficient;
	else if (temp->coefficient == -1) cout << '-';
	if (temp->degree > 1) cout <<"x^"<<temp->degree;
	else cout <<"x";
	temp = temp->next;
	while(temp != NULL) 
	{
		if (temp->degree == 0) {
			if (temp->coefficient > 0) 
				cout <<"+" <<temp->coefficient;
			else
				cout <<temp->coefficient;
			break;
		}
		if (temp->coefficient > 1) cout <<"+"<<temp->coefficient;
		else if (temp->coefficient < -1) cout << temp->coefficient;
		else if (temp->coefficient == 1) cout <<"+";
		else cout << "-";
		if (temp->degree > 1) cout <<"x^" <<temp->degree;
		else cout <<"x";
		temp = temp->next;
	}


}
Polynomial::Polynomial()
{
	head = NULL;
}
Polynomial::~Polynomial()
{ // d'tor to delete the polynomial linked list node by node(monomial)
	Monomial *previous, *forward;
	if (head)
	{
		previous = head;
		forward = head->next;
		while (forward)
		{
			delete previous;
			previous = forward;
			forward = forward->next;
		}
		delete previous;
	}
}
