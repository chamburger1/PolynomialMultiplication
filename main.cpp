/***************************************************************************************************************
Title: Polynomial Multiplication Assignment1

Author: Chris Hamburger

Created: 2/24/17

Description: Given a formatted text file as an argument, this program parses through it and creates Polynomials, 
             muliplying them, and prints them out based on the text file supplied at the command line.

Purpose: To practice desiging and implemengting classes and using existing class templates.  

Compile: Navigate to the program directory and run the make command to create an executable file.

*****************************************************************************************************************/

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include "Poly.h"
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

int main (int argc, char *argv[]){
set <int> usedIndices;

vector<Poly*> vectorOfPolys(100);				

ifstream inFile;
string line, filename;
int count=0;

if(argc==1){
	cerr<<"No input file provided"<<endl;
}
else{
	filename=argv[1];
	inFile.open(filename);

}

if(!inFile){
	cerr<<"File unable to be opened"<<endl;
}
else{	//parse file getting line
	while(getline(inFile, line)){ //get the line
		count++;
		unsigned int index;
		string first, symbol;
		istringstream   linestream(line);
		linestream>>first;
		//first item in the linestream will either be string eval, print, or int index(converted using std::stoi 
		if(first=="eval"){
			int x;
			string paren;
			double value;
			linestream>>x>>paren>>value;
			if(usedIndices.count(x)==0){
				Poly *newZeroPoly=new Poly;
				vectorOfPolys.at(x)=newZeroPoly;
			}
			cout<<count<<". Eval: Poly["<<x<<"]("<<value<<")= "<<vectorOfPolys.at(x)->eval(value)<<endl;
		}
		else if(first=="print"){
			linestream>>index;
			if(usedIndices.count(index)==0){
				Poly *newZeroPoly=new Poly;
				vectorOfPolys.at(index)=newZeroPoly;
			}
			cout<<count<<". Poly["<<index<<"]= "<<*vectorOfPolys.at(index)<<endl;
		}	
		else{
			//try to convert the string to an int
			//should never fail if file formatted correctly but handle exception nonetheless
			try{
				index=stoi(first);
			}
			catch(invalid_argument&){
				cerr<<"error with conversion"<<endl;
			};

			string timesSymbol;
			unsigned int x, y;
			linestream>>symbol;
			if(symbol=="="){
				linestream>>x>>timesSymbol>>y;

				//check bounds of index and x and y (multiplicand and a multiplier Polys)
				if(vectorOfPolys.capacity()-1<x){
					vectorOfPolys.resize(x+1);
				}
				if(vectorOfPolys.capacity()-1<y){
					vectorOfPolys.resize(y+1);
				}
				if(vectorOfPolys.capacity()-1<index){
					vectorOfPolys.resize(index+1);
				}
				Poly *newPoly=new Poly;

				//check index Zero Poly-if 0 terms then uninitialized-set to Zero poly
				//uses stl set to confirm if an index in vecor holds a poly object
				//if not, create a zero poly and store at index
				if(usedIndices.count(x)==0){
					Poly *newZeroPoly=new Poly;
					vectorOfPolys.at(x)=newZeroPoly;
				}
				if(usedIndices.count(y)==0){
					Poly *newZeroPoly=new Poly;
					vectorOfPolys.at(y)=newZeroPoly;
				}					

				//derefernce pointers 
				(*newPoly)=*vectorOfPolys.at(x)**vectorOfPolys.at(y);
				vectorOfPolys.at(index)=newPoly;
				usedIndices.insert(index);

				cout<<count<<". Poly["<<index<<"]= "<<"Poly["<<x<<"] * Poly["<<y<<"]"<<endl;

			}
			else if(symbol==":"){
				int counter =0;
				while(linestream>>x>>y){
					if(vectorOfPolys.size()-1<index){
						vectorOfPolys.resize(index+1);
					}
					if(counter==0){
						Poly *curr=new Poly(x, y);
						counter++;
						vectorOfPolys.at(index)=curr;
						usedIndices.insert(index);
					}
					else{
						vectorOfPolys.at(index)->insertNewTerm(x, y);
					}
				}
				vectorOfPolys.at(index)->combineLikeTerms();
				cout<<count<<". "<<*vectorOfPolys.at(index)<<endl;
			}

			
		}//end else
	}//end of while
}


//deallocate dynamically allocated memory
for(unsigned int i=0; i<vectorOfPolys.size(); i++){
	delete vectorOfPolys.at(i);
}

return 0;
}
