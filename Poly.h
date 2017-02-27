/***************************************************************************************************************
Title: Polynomial Multiplication Assignment1
Author: Chris Hamburger
created: 2/24/17
Description: Given a formatted text file as an argument, this program parses through it and creates Polynomials, 
             muliplying them, and prints them out based on the text file supplied at the command line.

Purpose: To practice desiging and implemengting classes and using existing class templates.  

Compile: Navigate to the program directory and run the make command to create an executable file.

Executable name: assignment1

To run: copy command inside the brackets [./assignment1 <name_of_text_file_argument.txt>]

*****************************************************************************************************************/

#ifndef POLY_H
#define POLY_H

#include <list>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <map>
#include <iterator>

using namespace std;

class Poly{

public:
	
	Poly();
	Poly(int p, int q);


	Poly(const Poly &p);
	~Poly(){}
	void insertNewTerm(int p, int q);
	double eval(double x);
	int listSize(){	return terms.size();}
	Poly operator* (const Poly &p);
	friend ostream& operator<<(ostream &out, Poly& p);
	Poly operator=(const Poly &p);	
	void combineLikeTerms();

	struct Term{
		int coef, exp;
		void setVals( int x, int y){ coef=x; exp=y;}
		int getCoef()const{ 	return coef;}
		int getExp()const{	return exp;}

	};

	list <Term>terms;
	
private:
	void insertTerm(Term & p){	terms.push_back(p);}
};


#endif
