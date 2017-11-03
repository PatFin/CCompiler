#include <iostream>

#include "ReturnInstruction.h"

using namespace Model;
using namespace std;


bool ReturnInstruction::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable)
{
	bool correct = true;
	if (expression != nullptr && !expression->computeAndVerifySymbols(symbolTable))
	{
		correct = false;
	}

	return correct;
}

void ReturnInstruction::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	IntermediateRepresentation::Address addr = expression->buildIR(firstBB);
	IntermediateRepresentation::Address retaddr;

	switch (expression->getType().getTypeValue()) {
	default:
	case VOID:
		retaddr = IntermediateRepresentation::NULL_ADDRESS;
		break;
	case CHAR:
		retaddr.type = IntermediateRepresentation::REGISTER_DIRECT;
		retaddr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R0, IntermediateRepresentation::BYTE);
		retaddr.offset = 0;
		break;
	case INT32:
		retaddr.type = IntermediateRepresentation::REGISTER_DIRECT;
		retaddr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R0, IntermediateRepresentation::DWORD);
		retaddr.offset = 0;
		break;
	case INT64:
		retaddr.type = IntermediateRepresentation::REGISTER_DIRECT;
		retaddr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R0, IntermediateRepresentation::QWORD);
		retaddr.offset = 0;
		break;
	}

	firstBB->add_IRInstr(IntermediateRepresentation::RETURN, addr, IntermediateRepresentation::NULL_ADDRESS, retaddr);
}

bool ReturnInstruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes ReturnInstruction --" << endl;
#endif

	bool correct = true;
	if (expression != nullptr && !expression->verifyAndUpdateType())
	{
		correct = false;
	}

	return correct;
}

// ----------------------------- Constructors ----------------------------------

ReturnInstruction::ReturnInstruction(Expression* exp)
	:expression(exp),Instruction(exp->getLine())
{
#ifdef DEBUG
    cout << "-- Constructor ReturnInstruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

ReturnInstruction::~ReturnInstruction()
{
#ifdef DEBUG
	cout << "-- Destructor ReturnInstruction --" << endl;
#endif
	delete expression;
}
