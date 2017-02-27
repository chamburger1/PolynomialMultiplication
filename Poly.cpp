/***************************************************************************************************************
Title: Polynomial Multiplication Assignment1

Author: Chris Hamburger

Created: 2/24/17

Description: Given a formatted text file as an argument, this program parses through it and creates Polynomials, 
             muliplying them, and prints them out based on the text file supplied at the command line.

Purpose: To practice desiging and implemengting classes and using existing class templates.  

Compile: Navigate to the program directory and run the make command to create an executable file.

Executable name: assignment1

To run: copy command inside the brackets [./assignment1 name_of_text_file_argument.txt]

*****************************************************************************************************************/

#ifndef POLY_CPP
#define POLY_CPP

#include "Poly.h"

//copy constructor 
Poly::Poly(const Poly& p){
	this->terms.assign(p.terms.begin(), p.terms.end());
}

//default Zero-polynomial constructor
Poly::Poly(){
	Term curr; 
	curr.setVals(0, 0); 
	insertTerm(curr);
}

//single term constructor for a single non-zero polynomial
Poly::Poly(int p, int q){
	if(p!=0){
		Term curr; 
		curr.setVals(p, q); 
		insertTerm(curr);
	}
}

//overloads the = operator to assign terms in argument Poly P to calling Poly
Poly Poly::operator=(const Poly &p){//working

	this->terms.assign(p.terms.begin(), p.terms.end());
	return *this;
}

//evaluate function that takes double as parameter
//iterates through calling Poly object's list container-performs mathematical operations
double Poly::eval(double x){
	list<Term>::iterator it;
	double sum=0;

	for(it=terms.begin(); it!=terms.end(); it++){
		double y, z, product;
		y=it->getCoef(); //coefficient
		z=it->getExp(); //exponent 
		
		if(it->getExp()==0)
			product=it->getCoef();
		else
			product=pow(x, z)*y;

		sum=sum+product;
	}

	return sum;
}

//Function to add more terms to a Poly 
void Poly::insertNewTerm(int p, int q){
	Term curr; 
	curr.setVals(p, q); 
	insertTerm(curr); 
}

//overloaded multiplication operator iterates through argument Poly object and calling Poly object using implicit this
//uses STL map with <exponent, coefficient> pairs to automatically combine like terms
Poly Poly::operator*(const Poly &p){
	Poly *newPoly=new Poly;
	
	list<Poly::Term>::const_iterator itP, itQ;
	map<int, int> coefExpPairs;

	for(itQ=this->terms.begin(); itQ!=this->terms.end(); itQ++){
		for(itP=p.terms.begin(); itP!=p.terms.end(); itP++){
			int x=itP->getCoef()*itQ->getCoef();
			int y=itP->getExp()+itQ->getExp();
			if(x!=0){
				if(!coefExpPairs.insert(make_pair(y,x)).second){
					coefExpPairs.at(y)=coefExpPairs.at(y)+x;
				}


  			}
		}
	}


	for(auto &x: coefExpPairs){
		newPoly->insertNewTerm(x.second, x.first);
	}

	return *newPoly;
}

//iterating through list to combine like terms
//need to make sure iterator is valid or seg so iterator
//set if erase condition met if not iterate through list
void Poly::combineLikeTerms(){
	map<int, int> coefExpPairs;
	for(list<Poly::Term>::iterator itP=terms.begin(); itP!=terms.end(); ){
			int x=itP->getCoef();
			int y=itP->getExp();

			//if there is a 0x^0 term with more then 1 term-not 0 poly and remove term
			if(y==0&&x==0&&listSize()>1){
				itP=terms.erase(itP);
			}
			
			else if(!coefExpPairs.insert(make_pair(y,x)).second){
				coefExpPairs.at(y)=coefExpPairs.at(y)+x;
				itP=terms.erase(itP);
  			}
			else
				itP++;
	}
}

//overloading <<outstream operator-declared as friend-given Poly object reference and outstream object
//send data to outstream and return outstream ref
ostream& operator<<(ostream &out, Poly &p){
	int count=0;
	p.terms.sort([](Poly::Term a, Poly::Term b){return a.getExp()> b.getExp();});
	
	for(auto &x: p.terms){
		if(x.getCoef()>0){
			if(count!=0){
				count++;
				out<<"+";
			}
			out<<x.getCoef();
			count++;
			if(x.getExp()!=0)
				out<<"x^"<<x.getExp();
		}
		else if(x.getCoef()<0){
			count++;
			out<<x.getCoef();
			if(x.getExp()!=0)
				out<<"x^"<<x.getExp();
		}
	}
	return out;
}

#endif


