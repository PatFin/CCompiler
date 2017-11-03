#include <iostream>

#include "VariableDeclaration.h"
#include "Expression.h"
#include "Value.h"

using namespace std;
using namespace Model;

bool VariableDeclaration::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes Declaration --" << endl;
#endif

	bool correct = true;
	if(initialisation!=nullptr){
		if(initialisation->verifyAndUpdateType()){
			if(initialisation->getType() != Types(VOID) && t != initialisation->getType()){
				correct = false;
				cerr << "ERROR on line "<< this->getLine() <<" initialisation of variable "<< *name <<" with wrong type."<< endl;
			}
		}
		else{
			correct = false;
		}
	}

	return correct;
}

bool VariableDeclaration::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols VariableDeclaration --" << endl;
#endif
	bool correct = true;

	// TODO - Tester si expression est correct

	map<string,Symbole>* lastLevel = (*(symbolTable->rbegin()));

	Symbole varSymbole(*name,VARIABLE,t, lineNumber);
	if(lastLevel->find(*name) == lastLevel->end()){
		lastLevel->emplace(*name,varSymbole);
	}
	else{

		cerr << "ERROR on line "<< this->getLine() <<" redefinition of variable : " << *name << endl;
		correct = false;
	}

	if(initialisation!=nullptr){
		if(!(initialisation->computeAndVerifySymbols(symbolTable))){
				correct = false;
		}
	}

	return correct;
}

std::string VariableDeclaration::getName()
{
	return *(this->name);
}

IntermediateRepresentation::Address VariableDeclaration::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	firstBB->getCfg()->add_to_symbol_table(*name, t);
	IntermediateRepresentation::Address dest = firstBB->getCfg()->get_var_address(*name);

	IntermediateRepresentation::Address addrValue = initialisation->buildIR(firstBB, *name);

	if(addrValue != IntermediateRepresentation::NULL_ADDRESS)
	{
		firstBB->add_IRInstr(IntermediateRepresentation::MOVE, addrValue, IntermediateRepresentation::NULL_ADDRESS, dest);
	}

	return dest;
}


/// @todo Implement constructor
Model::VariableDeclaration::VariableDeclaration(std::string * aName, Expression* expr, int line)
	:initialisation(expr), Declaration(aName, line)
{
#ifdef DEBUG
    cout << "-- Constructor VariableDeclaration --" << endl;
#endif
}

Model::VariableDeclaration::~VariableDeclaration()
{
#ifdef DEBUG
    cout << "-- Destructor VariableDeclaration --" << endl;
#endif
	delete initialisation;
}

void Model::VariableDeclaration::setType(Types type){
	t = type;
}
