#include <iostream>

#include "Symbole.h"

using namespace Model;
using namespace std;


bool Symbole::operator==(Symbole const& other){
	return (this->name == other.name )&&(this->type == other.type);
}

Types Symbole::getTypage(){
	return t;
}

TYPESYMBOLE Symbole::getType(){
	return type;
}

void Symbole::addFunctionParameters(list<Types>* parameters){
	functionParameters = parameters;
}

list<Types>* Symbole::getFunctionParameters(){
	return functionParameters;
}

void Symbole::setUsed()
{
	used = true;
}

bool Symbole::isUsed()
{
	return used;
}

string Symbole::getName()
{
	return name;
}

// ----------------------------- Constructors ----------------------------------

Symbole::Symbole(std::string aName,TYPESYMBOLE aType, Types aT, Line aLine)
	:name(aName), type(aType) , t(aT), functionParameters(nullptr), used(false), Line(aLine)
{
#ifdef DEBUG
    cout << "-- Constructor Symbole --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Symbole::~Symbole()
{
#ifdef DEBUG
    cout << "-- Destructor Symbole --" << endl;
#endif
	if(functionParameters != nullptr){
		delete functionParameters;
	}
}
