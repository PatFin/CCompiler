#include <iostream>

#include "ArrayDeclaration.h"
#include "Expression.h"
#include "Value.h"

using namespace std;
using namespace Model;

bool ArrayDeclaration::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols ArrayDeclaration --" << endl;
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
		for (std::list<Expression*>::iterator init = initialisation->begin(); init != initialisation->end(); init++)
		{
			if(!((*init)->computeAndVerifySymbols(symbolTable))){
				correct = false;
			}
		}
	}
	return correct;
}

std::string ArrayDeclaration::getName()
{
	return *(this->name);
}

bool ArrayDeclaration::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes Declaration --" << endl;
#endif

	bool correct = true;
	if(initialisation!=nullptr){
		for (std::list<Expression*>::iterator init = initialisation->begin(); init != initialisation->end(); init++)
		{
			if((*init)->verifyAndUpdateType()){
				if((*init)->getType() != Types(VOID) && t != (*init)->getType()){
					correct = false;
					cerr << "ERROR on line "<< this->getLine() <<" initialisation of array "<< *name <<" with wrong type."<< endl;
				}
			}
			else{
				correct = false;
			}
		}
	}

	return correct;
}

IntermediateRepresentation::Address ArrayDeclaration::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	// TODO
	firstBB->getCfg()->add_to_symbol_table(*name, t);
	IntermediateRepresentation::Address dest = firstBB->getCfg()->get_var_address(*name);

	int i = 0;
	for (std::list<Expression*>::iterator expr = initialisation->begin(); expr != initialisation->end(); expr++)
	{
		IntermediateRepresentation::Address exprAddr = (*expr)->buildIR(firstBB);
		IntermediateRepresentation::Address addrDest;
		addrDest.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::BP, IntermediateRepresentation::QWORD);
		addrDest.offset = dest.offset + i * t.getUnitSize();
		addrDest.type = IntermediateRepresentation::REGISTER_INDIRECT_OFFSET;
		firstBB->add_IRInstr(IntermediateRepresentation::MOVE, exprAddr, IntermediateRepresentation::NULL_ADDRESS, addrDest);
		i++;
	}
	return dest;
}


/// @todo Implement constructor
Model::ArrayDeclaration::ArrayDeclaration(std::string * aName, Value* val, std::list<Expression*>* expr, int line)
	:index(val), initialisation(expr), Declaration(aName, line)
{
#ifdef DEBUG
    cout << "-- Constructor ArrayDeclaration --" << endl;
#endif
}

Model::ArrayDeclaration::~ArrayDeclaration()
{
#ifdef DEBUG
    cout << "-- Destructor ArrayDeclaration --" << endl;
#endif
	delete index;
	while(!initialisation->empty())
	{
		delete initialisation->back();
		initialisation->pop_back();
	}
	delete initialisation;
}

void Model::ArrayDeclaration::setType(Types type){
	t = type;
	t.setArraySize(index->getValue());
}
