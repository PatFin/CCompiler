#include <iostream>

#include "Array.h"

#include <iostream>

using namespace Model;
using namespace std;


IntermediateRepresentation::Address Array::buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label)
{
	IntermediateRepresentation::Address exprAddr = arrayIndex->buildIR(firstBB);

	IntermediateRepresentation::Address tmpAddr;
	tmpAddr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R14, IntermediateRepresentation::QWORD);
	tmpAddr.type = IntermediateRepresentation::REGISTER_DIRECT;
	firstBB->add_IRInstr(IntermediateRepresentation::MOVE, exprAddr, IntermediateRepresentation::NULL_ADDRESS, tmpAddr);

	IntermediateRepresentation::Address tabAddr = firstBB->getCfg()->get_var_address(*name);
	tmpAddr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R15, IntermediateRepresentation::QWORD);
	firstBB->add_IRInstr(IntermediateRepresentation::LEA, tabAddr, IntermediateRepresentation::NULL_ADDRESS, tmpAddr);

	IntermediateRepresentation::Address addrDest;
	addrDest.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R15, IntermediateRepresentation::QWORD);
	addrDest.offset = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R14, IntermediateRepresentation::QWORD);
	addrDest.type = IntermediateRepresentation::REGISTER_INDIRECT_SCALE_8;
	return addrDest;
}

bool Array::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols Array --" << endl;
#endif
	bool correct = true;

	bool found = false;

	for(list<map<string,Symbole>*>::reverse_iterator lastLevel = symbolTable->rbegin() ; lastLevel != symbolTable->rend(); lastLevel++)
	{
		map<string,Symbole>::iterator it = (*lastLevel)->find(*name);
		if(it != (*lastLevel)->end())
		{
			if(it->second.getType() == VARIABLE)
			{
				found = true;
				t = it->second.getTypage();

				it->second.setUsed();
			}
		}
	}

	if(!found){
		correct = false;
		cerr << "ERROR on line "<< this->getLine() <<" use of undefined variable : " << *name << endl;
	}

	if(!(arrayIndex==nullptr) && !arrayIndex->computeAndVerifySymbols(symbolTable))
		correct = false;
	return correct;
}

// ----------------------------- Constructors ----------------------------------

Array::Array(std::string * identifier, Expression* value, int line)
	:name(identifier), arrayIndex(value), LValue(line)
{
#ifdef DEBUG
    cout << "-- Constructor Array --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Array::~Array()
{
#ifdef DEBUG
	cout << "-- Destructor Array --" << endl;
#endif
	delete name;
	delete arrayIndex;
}
