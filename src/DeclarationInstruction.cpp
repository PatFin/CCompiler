#include <iostream>

#include "DeclarationInstruction.h"

using namespace Model;
using namespace std;


bool DeclarationInstruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes DeclarationInstruction --" << endl;
#endif

	bool correct = true;
	for(list<Declaration*>::iterator declaration = declarations->begin(); declaration != declarations->end(); declaration++){
		if(!(*declaration)->verifyExpressionsTypes())
			correct = false;
	}
	return correct;
}

bool DeclarationInstruction::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable) {
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols DeclarationInstruction --" << endl;
#endif
	bool correct = true;
	for(list<Declaration*>::iterator declaration = declarations->begin(); declaration != declarations->end(); declaration++){
		if(!(*declaration)->computeAndVerifySymbols(symbolTable))
			correct = false;
	}
	return correct;
}

void DeclarationInstruction::buildIR(IntermediateRepresentation::BasicBlock* firstBB)
{
	for (list<Declaration*>::iterator d = declarations->begin(); d != declarations->end(); d++) {
		(*d)->buildIR(firstBB);
	}
}

// ----------------------------- Constructors ----------------------------------

DeclarationInstruction::DeclarationInstruction(Types* aType,
											   list<Declaration*>* decl)
	: type(aType), declarations(decl), Instruction(decl->back()->getLine())
{
	for(list<Declaration*>::iterator declaration = declarations->begin(); declaration != declarations->end(); declaration++){
		(*declaration)->setType(*type);
	}
#ifdef DEBUG
    cout << "-- Constructor DeclarationInstruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

DeclarationInstruction::~DeclarationInstruction()
{
#ifdef DEBUG
    cout << "-- Destructor DeclarationInstruction --" << endl;
#endif
	delete type;

	while (!declarations->empty())
	{
		delete declarations->back();
		declarations->pop_back();
	}
	delete declarations;
}
