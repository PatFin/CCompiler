#include <iostream>

#include "ParameterDeclaration.h"
#include <iostream>

using namespace Model;
using namespace std;

std::string ParameterDeclaration::getName()
{
	return *name;
}

void ParameterDeclaration::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	firstBB->getCfg()->add_to_symbol_table(*name, *type);
	IntermediateRepresentation::Address addr = firstBB->getCfg()->get_var_address(*name);
	// firstBB->add_IRInstr(IntermediateRepresentation::POP, IntermediateRepresentation::NULL_ADDRESS, IntermediateRepresentation::NULL_ADDRESS, addr);
}

Types ParameterDeclaration::getType()
{
	return *type;
}

bool ParameterDeclaration::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable)
{
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols ParameterDeclaration --" << endl;
#endif
	bool correct = true;

	std::map<string, Symbole>* topLevel = *(symbolTable->rbegin());

	if (topLevel->find(*name) != topLevel->end())
	{
		cerr << "ERROR on line "<< this->getLine() <<" multiple definition of parameter : " << *name << endl;
		correct = false;
	}
	else
	{
		Symbole parameter = Symbole(*name, VARIABLE,*type, *this);
		topLevel->emplace(*name, parameter);
	}

	return correct;
}

// ----------------------------- Constructors ----------------------------------

ParameterDeclaration::ParameterDeclaration(Types* aType, std::string * aName, int line)
	:type(aType), name(aName), Line(line)
{
#ifdef DEBUG
    cout << "-- Constructor ParameterDeclaration --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

ParameterDeclaration::~ParameterDeclaration()
{
#ifdef DEBUG
	cout << "-- Destructor ParameterDeclaration --" << endl;
#endif
	delete name;
	delete type;
}
