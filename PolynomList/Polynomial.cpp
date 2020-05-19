#define _CRT_SECURE_NO_WARNINGS
#include "Polynomial.h"
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
Polynomial::Polynomial()
{
	head = NULL;
}
Polynomial::Polynomial(const Polynomial &copyCtor)
{
	this->head = NULL;
	Monomial *temp =  copyCtor.head;
	Monomial toAdd;
	while (temp != NULL)
	{
		toAdd = *temp;
		this->add(toAdd);
		temp = temp->next;
	}

}
Polynomial::~Polynomial()
{ // d'tor to delete the polynomial linked list node by node(monomial)
	this->deleteNodes();
}
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

void Polynomial::deleteNodes()
{ // a function to delete the nodes from the polynomial
	//using the concept of linked list as a data structure
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
	this->head = NULL;
}
const Polynomial& Polynomial::operator+=(const Monomial& monom)
{
	//p=p+monom
	this->add(monom);
	return *this;
}

Polynomial & Polynomial::operator+=(Polynomial &p)
{
	// += operator overloading <==> this=this+p
	*this = *this + p;
	return *this;
}

Polynomial & Polynomial::operator-=(Polynomial &p)
{
	// this function overloading the binary opertator this->polynom-=(other polynom)
	*this = *this - p;
	return *this;
}

const Polynomial& Polynomial::operator-=(const Monomial& monom)
{
	// -= operator overloading <==> this=this-monom

	Monomial temp = monom;
	-temp;
	this->add(temp);
	return *this;
}
const bool Polynomial::operator==(const Monomial &monom) const
{
	bool flag =1;
	Monomial *temp = this->head;
	if (temp->next != NULL) //there is more than one Monomial in this Polynomial
		return false;
	else
	{
		if (*temp != monom)
			flag = 0;
	}
	return flag;
}
const bool Polynomial::operator!=(const Monomial &monom) const
{
	return !((*this) == monom);
}
const bool Polynomial::operator==(const Polynomial &polynom) const
{
	bool flag = 1;
	Monomial *p = this->head, *k = polynom.head;
	if (p == NULL && k != NULL)
		return false;
	if (k == NULL && p != NULL)
		return false;
	while (p&&k)
	{
		if (*p != *k)
		{
			return false;
		}
		p = p->next;
		k = k->next;
		if (p == NULL && k != NULL)
			return false;
		if (k == NULL && p != NULL)
			return false;
	}
	return flag;
}
const bool Polynomial::operator!=(const Polynomial &polynom) const
{
	return !(*this == polynom);
}
Polynomial & Polynomial::operator-()
{
	// this function overloading the unary minus opertator -(polynomial)
	Monomial *p = this->head;
	while (p)
	{
		*p = -(*p);
		p = p->next;
	}
	return *this;

}
const double Polynomial::operator()(const double oprnd) const
{
	Monomial *temp = this->head;
	double value=0;
	if (temp == NULL)
		value = 0;
	else
	{
		while (temp != NULL)
		{
			value += (*temp)(oprnd);
			temp = temp->next;
		}
	}
	return value;
}
double Polynomial::operator[](int degree) const
{
	Monomial *temp = this->head;

	while (temp != NULL)
	{
		if (temp->getDegree() == degree)
		return temp->getCoefficentReference();
		temp = temp->next;
	}
	return (0);
}

const Polynomial& Polynomial::addWithString(string str,int n)
{ // function that get a string and build a new node in the linked list of
	//this polynomial. 
	Monomial monom;
	string temp_coefficient, temp_degree = "";
	
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
	this->add(monom);
	
	return *this;
}

const Polynomial& Polynomial::operator=(const Polynomial& polynom)
{
	Monomial *temp = polynom.head;
	Monomial toAdd;
	this->deleteNodes();
	this->head=NULL;
	while (temp != NULL)
	{
		toAdd = *temp;
		this->add(toAdd);
		temp = temp->next;
	}
	return *this;
}
Polynomial Polynomial::operator+(const Monomial& monom) const
{
	Monomial *ptr = this->head;
	Polynomial temp;
	temp += monom;
	if (ptr == NULL)
	{
		return Polynomial(temp);
	}
	while (ptr != NULL)
	{
		temp += *ptr;
		ptr = ptr->next;
	}
	return Polynomial(temp);
}
Polynomial Polynomial::operator+(const Polynomial& poly) const
{
	Polynomial temp;
	Monomial toAdd;
	Monomial *ptr1 = this->head, *ptr2 = poly.head;
	while (ptr1&&ptr2)
	{
		if (ptr1->getDegree() == ptr2->getDegree())
		{
			toAdd = *ptr1;
			toAdd += *ptr2;
			temp.add(toAdd);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		else if (ptr1->getDegree() > ptr2->getDegree())
		{
			toAdd = *ptr1;
			temp.add(toAdd);
			ptr1 = ptr1->next;
		}
		else 
		{
			toAdd = *ptr2;
			temp.add(toAdd);
			ptr2 = ptr2->next;
		}
	}
	while (ptr1 != NULL)
	{
		toAdd = *ptr1;
		temp.add(toAdd);
		ptr1 = ptr1->next;
	}
	while (ptr2 != NULL)
	{
		toAdd = *ptr2;
		temp.add(toAdd);
		ptr2 = ptr2->next;
	}
	return Polynomial(temp);
}

Polynomial Polynomial::operator-(const Monomial &monom) const
{
	Monomial *ptr = this->head;
	Polynomial temp;
	temp -= monom;
	if (ptr == NULL)
	{
		return Polynomial(temp);
	}
	while (ptr != NULL)
	{
		temp+= (*ptr);
		ptr = ptr->next;
	}
	return Polynomial(temp);
}

Polynomial Polynomial::operator-(const Polynomial& poly) const
{
	if (this->head == NULL)
		return Polynomial(poly);
	if (this->head==NULL)
		return Polynomial(*this);
	Polynomial temp;
	Monomial toAdd;
	Monomial *ptr1 = this->head, *ptr2 = poly.head;
	while (ptr1&&ptr2)
	{
		if (ptr1->getDegree() == ptr2->getDegree())
		{
			//toAdd = *ptr1 - *ptr2;
			toAdd = *ptr1;
			toAdd -= *ptr2;
			if(toAdd.getCoefficient()!=0)
			temp.add(toAdd);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		else if (ptr1->getDegree() > ptr2->getDegree())
		{
			toAdd = *ptr1;
			temp.add(toAdd);
			ptr1 = ptr1->next;
		}
		else
		{
			toAdd = -*(ptr2);
			temp.add(toAdd);
			ptr2 = ptr2->next;
		}
	}
	while (ptr1 != NULL)
	{
		toAdd = *ptr1;
		temp.add(toAdd);
		ptr1 = ptr1->next;
	}
	while (ptr2 != NULL)
	{
		toAdd = -*ptr2;
		temp.add(toAdd);
		ptr2 = ptr2->next;
	}
	return Polynomial(temp);
}



ostream& operator<<(ostream & out, const Polynomial &polynom)
{
	Monomial *temp = polynom.head;
	if (!temp)
	{
		out << "0";
		return out;
	}
	if (temp->getDegree() == 0) {
		out << temp->getCoefficient();
		return out;
	}
	if (temp->getCoefficient() != 1 && temp->getCoefficient() != -1)
		out << temp->getCoefficient();
	else if (temp->getCoefficient() == -1) out << '-';
	if (temp->getDegree() > 1 && temp->getCoefficient() == 1) out << "x^" << temp->getDegree();
	else if (temp->getDegree() > 1 && temp->getCoefficient()!=1) out << "*x^" << temp->getDegree();
	else out << "x";
	temp=temp->ptrNext();
	while (temp != NULL)
	{
		if (temp->getDegree() == 0) {
			if (temp->getCoefficient() > 0)
				out << "+" << temp->getCoefficient();
			else
				out << temp->getCoefficient();
			break;
		}
		if (temp->getCoefficient() > 1) out << "+" << temp->getCoefficient();
		else if (temp->getCoefficient() < -1) out << temp->getCoefficient();
		else if (temp->getCoefficient() == 1) out << "+";
		else out << "-";
		if (temp->getDegree() > 1) out << "*x^" << temp->getDegree();
		else out << "*x";
		temp = temp->ptrNext();
	}
		return out;
}
istream & operator>>(istream &stream, Polynomial &polynom)
{
	string str;
	if (polynom.head) {
		polynom.deleteNodes();
	}
	getline(stream, str);
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	char *arr, *temp;
	temp = new char[str.length()];
	arr = new char[str.length()];
	for (unsigned int i = 0; i < str.length(); i++)
		arr[i] = str[i];

	int i, j = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (i == 0)
				continue;

			strncpy(temp, arr + j, i - j);
			temp[i - j] = '\0';
			string tString = temp;
			//function to add monom string-->polynom(using cin >> temp_monom )
			// polynom+=monom
			polynom.addWithString(tString, i - j);

			j = i;

		}
		if (str[i] == ',')
		{
			//temp = new char(i - j + 1);
			strncpy(temp, arr + j, i - j);
			temp[i - j] = '\0';
			string tString = temp;
			//function to add monom string-->polynom(using cin >> temp_monom )
			// polynom+=monom
			polynom.addWithString(tString, i - j);


			break;
		}
	}
	delete[] arr;
	delete[] temp;
	return stream;
}
