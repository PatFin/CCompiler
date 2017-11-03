#include <iostream>

#include "Declaration.h"
#include "Expression.h"
#include "Value.h"

using namespace std;
using namespace Model;

bool Declaration::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols Declaration --" << endl;
#endif
	bool correct = true;

	// TODO - Tester si expression est correct

	map<string,Symbole>* lastLevel = (*(symbolTable->rbegin()));

	Symbole varSymbole(*name,VARIABLE,t, *this);
	if(lastLevel->find(*name) == lastLevel->end()){
		lastLevel->emplace(*name,varSymbole);
	}
	else{

		cerr << "ERROR on line "<< this->getLine() <<" redefinition of variable : " << *name << endl;
		correct = false;
	}

	return correct;
}

std::string Declaration::getName()
{
	return *(this->name);
}

void Model::Declaration::setType(Types type){
	t = type;
}

// ----------------------------- Constructors ----------------------------------

Model::Declaration::Declaration(std::string * aName, int line)
	:name(aName), Line(line)
{
#ifdef DEBUG
    cout << "-- Constructor Declaration --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Model::Declaration::~Declaration()
{
#ifdef DEBUG
    cout << "-- Destructor Declaration --" << endl;
#endif
	delete name;
}
